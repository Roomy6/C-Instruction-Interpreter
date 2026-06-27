
#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

#define MAX_INSTRUCTIONS 1024
#define MAX_TOKEN_LEN 64
#define HEX_DISPLAY 16

void addressPrint(long address)
{
    printf("%08lx: ", address);
}

int hexToAscii(size_t bytesRead, unsigned char buffer[HEX_DISPLAY])
{
    for(size_t i = 0; i < bytesRead; i++)
    {
        if(buffer[i] >= 32 && buffer[i] <= 126)
            printf("%c", buffer[i]);
        else
            printf(".");
    }

    return 0;
}

void printLine(unsigned char *buffer, size_t len, long address)
{
    addressPrint(address);
    
    for(size_t i = 0; i < len; i++)
    {
        printf("%02x ", buffer[i]);
    }
    
    /* Use DISPLAY_SIZE instead of hardocding :) */
    for(size_t i = len; i < HEX_DISPLAY; i++)
        printf("   ");

    printf(" |");
    hexToAscii(len, buffer);
    printf("|\n");
}

#endif // !HELPER_H
