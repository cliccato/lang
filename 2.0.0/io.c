#include <stdlib.h>
#include <stdio.h>
#include "lib/io.h"


char* file_contents(const char* filepath) {
    char* buffer = 0;
    long len;

    FILE* f = fopen(filepath, "rb");

    if(f) {
        fseek(f, 0, SEEK_END);
        len = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = calloc(len, len);

        if(buffer) {
            fread(buffer, 1, len, f);
        }

        fclose(f);
        //printf("%s", buffer);
        return buffer;
    }

    printf("Errore il file %s non è leggibile o inesistente\n", filepath);
    exit(1);
}