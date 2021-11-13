#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Raw file not found\n");
        return 1;
    }
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    size_t byteR;
    bool fJPEG = false;
    char fname[70];
    FILE *curfile;
    int cfilenumber = 0;
    bool found = false;
    
    while (true)
    {
        byteR = fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);
        if (byteR == 0)
        {
            break;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found = true;
            if (!fJPEG)
            {
                fJPEG = true;
            }
            else
            {
                fclose(curfile);
            }
            sprintf(fname, "%03i.jpg", cfilenumber);
            curfile = fopen(fname, "w");
            fwrite(buffer, sizeof(BYTE), byteR, curfile);
            cfilenumber++;
        }
        else
        {
            if (found)
            {
                fwrite(buffer, sizeof(BYTE), byteR, curfile);
            }
        }
    }
    fclose(file);
    fclose(curfile);
    return 0;
}
