#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE p = image[i][j];
            int a = round((p.rgbtBlue + p.rgbtGreen + p.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtRed = a;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        int cp = 0;
        for (int j = width - 1; j >= 0; j--, cp++)
        {
            temp[i][cp] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float tR = 0;
            float tG = 0;
            float tB = 0;
            int xc[] = {i - 1, i, i + 1};
            int yc[] = {j - 1, j, j + 1};
            
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int cr = xc[x];
                    int cc = yc[y];
            
                    if (cr >= 0 && cr < height && cc >= 0 && cc < width)
                    {
                        RGBTRIPLE p = image[cr][cc];
                        tR += p.rgbtRed;
                        tG += p.rgbtGreen;
                        tB += p.rgbtBlue;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtRed = round(tR / count);
            temp[i][j].rgbtGreen = round(tG / count);
            temp[i][j].rgbtBlue = round(tB / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxR = 0;
            float GxG = 0;
            float GxB = 0;
            float GyR = 0;
            float GyG = 0;
            float GyB = 0;
            int xc[] = {i - 1, i, i + 1};
            int yc[] = {j - 1, j, j + 1};
            
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int cr = xc[x];
                    int cc = yc[y];
            
                    if (cr >= 0 && cr < height && cc >= 0 && cc < width)
                    {
                        RGBTRIPLE p = image[cr][cc];
                        GxR += Gx[x][y] * p.rgbtRed;
                        GxG += Gx[x][y] * p.rgbtGreen;
                        GxB += Gx[x][y] * p.rgbtBlue;
                        
                        GyR += Gy[x][y] * p.rgbtRed;
                        GyG += Gy[x][y] * p.rgbtGreen;
                        GyB += Gy[x][y] * p.rgbtBlue;
                    }
                }
            }
            int red = round(sqrt(GxR * GxR + GyR * GyR));
            int green = round(sqrt(GxG * GxG + GyG * GyG));
            int blue = round(sqrt(GxB * GxB + GyB * GyB));
            
            temp[i][j].rgbtRed = red > 255 ? 255 : red;
            temp[i][j].rgbtGreen = green > 255 ? 255 : green;
            temp[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
