#include <getopt.h>
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
void sw_flags(char ch, char* argv[], opt* options, int count, char searh_mas[][strlong], int* index, int argc);
void chek_flags(char ch, char* argv);
void pattern_e(char* argv[], int number, char search_mas[][strlong], int* index, int argc);
void search_pattern(char* argv[], int count, char search_mas[][strlong], int* index);
//void reader(int argc, char* argv[], opt* options);
//void cat_no_arguments();

int main(int argc, char* argv[]) {
  
  opt options = {0};
  char search_mas[strlong][strlong] = {{' '}};
  //char file_mas[strlong][strlong] = {{' '}};
  int index = 0;
  printf("%d\n", argc);
  parser(argc, argv, &options, search_mas, &index);
  printf("e = %d\n", options.e);
  printf("i = %d\n", options.i);
  printf("v = %d\n", options.v);
  printf("c = %d\n", options.c);
  printf("l = %d\n", options.l);
  printf("n = %d\n", options.n);
  for (int i = 0; i < index; i++) {
    printf("search_mas [%d] %s\n", i, search_mas[i]);
  }
  //printf("optind = %d\n", optind);
  for (int i = 0; i < argc; i++)
    printf("%s ", argv[i]);
  //reader(argc, argv, &options);
  return 0;
}
void parser(int argc, char* argv[], opt* options, char search_mas[][strlong], int* index) {
    int count = 1;
    while (count < argc) {
        if (argv[count][0] == '-') {
            for (size_t i = 1; i < strlen(argv[count]); i++) {
                sw_flags(argv[count][i], argv, options, count, search_mas, index, argc);
                chek_flags(argv[count][i], argv[count]);
            }
            search_pattern(argv, count, search_mas, index);
            memset(argv[count], '\0', 1);  
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
void search_pattern(char* argv[], int count, char search_mas[][strlong], int* index) {
  if (*index == 0) {
    strcpy(search_mas[*index], argv[count + 1]);
    *index += 1;
    memset(argv[count + 1], '\0', strlen(argv[count + 1]));
   }
}