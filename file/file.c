#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"

int file_size(char * filename){
	struct stat statbuf;
	stat(filename,&statbuf);
	int size=statbuf.st_size;
	return size;
}

char * file_get_contents(char *filename){
	FILE * fp = fopen(filename,"r");
	if( fp == NULL ){
		printf("file %s is not exist!",filename);
		return "";
	}
	int size = file_size(filename);
	char * fileContent = malloc(size);
	fgets(fileContent,size,fp);
	fclose(fp);
	return fileContent;
}

void file_put_contents(char *filename,char *content){
	FILE * fp = fopen(filename,"w+");
	fputs(content,fp);
	fclose(fp);
}

int main(){
	char * filename = "1.txt";
	char * str = file_get_contents(filename);
	printf("%s",str);
	return 0;
}
