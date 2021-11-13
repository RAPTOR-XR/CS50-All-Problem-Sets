#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int arg, char *argi[])
{
    if (arg == 2 && strlen(argi[1]) == 26)
    {
        bool v = false;
        for (int i = 0; i < strlen(argi[1]); i++)
        {
            for (int j = i + 1; j < strlen(argi[1]) + 1; j++)
            {
                if (isalpha(argi[1][i]) && tolower(argi[1][i]) != tolower(argi[1][j]))
                {
                    v = true;
                }
                else
                {
                    printf("Usage: ./substitution key\n");
                    return 1;
                }
            }
        }
        string input = get_string("plaintext: ");
        for (int i = 0; i < strlen(input); i++)
        {
            if (islower(input[i]))
            {
                input[i] = tolower(argi[1][input[i] - 'a']);
            }
            else if (isupper(input[i]))
            {
                input[i] = toupper(argi[1][input[i] - 'A']);
            }
        }
        printf("ciphertext: %s\n", input);
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}