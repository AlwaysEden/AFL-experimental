#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	struct dirent *dirent;
	struct stat stat;
	char path[255];
	int a = 0;
	for(int i = 0; i < 5; i++){
	sprintf(path,"findings%d/default/queue",i);
	DIR *dir = opendir(path);

	int pipefd[2];

	char output[256];
	char testcase[512];
	char *content;
	FILE *fp;
	int ret;
	int pid;
	int status;
	int w;
	while( (dirent = readdir(dir)) != NULL ){
		if(strncmp(".", dirent->d_name, 1) == 0){
			continue;
		}
		sprintf(testcase,"findings%d/default/queue/%s",i,dirent->d_name);
		#ifdef DEBUG
			printf("testcase name: %s\n", testcase);
		#endif
		if(lstat(testcase, &stat) == -1){
			fprintf(stderr,"ERROR: stat\n");
			exit(1);
		}
		#ifdef DEBUG
			printf("testcase size: %d\n", stat.st_size);
		#endif
		content = malloc(sizeof(char) * stat.st_size);
		fp = fopen(testcase,"r");
		ret = fread(content, 1,stat.st_size, fp);
		#ifdef DEBUG
			printf("fread size: %d\n", ret);
		#endif

		if(ret != stat.st_size){
			fprintf(stderr, "ERROR: fread()\n");
			exit(1);
		}
			
		sprintf(output,"rawdata%d",a);
		a++;
		setenv("LLVM_PROFILE_FILE", output, 1);
		#ifdef DEBUG
			char *n;
			n = getenv("LLVM_PROFILE_FILE");
			printf("env name: %s\n",n);
		#endif
		//pipe(pipefd);
		pid = fork();
		if(pid == 0){
			//close(pipefd[1]);
			//dup2(pipefd[0],STDIN_FILENO);

			execl("./test","./test ", testcase, NULL);
		}else{
			//close(pipefd[0]);
			//write(pipefd[1], content, stat.st_size);
			//close(pipefd[1]);
			wait(NULL);
		}
		free(content);
		fclose(fp);
	}
	closedir(dir);
	}
		
}
