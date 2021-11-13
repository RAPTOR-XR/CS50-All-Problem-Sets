#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, h, spc, sym;
    
    do
    {
        height= get_int("Height: \n" );
    }
    while ( height>8 || height<=0 );
    
    for ( h=1; h<=height; h++)
    {
        for ( spc= (height-h); spc>0; spc--)
        {
            printf(" ");
        }
        
        for ( sym=1; sym<=h; sym++)
        {
            printf("#");
        }
        
        for( int s=h; s==h; s++)
        {
        printf("  ");
        }
    
        for ( int j=1; j<=h; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}