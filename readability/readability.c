#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_length(string input);
int word_length = 1;
int num_setences(string input);

int main(void)
{
    string input = get_string("Text: ");        // gets input
    int n = get_length(input);      // gets number of letters
    int s = num_setences(input);        // gets number of sentences

    double L = ((double) n / (double) word_length) * 100;
    double S = (100 * (double) s) / (double) word_length;
    double i = .0588 * L - .296 * S - 15.8;
    int index = round(i);


    if (index > 0 && index < 17)
    {
        printf("Grade %i\n", index);
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int get_length(string input)        // gets length of input string
{
    int n = 0;
    int z = 0;
    while (input[n] != '\0')
    {
        if ((input[n] <= 'Z' && input[n] >= 'A') || (input[n] <= 'z' && input[n] >= 'a'))
        {
            n++;
        }
        else
        {
            n++;
            z++;
        }

        if (input[n] == ' ' && input[n - 1] != ' '
            && input[n + 1] != '\0')       // gets word count - adds extra word if two or more spaces at end
        {
            word_length++;
        }
    }
    return (n - z);
}

int num_setences(string input)      // gets number of sentences
{
    int s = 0;
    int n = 1;
    while (input[n] != '\0')
    {
        if (input[n] == '.' || input[n] == '?' || input[n] == '!')
        {
            s++;
        }
        n++;
    }
    return s;
}