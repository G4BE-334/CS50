#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Blue = image[i][j].rgbtBlue;
            int Green = image[i][j].rgbtGreen;
            int Red = image[i][j].rgbtRed;
            float avg = round((Blue + Green + Red)/3.000);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Create a swap function
void swap(RGBTRIPLE *pixel, RGBTRIPLE *pixel2)
{
    RGBTRIPLE tmp = *pixel;
    *pixel = *pixel2;
    *pixel2 = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width/2; i++)
    {
        for (int j = 0; j < height; j++)
        {
            swap(&image[j][i], &image[j][width-i-1]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avgB;
    float avgG;
    float avgR;
    // Create a new image to not use the original image to form blured pixels
    // In the end we will transfer newImage to original image
    RGBTRIPLE newImage[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // TOP EDGE OF IMAGE
            if (i == 0 && j != 0 && j != width-1)
            {
                // TOP EDGE = No i-1
                avgB = ((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/6.00);
                avgG = ((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/6.00);
                avgR = ((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/6.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // BOTTOM EDGE OF IMAGE
            else if (i == height-1 && j != 0 && j != width-1)
            {
                // BOTTOM EDGE = No i+1
                avgB = ((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue)/6.00);
                avgG = ((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen)/6.00);
                avgR = ((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed)/6.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // LEFT EDGE OF IMAGE
            else if (j == 0 && i != 0 && i != height-1)
            {
                // LEFT EDGE = No j-1
                avgB = ((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/6.00);
                avgG = ((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/6.00);
                avgR = ((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/6.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // RIGHT EDGE OF IMAGE
            else if (j == width-1 && i != 0 && i != height-1)
            {
                // RIGHT EDGE = No j+1
                avgB = ((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue)/6.00);
                avgG = ((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen)/6.00);
                avgR = ((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed)/6.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // TOP LEFT CORNER OF IMAGE
            else if(i == 0 && j == 0)
            {
                // TOP LEFT = No i-1 and no j-1
                avgB = ((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/4.00);
                avgG = ((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/4.00);
                avgR = ((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/4.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // TOP RIGHT CORNER OF IMAGE
            else if (i == 0 && j == width-1)
            {
                // TOP RIGHT = No i-1 and no j+1
                avgB = ((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue)/4.00);
                avgG = ((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen)/4.00);
                avgR = ((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed)/4.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // BOTTOM LEFT CORNER OF IMAGE
            else if(i == height-1 && j == 0)
            {
                // BOTTOM LEFT = No i+1 and no j-1
                avgB = ((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue)/4.00);
                avgG = ((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen)/4.00);
                avgR = ((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed)/4.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // BOTTOM RIGHT CORNER OF IMAGE
            else if (i == height-1 && j == width-1)
            {
                // BOTTOM RIGHT = No i+1 and no j+1
                avgB = ((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue)/4.00);
                avgG = ((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen)/4.00);
                avgR = ((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed)/4.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
            // MIDDLE OF IMAGE
            else
            {
                avgB = ((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/9.00);
                avgG = ((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/9.00);
                avgR = ((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/9.00);
                newImage[i][j].rgbtBlue = round(avgB);
                newImage[i][j].rgbtGreen = round(avgG);
                newImage[i][j].rgbtRed = round(avgR);
            }
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = newImage[x][y];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initiate the Gx and Gy variables
    int GxB, GxG, GxR, GyB, GyG, GyR; GxB = GxG = GxR = GyB = GyG = GyR = 0;
    // Initiate new Blue, new Green and new Red
    float newB, newG, newR; newB = newG = newR = 0;
    // Create new image to use for the edgy pixels
    RGBTRIPLE newImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // TOP EDGE OF IMAGE
            if (i == 0 && j != 0 && j != width-1)
            {
                GxB = (2*image[i][j+1].rgbtBlue) - (2*image[i][j-1].rgbtBlue) + image[i+1][j+1].rgbtBlue - image[i+1][j-1].rgbtBlue;
                GxG = (2*image[i][j+1].rgbtGreen) - (2*image[i][j-1].rgbtGreen) + image[i+1][j+1].rgbtGreen - image[i+1][j-1].rgbtGreen;
                GxR = (2*image[i][j+1].rgbtRed) - (2*image[i][j-1].rgbtRed) + image[i+1][j+1].rgbtRed - image[i+1][j-1].rgbtRed;
                GyB = (2*image[i+1][j].rgbtBlue) + image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue;
                GyG = (2*image[i+1][j].rgbtGreen) + image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen;
                GyR = (2*image[i+1][j].rgbtRed) + image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // BOTTOM EDGE OF IMAGE
            else if (i == height-1 && j != 0 && j != width-1)
            {
                GxB = (2*image[i][j+1].rgbtBlue) - (2*image[i][j-1].rgbtBlue) + image[i-1][j+1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                GxG = (2*image[i][j+1].rgbtGreen) - (2*image[i][j-1].rgbtGreen) + image[i-1][j+1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                GxR = (2*image[i][j+1].rgbtRed) - (2*image[i][j-1].rgbtRed) + image[i-1][j+1].rgbtRed - image[i-1][j-1].rgbtRed;
                GyB = -(2*image[i-1][j].rgbtBlue) - image[i-1][j+1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                GyG = -(2*image[i-1][j].rgbtGreen) - image[i-1][j+1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                GyR = -(2*image[i-1][j].rgbtRed) - image[i-1][j+1].rgbtRed - image[i-1][j-1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // LEFT EDGE OF IMAGE
            else if (j == 0 && (i != 0 & i != height-1))
            {
                GxB = (2*image[i][j+1].rgbtBlue) + image[i+1][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue;
                GxG = (2*image[i][j+1].rgbtGreen) + image[i+1][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen;
                GxR = (2*image[i][j+1].rgbtRed) + image[i+1][j+1].rgbtRed + image[i-1][j+1].rgbtRed;
                GyB = (2*image[i+1][j].rgbtBlue) - (2*image[i-1][j].rgbtBlue) + image[i+1][j+1].rgbtBlue - image[i-1][j+1].rgbtBlue;
                GyG = (2*image[i+1][j].rgbtGreen) - (2*image[i-1][j].rgbtGreen) + image[i+1][j+1].rgbtGreen - image[i-1][j+1].rgbtGreen;
                GyR = (2*image[i+1][j].rgbtRed) - (2*image[i-1][j].rgbtRed) + image[i+1][j+1].rgbtRed - image[i-1][j+1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // RIGHT EDGE OF IMAGE
            else if (j == width-1 && (i != 0 && i != height-1))
            {
                GxB = -(2*image[i][j-1].rgbtBlue) - image[i+1][j-1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                GxG = -(2*image[i][j-1].rgbtGreen) - image[i+1][j-1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                GxR = -(2*image[i][j-1].rgbtRed) - image[i+1][j-1].rgbtRed - image[i-1][j-1].rgbtRed;
                GyB = (2*image[i+1][j].rgbtBlue) - (2*image[i-1][j].rgbtBlue) + image[i+1][j-1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                GyG = (2*image[i+1][j].rgbtGreen) - (2*image[i-1][j].rgbtGreen) + image[i+1][j-1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                GyR = (2*image[i+1][j].rgbtRed) - (2*image[i-1][j].rgbtRed) + image[i+1][j-1].rgbtRed - image[i-1][j-1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // TOP LEFT CORNER OF IMAGE
            else if (i == 0 & j == 0)
            {
                GxB = (2*image[i][j+1].rgbtBlue) + image[i+1][j+1].rgbtBlue;
                GxG = (2*image[i][j+1].rgbtGreen) + image[i+1][j+1].rgbtGreen;
                GxR = (2*image[i][j+1].rgbtRed) + image[i+1][j+1].rgbtRed;
                GyB = (2*image[i+1][j].rgbtBlue) + image[i+1][j+1].rgbtBlue;
                GyG = (2*image[i+1][j].rgbtGreen) + image[i+1][j+1].rgbtGreen;
                GyR = (2*image[i+1][j].rgbtRed) + image[i+1][j+1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // TOP RIGHT CORNER OF IMAGE
            else if (i == 0 && j == width-1)
            {
                GxB = -(2*image[i][j-1].rgbtBlue) - image[i+1][j-1].rgbtBlue;
                GxG = -(2*image[i][j-1].rgbtGreen) - image[i+1][j-1].rgbtGreen;
                GxR = -(2*image[i][j-1].rgbtRed) - image[i+1][j-1].rgbtRed;
                GyB = (2*image[i+1][j].rgbtBlue) + image[i+1][j-1].rgbtBlue;
                GyG = (2*image[i+1][j].rgbtGreen) + image[i+1][j-1].rgbtGreen;
                GyR = (2*image[i+1][j].rgbtRed) + image[i+1][j-1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // BOTTOM LEFT CORNER
            else if (i == height-1 && j == 0)
            {
                GxB = (2*image[i][j+1].rgbtBlue) + image[i-1][j+1].rgbtBlue;
                GxG = (2*image[i][j+1].rgbtGreen) + image[i-1][j+1].rgbtGreen;
                GxR = (2*image[i][j+1].rgbtRed) + image[i-1][j+1].rgbtRed;
                GyB = -(2*image[i-1][j].rgbtBlue) - image[i-1][j+1].rgbtBlue;
                GyG = -(2*image[i-1][j].rgbtGreen) - image[i-1][j+1].rgbtGreen;
                GyR = -(2*image[i-1][j].rgbtRed) - image[i-1][j+1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // BOTTOM RIGHT CORNER
            else if(i == height-1 && j == width-1)
            {
                GxB = -(2*image[i][j-1].rgbtBlue) - image[i-1][j-1].rgbtBlue;
                GxG = -(2*image[i][j-1].rgbtGreen) - image[i-1][j-1].rgbtGreen;
                GxR = -(2*image[i][j-1].rgbtRed) - image[i-1][j-1].rgbtRed;
                GyB = -(2*image[i-1][j].rgbtBlue) - image[i-1][j-1].rgbtBlue;
                GyG = -(2*image[i-1][j].rgbtGreen) - image[i-1][j-1].rgbtGreen;
                GyR = -(2*image[i-1][j].rgbtRed) - image[i-1][j-1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
            // MIDDLE OF IMAGE
            else
            {
                GxB = (2*image[i][j+1].rgbtBlue) - (2*image[i][j-1].rgbtBlue) + image[i+1][j+1].rgbtBlue - image[i+1][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                GxG = (2*image[i][j+1].rgbtGreen) - (2*image[i][j-1].rgbtGreen) + image[i+1][j+1].rgbtGreen - image[i+1][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                GxR = (2*image[i][j+1].rgbtRed) - (2*image[i][j-1].rgbtRed) + image[i+1][j+1].rgbtRed - image[i+1][j-1].rgbtRed + image[i-1][j+1].rgbtRed - image[i-1][j-1].rgbtRed;
                GyB = (2*image[i+1][j].rgbtBlue) - (2*image[i-1][j].rgbtBlue) + image[i+1][j+1].rgbtBlue - image[i-1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue - image[i-1][j-1].rgbtBlue;
                GyG = (2*image[i+1][j].rgbtGreen) - (2*image[i-1][j].rgbtGreen) + image[i+1][j+1].rgbtGreen - image[i-1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen - image[i-1][j-1].rgbtGreen;
                GyR = (2*image[i+1][j].rgbtRed) - (2*image[i-1][j].rgbtRed) + image[i+1][j+1].rgbtRed - image[i-1][j+1].rgbtRed + image[i+1][j-1].rgbtRed - image[i-1][j-1].rgbtRed;
                newB = round((float)sqrt((GxB*GxB) + (GyB*GyB)));
                if (newB > 255)
                {
                    newB = 255;
                }
                newG = round((float)sqrt((GxG*GxG) + (GyG*GyG)));
                if (newG > 255)
                {
                    newG = 255;
                }
                newR = round((float)sqrt((GxR*GxR) + (GyR*GyR)));
                if (newR > 255)
                {
                    newR = 255;
                }
                newImage[i][j].rgbtBlue = newB;
                newImage[i][j].rgbtGreen = newG;
                newImage[i][j].rgbtRed = newR;
            }
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = newImage[x][y];
        }
    }
}
