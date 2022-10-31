#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

void parser(int argc, char* argv[], opt* options);
void reader(int argc, char* argv[], opt* options);
void cat_no_arguments();

int main(int argc, char* argv[]) {
  if (argc == 1) cat_no_arguments();
  opt options = {0};
  parser(argc, argv, &options);
  reader(argc, argv, &options);
  return 0;
}
void parser(int argc, char* argv[], opt* options) {
  int flag;
  const struct option long_option[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, no_argument, NULL, 0}};
  while ((flag = getopt_long(argc, argv, "+benstvTE", long_option, NULL)) !=
         -1) {
    switch (flag) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default:
        fprintf(stderr, "usage: cat [-benstvTE] [file ...]\n");
        exit(1);
    }
  }
}
void cat_no_arguments() {
  char ch;
  while ((ch = getc(stdin)) != EOF) fprintf(stdout, "%c", ch);
}

void reader(int argc, char* argv[], opt* options) {
  int currentFile = optind;
  FILE* fp;
  char ch;

  while (currentFile < argc) {
    fp = fopen(argv[currentFile], "rb");
    currentFile++;
    if (fp == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
              argv[currentFile - 1]);
      continue;
    }

    int lineNumber = 1;
    int position = 0;
    int positionLine = 0;
    int lastLine = 0;
    int currentLine = 0;
    while ((ch = fgetc(fp)) != EOF) {
      if (options->s) {
        currentLine = 0;
        if (ch == '\n' && positionLine == 0) currentLine = 1;
        if (ch == '\n' && positionLine != 0) positionLine = 0;
        if (ch != '\n' && positionLine == 0) positionLine = 1;
        if (currentLine && lastLine) {
          continue;
        }
        lastLine = currentLine;
      }
      if (options->b) {
        if (ch != '\n' && position == 0) {
          fprintf(stdout, "%*d\t", 6, lineNumber);
          lineNumber++;
          position++;
        }
        if (ch == '\n' && position != 0) {
          position = 0;
        }
      } else {
        if (options->n) {
          if (position == 0) {
            fprintf(stdout, "%*d\t", 6, lineNumber);
            lineNumber++;
            position++;
          }
          if (ch == '\n' && position != 0) {
            position = 0;
          }
        }
      }

      if (options->e) {
        if (ch == '\n') {
          fprintf(stdout, "$");
        }
      }
      if (options->t) {
        if (ch == '\t') {
          fprintf(stdout, "^");
          ch = 'I';
        }
      }
      if (options->v) {
        if ((ch >= 0 && ch < 9) || (ch >= 11 && ch <= 31)) {
          fprintf(stdout, "^");
          ch += 64;
        } else {
          if (ch == 127) {
            fprintf(stdout, "^");
            ch -= 64;
          }
        }
      }
      fprintf(stdout, "%c", ch);
    }
    fclose(fp);
  }
}