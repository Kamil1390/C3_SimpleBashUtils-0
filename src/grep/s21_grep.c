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

void parser(int argc, char* argv[], opt* options);
//void reader(int argc, char* argv[], opt* options);
//void cat_no_arguments();

int main(int argc, char* argv[]) {
  
  opt options = {0};
  printf("%d\n", argc);
  parser(argc, argv, &options);
  printf("e = %d\n", options.e);
  printf("i = %d\n", options.i);
  printf("v = %d\n", options.v);
  printf("c = %d\n", options.c);
  printf("l = %d\n", options.l);
  printf("n = %d\n", options.n);
  printf("optind = %d\n", optind);
  for (int i = 0; i < argc; i++)
    printf("%s ", argv[i]);
  //reader(argc, argv, &options);
  return 0;
}
void parser(int argc, char* argv[], opt* options) {
    char mas[10];
    int num_elem = 0;
    int count = 1;
    const char* s = "eivcln";
    while (count < argc) {
        if (argv[count][0] == '-') {
            for (int i = 1; i < strlen(argv[count]); i++) {
                if (strchr(s, argv[count][i]) != NULL) {
                    mas[num_elem] = argv[count][i];
                    num_elem++;
                    memset(argv[count], '\0', 1);
                } else {
                    fprintf(stderr, "invalid options\n");
                    exit(1);
                }
            }
        }
        count++;
    }
    for (int i = 0; i < num_elem; i++) {
         if (mas[i] == 'e') options->e = 1;
         if (mas[i] == 'i') options->i = 1;
         if (mas[i] == 'v') options->v = 1;
         if (mas[i] == 'c') options->c = 1;
         if (mas[i] == 'l') options->l = 1;
         if (mas[i] == 'n') options->n = 1;
    }
}