#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE* fp;
    char ch;
    if (argc > 1) {
        fp = fopen(argv[argc - 1], "r");
        if (fp == NULL) {
            fprintf(stderr, "%s: No such file or directory", argv[argc - 1]);
        }
        else {
            while ((ch = fgetc(fp)) != EOF)
            fprintf(stdout, "%c", ch);
        }
    }
    else {
        while ((ch = fgetc(stdin)) != EOF) {
        fprintf(stdout, "%c", ch);
        }
    }
    return 0;
}