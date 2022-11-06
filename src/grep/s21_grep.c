#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strlong 1024

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
} opt;

void parser(int argc, char* argv[], opt* options, char search_mas[][strlong], int* index);
void short_parser(char* argv[], char search_mas[][strlong], int* index);
void sw_flags(char ch, char* argv[], opt* options, int count, char search_mas[][strlong], int* index, int argc);
void chek_flags(char ch, char* argv);
void pattern_e(char* argv[], int number, char search_mas[][strlong], int* index, int argc);
void search_pattern(char* argv[], int count, char search_mas[][strlong], int* index, int* cfe, int argc);
void reader(int index_file, char file_mas[][strlong], opt* options, char search_mas[][strlong], int index);
//void cat_no_arguments();

int main(int argc, char* argv[]) {
  
  opt options = {0};
  char search_mas[strlong][strlong] = {{' '}};
  char file_mas[strlong][strlong] = {{' '}};
  int index = 0;
  int index_file = 0;

  if (argc == 3 && argv[1][0] != '-')
    short_parser(argv, search_mas,  &index);
  else 
    parser(argc, argv, &options, search_mas, &index);
    for (int i = 0; i < argc; i++) {
    if (argv[i][0] != '\0') {
      strcpy(file_mas[index_file], argv[i]);
      index_file++;
    }
  }
  reader(index_file, file_mas, &options, search_mas, index);
  // printf("e = %d\n", options.e);
  // printf("i = %d\n", options.i);
  // printf("v = %d\n", options.v);
  // printf("c = %d\n", options.c);
  // printf("l = %d\n", options.l);
  // printf("n = %d\n", options.n);
  
  // for (int i = 0; i < index_file; i++)
  //   printf("fiel_mas [%d] %s\n", i, file_mas[i]);
  // for (int i = 0; i < index; i++) {
  //   printf("search_mas [%d] %s\n", i, search_mas[i]);
  // }
  // for (int i = 0; i < argc; i++)
  //   printf("%s ", argv[i]);
  
  return 0;
}
void parser(int argc, char* argv[], opt* options, char search_mas[][strlong], int* index) {
    int count = 1;
    int cfe = 0;
    while (count < argc) {
        if (argv[count][0] == '-') {
            for (size_t i = 1; i < strlen(argv[count]); i++) {
                if (argv[count][i] == 'e') 
                  cfe++;
                sw_flags(argv[count][i], argv, options, count, search_mas, index, argc);
                chek_flags(argv[count][i], argv[count]);
            } 
        }
        count++;
    }
    count = 1;
    while (count < argc) {
      if (argv[count][0] == '-') {
        search_pattern(argv, count, search_mas, index, &cfe, argc);
        memset(argv[count], '\0', strlen(argv[count]));
      }
      count++;
    }
}
void sw_flags(char ch, char* argv[], opt* options, int count, char search_mas[][strlong], int* index, int argc) {
  switch (ch)
  {
  case 'e':
    options->e = 1;
    pattern_e(argv, count, search_mas, index, argc);
    break;
  case 'i':
    options->i = 1;
    break;
  case 'v':
    options->v = 1;
    break;
  case 'c':
    options->c = 1;
    break;
  case 'l':
    options->l = 1;
    break;
  case 'n':
    options->n = 1;
    break;
  default:
    printf("invalid options\n");
    break;
  }
}
void chek_flags(char ch, char* argv) {
  int len = strlen(argv);
  int num_error = 0;
  int flag_error = 0;
  ch = argv[1];
  for (int i = 1; i < len; i++) {
    if (argv[i] == '-' && ch != 'e') {
      num_error = i;
      flag_error = 1;
      break;
    }
  }
  if (flag_error == 1) {
    printf("unrecognized option -");
    for (int i = num_error; i < len; i++) {
      printf("%c", argv[i]);
    }
    exit(1);
  }
}
void pattern_e(char* argv[], int number, char search_mas[][strlong], int* index, int argc) {
  int k = 0;
  for (size_t i = 1; i < strlen(argv[number]); i++) {
    if (argv[number][i] == 'e' && argv[number][i + 1] == '\0' && number == argc - 1) {
      fprintf(stderr, "option requires an argument -- e\n");
      exit(1);
    } else {
        if (argv[number][i] == 'e') {
        k = i;
      } 
    }
  }
  if (argv[number][k + 1] == '\0') {
    strcpy(search_mas[*index], argv[number + 1]);
    memset(argv[number + 1], '\0', strlen(argv[number + 1]));
    memset(argv[number], '\0', strlen(argv[number]));
    *index += 1;
  } else {
    int m = 0;
    int l = k + 1;
    while (argv[number][l] != '\0') {
      search_mas[*index][m] = argv[number][l];
      m++;
      l++;
    }
    memset(argv[number], '\0', strlen(argv[number]));
    *index += 1;
  }
}
void search_pattern(char* argv[], int count, char search_mas[][strlong], int* index, int* cfe, int argc) {
  if (*cfe == 0 && ((argv[count + 1][0] != '-') && (count != argc - 2))) {
    strcpy(search_mas[*index], argv[count + 1]);
    *index += 1;
    *cfe += 1; 
    memset(argv[count + 1], '\0', strlen(argv[count + 1]));
   }
}
void short_parser(char* argv[], char search_mas[][strlong], int* index) {
  strcpy(search_mas[*index], argv[1]);
  memset(argv[1], '\0', strlen(argv[1]));
  *index += 1;
}
void reader(int index_file, char file_mas[][strlong], opt* options, char search_mas[][strlong], int index) {
  int current_File = 1;
  int current_Pattern = 0;
  FILE* fp;

  while (current_File < index_file) {
    fp = fopen(file_mas[current_File], "r");
    current_File++;
    if (fp == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", file_mas[0],
              file_mas[current_File - 1]);
      continue;
    }
    // while () {

    // }
    fclose(fp);
  }
}