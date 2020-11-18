#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

char num_alphabet(char letter, string key);
int lock = 0;

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2)      // checks for correct input
    {
        printf("ERROR: please input exactly one key (no spaces)\n");
        return 1;
    }
    if ((strlen(key) != 26))
    {
        printf("ERROR: please input a 26-digit long key\n");
        return 1;
    }
    for (int i = 0; key[i] != '\0'; i++)
    {
        if ((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z'))
        {
        }
        else
        {
            printf("ERROR: please input a key with only letters\n");
            return 1;
        }
    }
    for (int i = 0; i < 25; i++)
    {
        for (int d = 0; d < 25; d++)
    {
        if ((key[i] == key[d]) && (i != d))
        {
            printf("ERROR: duplicate character in key");
            return 1;
        }
    }
    }

    string ptext = get_string("plaintext: ");
    int b = 0;
    while (ptext[b] != '\0')
    {
        b++;
    }
    char ctext[b];
    for (int i = 0; i <= b; i++)        //creates cipher text
    {
        if ((ptext[i] >= 'A' && ptext[i] <= 'Z') || (ptext[i] >= 'a' && ptext[i] <= 'z'))
        {
            char letter = num_alphabet(ptext[i], key);// gets # of alphabet the inputed letter is... a = 1.
            ctext[i] = letter;
        }
        else
        {
            ctext[i] = ptext[i];
        }
    }
    printf("ciphertext: %s\n", ctext);
    return 0;
}

char num_alphabet(char letter, string key)      // gets number of alphabet a character is and gets cipher text character from that
{
    char upkey[27];
    char lowkey[27];
    char cletter;

    for (int i = 0; i <= 25; i++)
    {
        upkey[i] = toupper(key[i]);
        lowkey[i] = tolower(key[i]);
    }

    int num;
    if (letter >= 'a' && letter <= 'z')
    {
        num = (int) letter - 96;
        cletter = lowkey[num - 1];
    }
    if (letter >= 'A' && letter <= 'Z')
    {
        num = (int) letter - 64;
        cletter = upkey[num - 1];
    }
    return cletter;
}

