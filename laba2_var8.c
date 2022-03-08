#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
#include<limits.h>//realpath
#include<libgen.h>//basename

char *AppName;
long double byt = 0;
long SumBlocks = 0;
long double sumResult = 0;
long int diskUsage = 0;

int ProcessFolder(char *curPath){
	DIR *curDir;
	curDir = opendir(curPath);
	if(curDir == NULL) {
		perror("Could not open directory");
		return -1;
	}

	struct dirent *dent;
	struct stat buf;
	char *file = alloca(strlen(curPath) + NAME_MAX + 2);
	long int sum = 0;
	long int blocks1 = 0;
	errno = 0;
	while(dent = readdir(curDir)){
		if(strcmp(".", dent->d_name) && strcmp("..", dent->d_name)){
			strcpy(file, curPath);
			strcat(file, "/");
 			strcat(file, dent->d_name);

			if (lstat(file,&buf) == -1) {
				fprintf(stderr,"%s: %s: %s\n", AppName, curPath, strerror(errno));
				return -1;
			}

			if(!S_ISDIR(buf.st_mode)){
				sum+=buf.st_size;  // суммарный размер файлов

				blocks1+=(buf.st_blocks * 512);  //суммарный размер занимаего файлами на диске пространства 
			}

			if(S_ISDIR(buf.st_mode)){
				ProcessFolder(file);
			}
		}
	}

	printf("%s %ld %ld\n", curPath, sum, blocks1);

	SumBlocks = SumBlocks + blocks1;
	sumResult += sum;
	diskUsage = (sumResult / SumBlocks) * 100;

	if(closedir(curDir)==-1){
		perror("Couldnot close file");
		return -1;
	}
	return 0;
}

int main(int argc, char **argv){
	AppName = alloca(strlen(basename(argv[0])));
	strcpy(AppName, basename(argv[0]));
	if(argc<2){
		fprintf(stderr, "%s:  Enter valid number of arguments: 1 - exe-file, 2 - directory.\n", AppName);
		return -1;
	}
	
	if(realpath(argv[1], NULL) == NULL) {
		fprintf(stderr,"%s: %s: %s\n", AppName, argv[1], strerror(errno));
		return -1;
	}
	
	ProcessFolder(realpath(argv[1], NULL));
	
	fprintf(stderr,"Disk usage is %Lf\n", (sumResult / SumBlocks)*100);
	return 0;
}