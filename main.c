
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
#include <stdbool.h>

#define MAX_INSTRUCTIONS 1024
#define MAX_TOKEN_LEN 64

typedef struct
{
    char name[MAX_TOKEN_LEN];
} Instruction;

/* Array to simulate the "compiled" program */
Instruction program[MAX_INSTRUCTIONS];
int instruction_count = 0;

int main(int argc, char* argv[])
{
    /* Check for valid arguments */
    if(argc <= 1) { printf("Invalid args.\n"); return 1; }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Error: cannot open file.\n");
        return 1;
    }

    int ch;
    bool in_comment = false;
    char token[MAX_TOKEN_LEN];
    int token_idx = 0;

    printf("--- COMPILING ---h\n");

    while((ch = fgetc(file)) != EOF)
    {
        if(!isspace(ch))
            printf("Char: '%c' | HEX: %02X\n", ch, (unsigned char)ch);

        if(ch == '[')
        {
            in_comment = true;
            continue;
        }
        if(ch == ']')
        {
            in_comment = false;
            continue;
        }

        if(in_comment)
            continue;

        if(isspace(ch))
        {
            if(token_idx > 0)
            {
                /* NULL terminate */
                token[token_idx] = '\0';

                /* Instruction validation */
                if(strcmp(token, "HELLO") == 0 || strcmp(token, "BYE") == 0)
                {
                    strcpy(program[instruction_count].name, token);
                    instruction_count++;
                } else
                {
                    printf("\nCOMPILE ERROR: Unknown instruction '%s'\n", token);
                    fclose(file);
                    return 1;
                }
                /* Reset for the next word */
                token_idx = 0;
            }
        } else
        {
            if(token_idx < MAX_TOKEN_LEN - 1)
                token[token_idx++] = ch;
        }
        
    }

    /* Check for instruction at EOF */
    if(token_idx > 0)
    {
        token[token_idx] = '\0';
        if(strcmp(token, "HELLO") == 0 || strcmp(token, "BYE") == 0)
        {
            strcpy(program[instruction_count++].name, token);
        } else
        {
            printf("\nCOMPILE ERROR: Unknown instruction '%s'\n", token);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    printf("COMPILATION SUCCESSFULL! %d instruction loaded.\n\n", instruction_count);

    printf("--- EXECUTING ---\n");

    /* Run the instructions */
    for(int i = 0; i < instruction_count; i++)
    {
        if(strcmp(program[i].name, "HELLO") == 0)
        {
            printf("Interpreter says: Hello\n");
        }
        else if(strcmp(program[i].name, "BYE") == 0)
        {
            printf("Interpreter says: Goodbye.\n");
            break;
        }
    }

    return 1;
}
