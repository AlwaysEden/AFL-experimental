#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 256
#define JSONFILE 1024
int main(){
	FILE *fp = fopen("haha.json", "r");
        if(fp == NULL){
                fprintf(stderr,"ERROR: file open\n");
                return 1;
        }
	char *total_func = NULL;
        char **func = NULL;
	char *target_path = NULL; 
	
	int func_cnt = 0;

	char line[LENGTH];
	char *tmp;
	while( (fgets(line, LENGTH, fp)) != NULL){
		if(line[0] == '{' || line[0] == '}') continue;
		tmp = strtok(line, " ");
		if(strcmp(tmp, "\t\"total_func\":") == 0){
			tmp = strtok(NULL,",");
			total_func = malloc(sizeof(char));
			memcpy(total_func, tmp, sizeof(char));
			func = malloc(sizeof(char) * atoi(total_func));
			printf("total_func: %s\n", total_func);
		}else if(strcmp(tmp, "\t\"func\":") == 0){
			if(total_func == NULL){
				fprintf(stderr, "ERROR: NO total_func\n");
				exit(1);
			}
			tmp = strtok(NULL, "\"");
			func[func_cnt] = malloc(sizeof(char)*LENGTH);
			memcpy(func[func_cnt], tmp, strlen(tmp));
			printf("func: %s\n",func[func_cnt]);
			func_cnt++;
			if(func_cnt >= 5){
				fprintf(stderr, "ERROR: Don't over 5 target function\n");
				exit(1);
			}
		}else if(strcmp(tmp, "\t\"target_path\":")==0){
			tmp = strtok(NULL, "\"");
			target_path = malloc(sizeof(char)*LENGTH);	
			memcpy(target_path, tmp, strlen(tmp));
			printf("target_path: %s\n", target_path);
		}else{
			fprintf(stderr,"ERROR: Check your JSON Format.\n");
			fprintf(stderr,"Example: \n");
			fprintf(stderr, "{\n");
			fprintf(stderr, "\t\"total_func\": 4,\n");
			fprintf(stderr, "\t\"func\": \"arrayValue1\",\n");
			fprintf(stderr, "\t\"func\": \"arrayValue2\",\n");
			fprintf(stderr, "\t\"func\": \"arrayValue3\",\n");
			fprintf(stderr, "\t\"func\": \"arrayValue4\",\n");
			fprintf(stderr, "\t\"target_path\": \"./haha\"\n");
			fprintf(stderr,"}\n");
			exit(1);
		}
	}	
	if(atoi(total_func) != func_cnt){
		fprintf(stderr, "ERROR: Not Match \"total_func\" and the number of \"func\"\n");
		exit(1);
	}
	if(total_func == NULL){
		fprintf(stderr, "ERROR: NO total_func\n");
		exit(1);
	}
	if(func == NULL){
		fprintf(stderr, "ERROR: No Func\n");
		exit(1);
	}
	if(target_path == NULL){
		fprintf(stderr, "ERROR: No target_path\n");
		exit(1);
	}
	fclose(fp);

	fp = fopen("parsed_json","w+");
	strcat(total_func, "\n");
	fwrite(total_func, 1, strlen(total_func),fp);
	for(int i = 0; i < func_cnt; i++){
		strcat(func[i], "\n");
		fwrite(func[i],1, strlen(func[i]),fp);
		free(func[i]);
	}
	fwrite(target_path, 1, strlen(target_path),fp);


	free(total_func);
	free(target_path);
}
