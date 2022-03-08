#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

void PrintDir(char *dir)
{
    DIR *dirStream;
    if ((dirStream = opendir(dir)) == NULL)
    {
        perror("Can not open the dir");
        return;
    }
    struct dirent *curDir;
    while ((curDir = readdir(dirStream)) != NULL)
        printf("%s\n", curDir->d_name);

    if(closedir(dirStream) == -1)
        perror("Can not close the dir");
}

int main(int argc, char *argv[]) {
    char curDir[256];
    getcwd(curDir, 256);
    PrintDir(curDir);

    printf("\n\n\n/\n");
    PrintDir("/");
    return 0;
}