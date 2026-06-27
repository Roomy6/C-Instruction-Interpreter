
/*
 * Basic File Interpreter
 * 
 * A basic instruction interpreter written
 * in pure C.
 *
 * By Roomy, code available on GitHub @Roomy6
 *
 * 27/06/2026 - 15:32
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER 1024

FILE* file;

int main(int argc, char* argv[])
{
    if(argc <= 1) { printf("Invalid args.\n"); return 1; }

    file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Cannor open file.\n");
        return 1;
    }

    char buffer[1024];
    int count = 0;

    while(fgets(buffer, sizeof(buffer), file))
    {
        count++;

        printf("%s\n", buffer);
    }

    fclose(file);
    return 1;
}
