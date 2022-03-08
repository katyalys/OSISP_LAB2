#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	if (argc != 3)
		perror("Enter three parameters: exe-file, file which stores output strings, number of strings\n");
			
	FILE *fp;
	int f1;
	int N = 0;
	char str[300];
	

	//printf("%c\n", *(argv[2]));
	
	if (f1 = open(argv[1], O_RDONLY)){
	
		fp = fdopen(f1, "r");
		while (fgets(str, sizeof(str), fp) != NULL) {
			printf("%s", str);
			
			//if (atoi(argv[2]) !=0)
				N++;
			
			if ((N >= atoi(argv[2])) && (atoi(argv[2]) != 0)){
				fgetc(stdin);
				N = 0;
			}
		}
	}
	else
		perror("File was not opened\n");
	
	
	if (fclose(fp) != 0)
		perror("Could not close file\n");

	return 0;
}
