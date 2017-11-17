#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void myftw(char *path) {
	struct stat type;
	struct dirent *dir;
	DIR *dirptr;
	char buf[225];

	if((dirptr = opendir(path)) == NULL) {
		printf("OPEN ERROR!\n");
		exit(-1);
	}	

	if(chdir(path)){
		perror("PATH ERROR!\n");	
		exit(-1);
	}

	while((dir = readdir(dirptr)) != NULL) {
		lstat(dir->d_name, &type);
		if(S_ISDIR(type.st_mode)){
			if(strcmp("..",dir->d_name) == 0 || strcmp(".",dir->d_name) == 0) {
				continue;
			}
			getcwd(buf,255);
			printf("%s/%s\t(DIRECTORY)\n", buf, dir->d_name);
			myftw(dir->d_name);
		} else {
			getcwd(buf,255);
			printf("%s/%s\t(FILE)\n", buf, dir->d_name);
		}
	}
	chdir("..");
}

int main(int argc, char *argv[]){
    if(argc != 2) {
        printf("You write Wrong\n");
        exit(0);
    }

    myftw(argv[1]);
    return 0;
}

