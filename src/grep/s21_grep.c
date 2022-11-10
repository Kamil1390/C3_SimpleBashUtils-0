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
  int h;
  int s;
  int f;
  int o;
} opt;

int preliminary_search(char* argv[], int argc);
void parser(int argc, char* argv[], opt* options, char search_mas[][strlong], int* index);
void short_parser(char* argv[], char search_mas[][strlong], int* index);
void creat_fmas(int argc, char* argv[], int* index_file, char file_mas[][strlong]);
void sw_flags(char ch, char* argv[], opt* options, int count, char search_mas[][strlong], int* index, int argc);
void chek_flags(char ch, char* argv);
void pattern_e(char* argv[], int number, char search_mas[][strlong], int* index, int argc);
void pattern_f(char* argv[], int number, char search_mas[][strlong], int* index, int argc);
void search_pattern(char* argv[], int count, char search_mas[][strlong], int* index, int* cfe, int argc);
void reader(int index_file, char file_mas[][strlong], opt* options, char search_mas[][strlong], int index);
void reg (regex_t myreg, opt* options, char* string, char* pattern, int* count_line);
void func_v(int* count_line);
void func_lc(int count_line, int* count_string);
void output(char* file_mas, int index_file, char* string, int num_line, opt* options);
void output_lc(opt* options, int count_string, char* file_mas, int index_file);
void new_line(char* string, int current_file, int index_file, int flag_c, int flag_l, int count_line);

int main(int argc, char* argv[]) {
  
  opt options = {0};
  char search_mas[strlong][strlong] = {{' '}};
  char file_mas[strlong][strlong] = {{' '}};
  int index = 0;
  int index_file = 0;

  if (preliminary_search(argv, argc) == 0)
    short_parser(argv, search_mas,  &index); 
  else 
    parser(argc, argv, &options, search_mas, &index);
  creat_fmas(argc, argv, &index_file, file_mas);
  // printf("index = %d\nindex_file = %d\n", index, index_file);
  reader(index_file, file_mas, &options, search_mas, index);
  // printf("\ne = %d\n", options.e);
  // printf("i = %d\n", options.i);
  // printf("v = %d\n", options.v);
  // printf("c = %d\n", options.c);
  // printf("l = %d\n", options.l);
  // printf("n = %d\n", options.n);
  // printf("h = %d\n", options.h);
  // printf("s = %d\n", options.s);
  // printf("f = %d\n", options.f);
  // for (int i = 0; i < index_file; i++)
  //   printf("fiel_mas [%d] %s\n", i, file_mas[i]);
  // for (int i = 0; i < index; i++) {
  //   printf("search_mas [%d] %s\n", i, search_mas[i]);
  // }
  // for (int i = 0; i < argc; i++)
  //   printf("%s ", argv[i]);
  
  return 0;
}
int preliminary_search(char* argv[], int argc) {
  int count = 0;
  int num = 1;
  while (num < argc) {
    if (argv[num][0] == '-') {
      count++;
    }
    num++;
  }
  if (count > 0)
    return 1;
  else
    return 0;  
}
void creat_fmas(int argc, char* argv[], int* index_file, char file_mas[][strlong]) {
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] != '\0') {
      strcpy(file_mas[*index_file], argv[i]);
      *index_file += 1;
    }
  }
}
void parser(int argc, char* argv[], opt* options, char search_mas[][strlong], int* index) {
    int count = 1;
    int cfe = 0;
    while (count < argc) {
        if (argv[count][0] == '-') {
            for (size_t i = 1; i < strlen(argv[count]); i++) {
                if (argv[count][i] == 'e' || argv[count][i] == 'f') 
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
  case 'h':
    options->h = 1;
    break;
  case 's':
    options->s = 1;
    break;
  case 'f':
    options->f = 1;
    pattern_f(argv, count, search_mas, index, argc);
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
        break;
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
void pattern_f(char* argv[], int number, char search_mas[][strlong], int* index, int argc) {
  FILE* fp = NULL;
  int k = 0;
  int len = 0;
  char string[1024] = "";
  for (size_t i = 1; i < strlen(argv[number]); i++) {
    if (argv[number][i] == 'f' && argv[number][i + 1] == '\0' && number == argc - 1) {
      fprintf(stderr, "option requires an argument -- f\n");
      exit(1);
    } else {
        if (argv[number][i] == 'f') {
          k = i;
          break;
        }
    }
  }
  if (argv[number][k + 1] == '\0') {
    fp = fopen(argv[number + 1], "r");
    if (fp == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
              argv[number + 1]);
      exit(1);
    } 
    while (fgets (string, 1024, fp) != NULL) {
      len = strlen(string);
      if (string[len - 1] == '\n' && len > 1) {
        string[len - 1] = '\0';
      }
      strcpy(search_mas[*index], string);
      *index += 1;
    }
    memset(argv[number + 1], '\0', strlen(argv[number + 1]));
    memset(argv[number], '\0', strlen(argv[number]));
    fclose(fp);
  } else {
    int m = 0;
    int l = k + 1;
    while (argv[number][l] != '\0') {
      string[m] = argv[number][l];
      m++;
      l++;
    }
    fp = fopen(string, "r");
    if (fp == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
              string);
      exit(1);
    }
    while (fgets (string, 1024, fp) != NULL) {
      len = strlen(string);
      if (string[len - 1] == '\n' && len > 1) {
        string[len - 1] = '\0';
      }
      strcpy(search_mas[*index], string);
      *index += 1;
    }
    memset(argv[number], '\0', strlen(argv[number]));
    fclose(fp);
  }
}
void search_pattern(char* argv[], int count, char search_mas[][strlong], int* index, int* cfe, int argc) {
  if (*cfe == 0 && ((argv[1][0] != '-') && (argv[1][0] != '\0')) && (count)) {
    strcpy(search_mas[*index], argv[1]);
    *index += 1;
    *cfe += 1; 
    memset(argv[1], '\0', strlen(argv[1]));
   }
  if (*cfe == 0 && ((argv[1][0] != '-') && (argv[1][0] != '\0')) && (count)) {
    strcpy(search_mas[*index], argv[count - 1]);
    *index += 1;
    *cfe += 1; 
    memset(argv[1], '\0', strlen(argv[count - 1]));
   }

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
  int rez = 0;
  regex_t myreg;
  int count_line = 0;
  int current_File = 1;
  int current_Pattern = 0;
  char string[1024];
  FILE* fp;

  while (current_File < index_file) {
    fp = fopen(file_mas[current_File], "r");
    current_File++;
    int num_line = 1;
    if (fp == NULL) {
      if (!options->s) {
        fprintf(stderr, "%s: %s: No such file or directory\n", file_mas[0],
              file_mas[current_File - 1]);
      }
      continue;
    }
    int count_string = 0;
    while (fgets (string, 1024, fp) != NULL) {
      count_line = 0;
      for (int i = 0; i < index && count_line == 0; i++) {
          reg(myreg, options, string, search_mas[i], &count_line);
      }
      if (options->v) {
        func_v(&count_line);
      }
      if (options->c || options->l) {
        func_lc(count_line, &count_string);
      }
      // printf("count_line = %d \n", count_line);
      // printf("%s", string);
      if (count_line > 0 && !options->c && !options->l) {
        output(file_mas[current_File - 1], index_file, string, num_line, options);
      }
      num_line++;
    }
    if (options->c || options->l) {
      output_lc(options, count_string, file_mas[current_File - 1], index_file);
    }
    //new_line(string, current_File - 1, index_file, options->c, options->l, count_line);
    fclose(fp);
  }
}
void reg(regex_t myreg, opt* options, char* string, char* pattern, int* count_line) {
  int rez = 0;
  if (strcmp(pattern, ".") == 0) {
    rez = regcomp(&myreg, pattern, REG_NEWLINE);
  } else {
    rez = regcomp(&myreg, pattern, options->i ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);
  }
  if (rez == 0) {
        if ((regexec(&myreg, string, 0, NULL, 0) == 0)) {
            *count_line = 1;
        }
      }
  regfree(&myreg);
}
void func_v(int* count_line) {
  if (*count_line == 1) {
    *count_line = 0;
  } else {
    *count_line = 1;
  }
}
void func_lc(int count_line, int* count_string) {
  if (count_line == 1) {
    *count_string += 1;
  }
}
void output(char* file_mas, int index_file, char* string, int num_line, opt* options) {
  int len = strlen(string);
  if (options->h) {
    index_file = 2;
  }
  if (options->n) {
    if (index_file == 2) {
      printf("%d:%s", num_line, string);
    }
    if (index_file > 2) {
      printf("%s:%d:%s", file_mas, num_line, string);
    }
    if (string[len - 1] != '\n') {
      printf("\n");
    }
  } else {
    if (index_file == 2) {
      printf("%s", string);
    }
    if (index_file > 2) {
      printf("%s:%s", file_mas, string);
    }
    if (string[len - 1] != '\n') {
      printf("\n");
    } 
  }
}
void output_lc(opt* options, int count_string, char* file_mas, int index_file) {
  if (options->h) {
    index_file = 2;
  }
  if (options->c && options->l) {
    if (count_string > 0) {
        count_string = 1;
      }
  }
  if (options->c) {
    if (index_file == 2) {
      printf("%d\n", count_string);
    }
      if (index_file > 2) {
      printf("%s:%d\n", file_mas, count_string);
    } 
  }
  if (options->l && count_string > 0) {
    printf("%s\n", file_mas);
  }
}
void new_line(char* string, int current_file, int index_file, int flag_c, int flag_l, int count_line) {
  if (string[strlen(string)] != '\n' && count_line && !flag_c && !flag_l)
    printf("\n");
}
