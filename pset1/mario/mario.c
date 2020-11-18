#include <stdio.h>
#include <cs50.h>

int prompt_height(void);
void display_pyramid(int);

int main(void)
{
    int h = prompt_height();
    display_pyramid(h);
    return 0;
}


int prompt_height(void)     // prompt to get the height of the pyramid
{
    int height = -1;

    while (height < 1 || height > 8)
    {
        height = get_int("Let's make a pyramid! How tall would you like the pyramid to be? (between 1-8)\n     Height:");
    }

    return height;
}


void display_pyramid(int k)     // display pyramid
{
    int m;
    for (m = 1; m <= k; m++)        // going through k lines of code (height)
    {

        for (int q = 0; q < k - m; q++)     // displaying k-m blanks
        {
            printf(" ");
        }

        for (int q = 0; q < m; q++)     // displaying m hashtags
        {
            printf("#");
        }

        printf("  ");       // displaying two blanks

        for (int q = 0; q < m; q++)     // displaying m hashtags
        {
            printf("#");
        }                                    // I removed adding blanks at the end.. check50 doesn't like them
        printf("\n");       // next line

    }

}