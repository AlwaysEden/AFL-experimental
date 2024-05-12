#include <stdio.h>
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>


#define JSONFILE 1024
#define FUNC_MAX 10
#define LENGTH 128

int main(){
	int numberOfFunc = 0;
	char *func[FUNC_MAX];
	char binary_path[256];

	FILE *fp = fopen("enhance.json", "r");
	if(fp == NULL){
		fprintf(stderr,"ERROR: file open\n");
		return 1;
	}
	char fileContent[JSONFILE];
	fread(fileContent, 1, JSONFILE, fp);
	
	cJSON* root;
	root = cJSON_Parse(fileContent);
	if(root == NULL || root->child == NULL){
		printf("JSON parsing error: %s\n", cJSON_GetErrorPtr());
                return 1;
	}
	cJSON* total_func = cJSON_GetObjectItem(root,"total_func");
	if(total_func== NULL || total_func->valueint <= 0 || total_func->valueint > FUNC_MAX){
                fprintf(stderr, "ERROR: total_func\n");
                return 1;
        }
	numberOfFunc = total_func->valueint;
	
	printf("total_func: %d\n", numberOfFunc);

	cJSON* name_func = cJSON_GetObjectItem(root, "name_func");
	int count_func = cJSON_GetArraySize(name_func);
	if( count_func != numberOfFunc){
		fprintf(stderr, "ERROR: not match Function count\n");
		return 1;
	}

	for(int i = 0; i < numberOfFunc; i++){
		func[i] = malloc(sizeof(char) * LENGTH);
		cJSON* func_array = cJSON_GetArrayItem(name_func, i);
		if(func_array == NULL){
			fprintf(stderr, "ERROR: func_array\n");
			return 1;
		}
		memcpy(func[i], func_array->valuestring, strlen(func_array->valuestring));
		printf("func_name: %s\n", func[i]);

	}

	cJSON* target_path = cJSON_GetObjectItem(root, "target_path");
	if(target_path == NULL || strlen(target_path->valuestring) > 256){
		fprintf(stderr, "ERROR: target_path\n");
		return 1;
	}
	
	memcpy(binary_path, target_path->valuestring, strlen(target_path->valuestring));
	printf("path: %s\n", binary_path);
	



}
