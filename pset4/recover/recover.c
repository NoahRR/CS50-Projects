#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("input exactly one command line argument\n");
        return 1;
    }
    //open file 'f'
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("could not open file\n");
        return 1;
    }

    //create buffer
    unsigned char buffer[512];          // INT GIVES SEGMENTATION FAULT!!?
    for (int i = 0; i < 512; i++)
    {
        buffer[i] = 0;
    }

    int counter = 0;
    char fn[8];     // space to write "###.jpg" and \0
    FILE *img = NULL;
    while (fread(buffer, 512, 1, f))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xe0) == 0xe0)      // if new JPEG          //error: this is never going through.. never true.
        {
            if (counter != 0)
            {
                fclose(img);
            }
            sprintf(fn, "%03i.jpg", counter);       //creating the name of the file
            img = fopen(fn, "w");             //opening new file just created with FILE *IMG
            fwrite(buffer, 512, 1, img);            //copying buffer onto img
            counter++;
        }
        else if (counter != 0)       // if continuation of file
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(img);
    fclose(f);
}       //WORKS
