#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
} opt;

void parser(int argc, char* argv[], opt* options, char* search_mas);
void sw_flags(char ch, opt* options);
void chek_flage(char ch, char* argv, char* search_mas);
//void pater_e();
//void reader(int argc, char* argv[], opt* options);
//void cat_no_arguments();

int main(int argc, char* argv[]) {
  
  opt options = {0};
  char* search_mas = NULL;
  search_mas = realloc(search_mas, sizeof(char));
  printf("%d\n", argc);
  parser(argc, argv, &options, search_mas);
  printf("e = %d\n", options.e);
  printf("i = %d\n", options.i);
  printf("v = %d\n", options.v);
  printf("c = %d\n", options.c);
  printf("l = %d\n", options.l);
  printf("n = %d\n", options.n);
  //printf("optind = %d\n", optind);
  for (int i = 0; i < argc; i++)
    printf("%s ", argv[i]);
  //reader(argc, argv, &options);
  return 0;
}
void parser(int argc, char* argv[], opt* options, char* search_mas) {
    int count = 1;
    while (count < argc) {
        if (argv[count][0] == '-') {
            for (size_t i = 1; i < strlen(argv[count]); i++) {
                sw_flags(argv[count][i], options);
                chek_flage(argv[count][i], argv[count], search_mas);
                // if (strchr(s, argv[count][i]) != NULL) {
                //     mas[num_elem] = argv[count][i];
                //     num_elem++;
                // } else {
                //     fprintf(stderr, "invalid options\n");
                //     exit(1);
                // }
            }
            memset(argv[count], '\0', 1);
        }
        count++;
    }
}
void sw_flags(char ch, opt* options) {
  switch (ch)
  {
  case 'e':
    options->e = 1;
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
void chek_flage(char ch, char* argv, char* search_mas) {
  int len = strlen(argv);
  int num_error = 0;
  int flag_error = 0;
  ch = argv[1];
  (void)(search_mas);
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