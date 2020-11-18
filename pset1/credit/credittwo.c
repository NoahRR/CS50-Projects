#include <cs50.h>
#include <stdio.h>
#include <math.h>

int cc_check(long, int);
char type_check(long);
int find_num_length(long);

int main(void)
{
    long cn = get_long("Please enter your credit card number\nNumber: ");        // prompts for credit card number
    int ll = find_num_length(cn);                                               // gets the number of digits in the credit card number
    int credit = cc_check(cn, ll);                                              // checks for validity of credit card number

    if (credit == 0)
    {
        printf("INVALID\n");
    }
    else
    {
       char cv = type_check(cn);                                                // checks type of credit card number

       if (cv == 'a')
       {
           printf("AMEX\n");
       }
       if (cv == 'm')
       {
           printf("MASTERCARD\n");
       }
       if (cv == 'v')
       {
           printf("VISA\n");
       }
    }
}



int cc_check(long cn, int ll)      // check if number is valid credit card number
{
    int credit = 0;
    int sum = 0;
    for (int d = 2; d <= ll; d += 2)        // gets sum of every other value from right times 2.
    {

          long xa = pow(10, d);
          long xb = pow(10, d - 1);
          int y;
          int nu = 0;
          nu = ((cn % xa) / xb);    // getting the individual digit.
          nu *= 2;

          if (nu >= 10)     //separates 2 digit under into individual digits
          {
              sum += (nu % 10);
              int ww = nu / 10;
              sum += (ww);
          }
          else
          {
              sum += nu;
          }
    }
    int ll2 = 1;
     for (int d = 1; d <= ll; d += 2)       // gets sum of every other other value from right.
    {

          long xa = pow(10, d);
          long xb = pow(10, d - 1);
          int y;
          int nu = ((cn % xa) / xb);
          sum += nu;
    }

    if ((sum % 10) == 0)        // checks if last digit of the total sum equals zero. if it does, then it is a valid credit card.
    {
        credit = 1;
    }

    return credit;
}



char type_check(long cn)        // check which bank credit card number belongs to
{
    char type = 'n';        // American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
                            // All American Express numbers start with 34 or 37
                            //most MasterCard numbers start with 51, 52, 53, 54, or 55
                            //all Visa numbers start with 4
    int ll = find_num_length(cn);
    if (ll == 15)       // american express
    {
        long xd = pow(10, ll-2);
        int ft = (cn / xd);
        if (ft == 34 || ft == 37)
        {
            type = 'a';
        }
    }
    if (ll == 16)      // master card
    {
        long xd = pow(10, ll-2);
        int ft = (cn / xd);
        if (ft < 56 && ft > 50)
        {
            type = 'm';
        }
    }
    if (ll == 13 || ll == 16)      // visa
    {
        long xd = pow(10, ll-1);
        int ft = (cn / xd);
        if (ft == 4)
        {
            type = 'v';
        }
    }
    return type;
}



int find_num_length(long dn)     // determines how many digits are in the inputed number
{                               // DOESN'T WORK WITH ZEROS AT START OF NUMBER!
    int i = 0;

    if (dn >= 1)
    {
        i = 0;
        while (dn >= 1)
        {
            dn = dn / 10;
            i += 1;
        }
    }
    return i;
}