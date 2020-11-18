#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // go through rows of bit map
    for (int i = 0; i < height; i++)
    {
        // go through each pixel in each row
        for (int ii = 0; ii < width; ii++)
        {
            // get rgb values of current pixel and find average
            int rgb_value = 0;
            rgb_value += image[i][ii].rgbtBlue;
            rgb_value += image[i][ii].rgbtGreen;
            rgb_value += image[i][ii].rgbtRed;
            rgb_value = round(((float) rgb_value) / 3);

            //set all 3 color values to that average value
            image[i][ii].rgbtBlue = rgb_value;
            image[i][ii].rgbtGreen = rgb_value;
            image[i][ii].rgbtRed = rgb_value;
        }
    }
    return;
}       //WORKS

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // go through each row
    for (int i = 0; i < height; i++)
    {
        // swap symetrical pairs in each row
        for (int ii = 0; ii < (width / 2);
             ii++)
        {
            int b, g, r;
            b = g = r = 0;

            b = image[i][ii].rgbtBlue;
            g = image[i][ii].rgbtGreen;
            r = image[i][ii].rgbtRed;

            image[i][ii].rgbtBlue = image[i][width - 1 - ii].rgbtBlue;
            image[i][ii].rgbtGreen = image[i][width - 1 - ii].rgbtGreen;
            image[i][ii].rgbtRed =  image[i][width - 1 - ii].rgbtRed;

            image[i][width - 1 - ii].rgbtBlue = b;
            image[i][width - 1 - ii].rgbtGreen = g;
            image[i][width - 1 - ii].rgbtRed = r;
        }
    }
    return;
}       //WORKS

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create image duplicate to store RGB values
    RGBTRIPLE dup_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int ii = 0; ii < width; ii++)
        {
            dup_image[i][ii].rgbtBlue = image[i][ii].rgbtBlue;
            dup_image[i][ii].rgbtGreen = image[i][ii].rgbtGreen;
            dup_image[i][ii].rgbtRed = image[i][ii].rgbtRed;
        }
    }

    // two for loops to cycle through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int ii = 0; ii < width; ii++)
        {
            // summing the RGB values of the pixels around the main pixel

            int b, g, r;
            b = g = r = 0;     // blue, green, and red values respectively

            int w = (i - 1);        // min rows check
            int q = w + 3;      // max rows check
            int e = (ii - 1);       // min collumns check
            int y = e + 3;      // max collumns check

            double div = 0;        // counter

            // factoring in horizontal edges (rows outside of grid)
            if (i < 1)
            {
                w += 1;
            }
            if (i > (height - 1))
            {
                q -= 1;
            }

            // factoring in verticle edges (columns outside of grid)
            if (ii < 1)
            {
                e += 1;
            }
            if (ii > (width - 1))
            {
                y -= 1;
            }

            // summing and averaging
            for (int j = w; j < q; j++)
            {
                for (int jj = e; jj < y; jj++)
                {
                    if (jj < width
                        && j < height)     //this corrects all errors on right bound and bottom bound.. BUT IT SHOULDN'T... PROGRAM SHOULDN'T NEED THIS... AND IT'S NOT CORRECT!
                    {
                        b += dup_image[j][jj].rgbtBlue;     // error msg without if state: helpers.c:106(and 107 and 108):26: runtime error: index 600 out of bounds for type 'RGBTRIPLE [width]'
                        g += dup_image[j][jj].rgbtGreen;
                        r += dup_image[j][jj].rgbtRed;
                        div++;
                    }
                }
            }

            // print new pixel of RGB average color on original image
            image[i][ii].rgbtBlue = round(b / div);
            image[i][ii].rgbtGreen = round(g / div);
            image[i][ii].rgbtRed = round(r / div);
        }
    }
    return;
}       //WORKS

// 'EDGES' FUNCTIONS BELOW

int get_value(int i, int ii, int j, int jj, int GG, char typ, int height, int width, RGBTRIPLE dup_image[height][width])
{
    int VALUE;

    // if top left
    if (j == (i - 1) && jj == (ii - 1))
    {
        // no GG consideration.. because muliplier is same for GY and GX
        if (typ == 'b')      // then blue
        {
            VALUE = dup_image[j][jj].rgbtBlue;
        }
        if (typ == 'g')      // then green
        {
            VALUE = dup_image[j][jj].rgbtGreen;
        }
        if (typ == 'r')      // then red
        {
            VALUE = dup_image[j][jj].rgbtRed;
        }
        return (VALUE * -1);
    }

    // if top center
    if (j == (i - 1) && jj == ii)
    {
        if (GG == 1)        // then GX
        {
            return 0;
        }
        else                // then GY
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return (VALUE * -2);
        }
    }

    // if top right
    if (j == (i - 1) && jj == (ii + 1))
    {
        if (GG == 1)        // then GX
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return VALUE;
        }
        else                // then GY
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return (VALUE * -1);
        }
    }

    // if middle left
    if (j == i && jj == (ii - 1))
    {
        if (GG == 1)        // then GX
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return (VALUE * -2);
        }
        else                // then GY
        {
            return 0;
        }
    }

    // if middle center
    if (j == i && jj == ii)
    {
        return 0;
    }

    // if middle right
    if (j == i && jj == (ii + 1))
    {
        if (GG == 1)        // then GX
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return (VALUE * 2);
        }
        else                // then GY
        {
            return 0;
        }
    }

    // if lower left
    if (j == (i + 1) && jj == (ii - 1))
    {
        if (GG == 1)        // then GX
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return (VALUE * -1);
        }
        else                // then GY
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return VALUE;
        }
    }

    // if lower center
    if (j == (i + 1) && jj == ii)
    {
        if (GG == 1)        // then GX
        {
            return 0;
        }
        else                // then GY
        {
            if (typ == 'b')      // then blue
            {
                VALUE = dup_image[j][jj].rgbtBlue;
            }
            if (typ == 'g')      // then green
            {
                VALUE = dup_image[j][jj].rgbtGreen;
            }
            if (typ == 'r')      // then red
            {
                VALUE = dup_image[j][jj].rgbtRed;
            }
            return (VALUE * 2);
        }
    }

    // if lower right
    if (j == (i + 1) && jj == (ii + 1))
    {
        if (typ == 'b')      // then blue
        {
            VALUE = dup_image[j][jj].rgbtBlue;
        }
        if (typ == 'g')      // then green
        {
            VALUE = dup_image[j][jj].rgbtGreen;
        }
        if (typ == 'r')      // then red
        {
            VALUE = dup_image[j][jj].rgbtRed;
        }
        return VALUE;
    }
    // if here, return 666, which signals an error
    return 666;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create image duplicate to get original values from
    RGBTRIPLE dup_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int ii = 0; ii < width; ii++)
        {
            dup_image[i][ii].rgbtBlue = image[i][ii].rgbtBlue;
            dup_image[i][ii].rgbtGreen = image[i][ii].rgbtGreen;
            dup_image[i][ii].rgbtRed = image[i][ii].rgbtRed;
        }
    }

    // loops through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int ii = 0; ii < width; ii++)
        {
            // variables to store RBG values for both gx and gy matrix
            int gxb, gxg, gxr, gyb, gyg, gyr;
            gxb = gxg = gxr = gyb = gyg = gyr = 0;

            // same conditional statements and loop as BLUR function
            // (to go around the pixel and avoid "border" around image)
            int w = (i - 1);
            int q = w + 3;
            int e = (ii - 1);
            int y = e + 3;
            double div = 0;
            int GG;        // determines gx or gy. gx = true. gy = false.

            if (i < 1)
            {
                w += 1;
            }
            if (i > (height - 1))
            {
                q -= 1;
            }

            if (ii < 1)
            {
                e += 1;
            }
            if (ii > (width - 1))
            {
                y -= 1;
            }

            for (int j = w; j < q; j++)
            {
                for (int jj = e; jj < y; jj++)
                {
                    if (jj < width && j < height)
                    {
                        // large magnitude of values indicate a change in color
                        gxb += get_value(i, ii, j, jj, 1, 'b', height, width, dup_image);
                        gxg += get_value(i, ii, j, jj, 1, 'g', height, width, dup_image);
                        gxr += get_value(i, ii, j, jj, 1, 'r', height, width, dup_image);
                        gyb += get_value(i, ii, j, jj, 0, 'b', height, width, dup_image);
                        gyg += get_value(i, ii, j, jj, 0, 'g', height, width, dup_image);
                        gyr += get_value(i, ii, j, jj, 0, 'r', height, width, dup_image);
                    }
                }
            }

            // printing new RGB values onto main pixel (according to formula)
            int B = round((float) pow((gxb * gxb) + (gyb * gyb), .5));
            int G = round((float) pow((gxg * gxg) + (gyg * gyg), .5));
            int R = round((float) pow((gxr * gxr) + (gyr * gyr), .5));

            // capping values at 255
            if (B > 255)
            {
                B = 255;
            }
            if (G > 255)
            {
                G = 255;
            }
            if (R > 255)
            {
                R = 255;
            }

            image[i][ii].rgbtBlue = B;
            image[i][ii].rgbtGreen = G;
            image[i][ii].rgbtRed = R;
        }
    }
    return;
}
