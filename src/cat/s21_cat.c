#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

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

int main(int argc, char *argv[]) {
    // FILE* fp;
    // char ch;
    // if (argc > 1) {
    //     fp = fopen(argv[argc - 1], "r");
    //     if (fp == NULL) {
    //         fprintf(stderr, "%s: No such file or directory", argv[argc - 1]);
    //     }
    //     else {
    //         while ((ch = fgetc(fp)) != EOF)
    //         fprintf(stdout, "%c", ch);
    //     }
    // }
    // else {
    //     while ((ch = fgetc(stdin)) != EOF) {
    //     fprintf(stdout, "%c", ch);
    //     }
    // }
    if (argc == 1)
        cat_no_arguments();
    opt options = {0};
    parser(argc, argv, &options);
    // printf("b = %d\n", options.b);
    // printf("e = %d\n", options.e);
    // printf("n = %d\n", options.n);
    // printf("s = %d\n", options.s);
    // printf("t = %d\n", options.t);
    // printf("v = %d\n", options.v);
    // printf("optind = %d\n", optind);
    // printf("argc = %d\n", argc);
    reader(argc, argv, &options);
    return 0;
}
void parser(int argc, char* argv[], opt* options) {
    int flag;
    const struct option long_option[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'},
        { NULL, no_argument, NULL, 0}
    };
    while ((flag = getopt_long(argc, argv, "+benstvTE", 
        long_option, NULL)) != -1) {
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
    while ((ch = getc(stdin)) != EOF)
        fprintf(stdout, "%c", ch);
}

void reader(int argc, char* argv[], opt* options) {
    int currentFile = optind;
    FILE* fp;
    char ch;

    while (currentFile < argc) {
        if (currentFile != argc) {
            fp = fopen(argv[currentFile], "r");
            if (fp == NULL) {
                fprintf(stderr, "%s: %s: No such file or directory",
                    argv[0], argv[currentFile]);
                exit(1);
            }
        }

        int lineNumber = 1;
        int position = 0;
        while ((ch = fgetc(fp)) != EOF) {
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
            fprintf(stdout, "%c", ch);
        }
        fclose(fp);
        currentFile++;
    }
}