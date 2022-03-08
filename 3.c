#include <stdio.h>
#include <fcntl.h>


int main(int argc, char *argv[]){

	if (argc != 2)
		perror("Enter two parameters: exe-file, output file");
			
	FILE *fp;
	int f1;
	char exit = 'q'; // символ окончания ввода
	char symb;
	
	if (f1 = open(argv[1], O_WRONLY | O_CREAT, 0644)){
	
		fp = fdopen(f1, "w");
		while ((symb = getchar()) != exit){
		
			if (putc(symb, fp) == EOF)
				perror("File output error\n");
		}
	}
	else
		perror("File was not opened\n");
	
	
	if (fclose(fp) != 0)
		perror("Could not close file\n");

	return 0;
}
