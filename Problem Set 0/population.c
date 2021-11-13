#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i;
    do
    {
        i = get_int("Start size: ");
    }
    while (i<9);
    
    int j;
    do
    {
        j = get_int("End size: ");
    }
    while (j<i);
    
    int n=0;
    while (i<j)
    {
        i=i+(i/3)-(i/4);
        n++;
    }
    printf("Years: %i\n", n);
}