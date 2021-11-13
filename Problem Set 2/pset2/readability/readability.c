#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int letter_count(string text);
int word_count(string text);
int sentence_count(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("%s\n", text);
    double L, S;
    int index;
    int letter = letter_count(text);
    int word = word_count(text);
    int sen = sentence_count(text);
    L = (letter * 100.0f) / word;
    S = (sen * 100.0f) / word;
    index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int letter_count(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            count++;
        }
    }
    return count;
}

int word_count(string text)
{
    int count = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char c = text[i];
        if (isspace(c))
        {
            count++;
        }
    }
    return count;
}

int sentence_count(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char c = text[i];
        if (c == '.')
        {
            count++;
        }
        else if (c == '!')
        {
            count++;
        }
        else if (c == '?')
        {
            count++;
        }
    }
    return count;
}