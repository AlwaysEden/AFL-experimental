#include <stdio.h>
#include <string.h>

#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 256
#define MAX_JSON_LENGTH 1024

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} KeyValue;

void parseJson(char* json, KeyValue* kv) {
    char currentKey[MAX_KEY_LENGTH] = {0};
    char currentValue[MAX_VALUE_LENGTH] = {0};
    int inString = 0;
    int inKey = 1;
    int i = 0;

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
                kv[i].key[0] = '\0';
                strcpy(kv[i].key, currentKey);
                kv[i].value[0] = '\0';
                strcpy(kv[i].value, currentValue);
                i++;
                currentKey[0] = '\0';
                currentValue[0] = '\0';
                inKey = 1;
            }
        }
    }

    kv[i].key[0] = '\0';
    strcpy(kv[i].key, currentKey);
    kv[i].value[0] = '\0';
    strcpy(kv[i].value, currentValue);
}

int main() {
    KeyValue kv[10];
    FILE *fp = fopen("enhance.json", "r");
        if(fp == NULL){
                fprintf(stderr,"ERROR: file open\n");
                return 1;
        }
        char fileContent[MAX_JSON_LENGTH];
        fread(fileContent, 1, 1024, fp);
    parseJson(fileContent, kv);

    for (int i = 0; i < 3; i++) {
        printf("Key: %s, Value: %s\n", kv[i].key, kv[i].value);
    }

    return 0;
}
