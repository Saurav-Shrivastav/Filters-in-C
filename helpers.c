#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round(((double) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int nb, ng, nr;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            nr = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            ng = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            nb = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (nr > 255)
            {
                nr = 255;
            }
            if (ng > 255)
            {
                ng = 255;
            }
            if (nb > 255)
            {
                nb = 255;
            }

            image[i][j].rgbtRed = nr;
            image[i][j].rgbtGreen = ng;
            image[i][j].rgbtBlue = nb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp, mv;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            mv = width - (j + 1);

            tmp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][mv].rgbtBlue;
            image[i][mv].rgbtBlue = tmp;

            tmp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][mv].rgbtGreen;
            image[i][mv].rgbtGreen = tmp;

            tmp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][mv].rgbtRed;
            image[i][mv].rgbtRed = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int green;
    int blue;
    float counter;
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = blue = green = 0;
            counter = 0.00;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if ((i + k) < 0 || (i + k) > (height - 1) || (j + l) < 0 || (j + l) > (width - 1))
                    {
                        continue;
                    }
                    red += image[i + k][j + l].rgbtRed;
                    blue += image[i + k][j + l].rgbtBlue;
                    green += image[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }
            new_image[i][j].rgbtRed = round(red / counter);
            new_image[i][j].rgbtBlue = round(blue / counter);
            new_image[i][j].rgbtGreen = round(green / counter);
        }
    }
    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = new_image[j][i].rgbtBlue;
            image[j][i].rgbtGreen = new_image[j][i].rgbtGreen;
            image[j][i].rgbtRed = new_image[j][i].rgbtRed;
        }
    }
}
