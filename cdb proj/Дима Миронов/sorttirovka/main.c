#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void merge();

void convertString(char *str) {
    while (*str != '\n' && *str != '\0')
        ++str;

    *str = '\0';
}

void sorting(char *file) {
    FILE *f = NULL, *outf1, *outf2;
    int flag = 1, c, isEnd = 1;
    char str1[128], str2[128];

    f = fopen(file, "r");
    outf1 = fopen("file1.txt","w");
    outf2 = fopen("file2.txt","w");

    fgets(str1, 127, f);

    while (fgets(str2, 127, f)) {
        c = strcmp(str2, str1);
        //printf("%d",c);
        FILE *cf = flag ? outf1: outf2;

        fputs(str1, cf);

        if (c < 0) {
            fputs("*\n", cf);
            isEnd = 0;
            flag = 1 - flag;
        }
        strcpy(str1, str2);
    }
    convertString(str1);
    fputs(str1, flag ? outf1: outf2);
    fputs("\n*\n", flag ? outf1: outf2);
    fclose(outf1);
    fclose(outf2);
    fclose(f);
    if (!isEnd)
        merge();
}

void merge() {
    FILE *f1,*f2,*outf;
    f1=fopen("file1.txt", "r");
    f2=fopen("file2.txt", "r");
    outf=fopen("out.txt","w");
    char str1[128], str2[128];

    fgets(str1,128,f1);
    fgets(str2,128,f2);
    while (!feof(f2)) {
        if (strcmp(str2,"*\n")!=0 && strcmp(str1,"*\n")!=0) {
            if (strcmp(str2,str1) >= 0) {
                fputs(str1,outf);
                fgets(str1,128,f1);
            } else {
                fputs(str2,outf);
                fgets(str2,128,f2);
            }
        } else {
            while (strcmp(str1,"*\n")!=0) {
                fputs(str1,outf);
                fgets(str1,128,f1);
            }
            while (strcmp(str2,"*\n")!=0) {
                fputs(str2,outf);
                fgets(str2,128,f2);
            }
            fgets(str1,128,f1);
            fgets(str2,128,f2);
        }
    }
    while (!feof(f1)) {
        if (strcmp(str1,"*\n")!=0)
            fputs(str1,outf);
        fgets(str1,127, f1);
    }
    fclose(f1);
    fclose(f2);
    fclose(outf);
    sorting("out.txt");
}

int main(){
    sorting("films.txt");
    return 0;
}
