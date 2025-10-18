#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define LOG_FILE "data\\logs.txt"

FILE* safeOpenFile(const char* filename,const char* mode){
    FILE* fp = fopen(filename,mode);
    if(fp==NULL){
        fp=fopen(filename,"w+");
        if(fp==NULL){
            printf("Cannot open or create file: %s\n",filename);
            exit(1);
        }
    }
    return fp;
}

void logAction(const char *message){
    FILE *fp = safeOpenFile(LOG_FILE,"a+");
    fprintf(fp,"%s\n",message);
    fclose(fp);
}
