#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <types.h>
#include <stat.h>
#include <io.h>


int main(int argc, char *argv[]){

	if (argc != 3)
		perror("Enter three parameters: exe-file, copied file, file in which text is copied\n");
			
	FILE *fp;
	FILE *fd;
	int f1;
	int f2;
	char symbol;
	
	if (f1 = open(argv[1], O_RDONLY)){
	
		fp = fdopen(f1, "r");
		if (f2 = open(argv[2], O_WRONLY | O_CREAT, 0644)){
			fd = fdopen(f2, "w");
			
			while ((symbol = fgetc(fp)) != -1){	
				fputc(symbol, fd);
			}
		
		}
		else
		perror("Second file was not opened\n");
	}
	else
		perror("First file was not opened\n");
		
	//копирование режима доступа
	struct stat buff;
	if (fstat(f1, &buff) == 0){
		fchmod(f2, buff.st_mode);
	}
	else
		perror("Error\n");
	
	
	if (fclose(fp) != 0 || fclose(fd) != 0)
		perror("Could not close file\n");

	return 0;
}
