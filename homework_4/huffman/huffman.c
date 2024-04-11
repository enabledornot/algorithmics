#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <filename>\n",argv[0]);
    }
    FILE* file = fopen(argv[1],"r");

    if(file == NULL) {
        printf("Error opening file %s\n",argv[1]);
        return 1;
    }
    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c",c);
    }
    fclose(file);

    return 0;
}