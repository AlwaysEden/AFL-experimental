#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 256
#define MAX_JSON_LENGTH 1024

typedef enum {
    OBJECT,
    ARRAY,
    STRING,
    NUMBER
} ValueType;

typedef struct {
    char key[MAX_KEY_LENGTH];
    ValueType type;
    char value[MAX_VALUE_LENGTH];
    int arraySize;
    char** arrayValues;
} KeyValue;

void parseJson(char* json, KeyValue* kv) {
    char currentKey[MAX_KEY_LENGTH] = {0};
    char currentValue[MAX_VALUE_LENGTH] = {0};
    int inString = 0;
    int inKey = 1;
    int i = 0;
    int arrayIndex = 0;

    for (int j = 0; j < strlen(json); j++) {
        char c = json[j];

        if (c == '"') {
            inString =!inString;
        } else if (inString) {
            if (inKey) {
                strncat(currentKey, &c, 1);
            } else {
                strncat(currentValue, &c, 1);
            }
        } else {
            if (c == ':') {
                inKey = 0;
            } else if (c == ',') {
                if (currentValue[0]!= '\0') {
                    kv[i].key[0] = '\0';
                    strcpy(kv[i].key, currentKey);
                    kv[i].type = STRING;
                    kv[i].value[0] = '\0';
                    strcpy(kv[i].value, currentValue);
                    i++;
                }
                currentKey[0] = '\0';
                currentValue[0] = '\0';
                inKey = 1;
            } else if (c == '[') {
                kv[i].key[0] = '\0';
                strcpy(kv[i].key, currentKey);
                kv[i].type = ARRAY;
                kv[i].arraySize = 0;
                kv[i].arrayValues = (char**)malloc(sizeof(char*) * 10);
                inKey = 0;
            } else if (c == ']') {
                i++;
                currentKey[0] = '\0';
                currentValue[0] = '\0';
                inKey = 1;
            } else if (c == '{') {
                // Handle nested objects
            } else if (c == '}') {
                // Handle nested objects
            } else {
                if (inKey) {
                    strncat(currentKey, &c, 1);
                } else {
                    strncat(currentValue, &c, 1);
                }
            }
        }
    }

    if (currentValue[0]!= '\0') {
        kv[i].key[0] = '\0';
        strcpy(kv[i].key, currentKey);
        kv[i].type = STRING;
        kv[i].value[0] = '\0';
        strcpy(kv[i].value, currentValue);
        i++;
    }
}

void parseArray(char* json, KeyValue* kv, int i) {
    char currentValue[MAX_VALUE_LENGTH] = {0};
    int inString = 0;
    int j = 0;

    for (int k = 0; k < strlen(json); k++) {
        char c = json[k];

        if (c == '"') {
            inString =!inString;
        } else if (inString) {
            strncat(currentValue, &c, 1);
        } else {
            if (c == ',' || c == ']') {
                kv[i].arrayValues[kv[i].arraySize] = (char*)malloc(sizeof(char) * (strlen(currentValue) + 1));
                strcpy(kv[i].arrayValues[kv[i].arraySize], currentValue);
                kv[i].arraySize++;
                currentValue[0] = '\0';
            }
        }
    }
}

int main() {
	    FILE *fp = fopen("enhance.json", "r");
        if(fp == NULL){
                fprintf(stderr,"ERROR: file open\n");
                return 1;
        }
        char fileContent[MAX_JSON_LENGTH];
        fread(fileContent, 1, 1024, fp);
    KeyValue kv[10];
    parseJson(fileContent, kv);

    for (int i = 0; i < 3; i++) {
        if (kv[i].type == STRING) {
            printf("Key: %s, Value: %s\n", kv[i].key, kv[i].value);
        } else if (kv[i].type == ARRAY) {
            printf("Key: %s, Values: ", kv[i].key);
            for (int j = 0; j < kv[i].arraySize; j++) {
                printf("%s ", kv[i].arrayValues[j]);
            }
            printf("\n");
        }
    }

    return 0;
}
