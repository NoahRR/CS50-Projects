#include <cs50.h>
#include <stdio.h>
#include <math.h>
                                //WORKS WITHOUT ZEROS.
int cc_check(long, int);
char type_check(long);
int find_num_length(long);


int main(void)
{
    long cn = get_long("Please enter your credit card number\nNumber:");
    int ll = find_num_length(cn);
    int credit = cc_check(cn, ll);

    if (credit == 0)
    {
        printf("INVALID\n");
    }
    else                    // I NEED TO ENCORPORATE THE NUMBER LENGTH AS WELL!
    {
        char type = type_check(cn);

        if (type == 'a')
        {
            printf("AMEX\n");
        }
        else if (type == 'm')
        {
            printf("MASTERCARD\n");
        }
        else if (type == 'v')
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
          int ll2 = find_num_length(cn % xa);   //!!!!!! ll2 doesn't recognize zeros as adding to the length.                        // this might be where the FLOATING POINT EXCEPTION IS... number % zero. next line.. !!!!if cn % xa is zero!!!!!.. but that wouldn't end up in the next line being wrong?
          //printf("ll2 = %i  ", ll2);
          long xb = pow(10, ll2 - 1);                                    // code doesn't work yet..
          int y;
          int nu = 0;   // doesn't help
          nu = ((cn % xa) / xb);    // getting the individual digit.      0014 /xb
          //printf("nu = %i       ", nu);
          nu *= 2;
         // printf("nu*2 = %i  ", nu);
          int ll3 = find_num_length(nu);        //cn is good.

          if (ll3 == 2)     //separates 2 digit under into individual digits
          {
              sum += (nu % 10);
              int ww = nu / 10;
              sum += (ww);
      //        printf("sum1 = %i   ", sum);
          }
          else
          {
              sum += nu;        // why isn't nu zero here second step. d=4
     //         printf("sum2 = %i   ", sum);
          }
    }                                       // CHECC WITH LOTS OF PRINTF'S... IT'S WORKING.. BUT NOT GETTING THE RIGHT ANSWER... idk where it's going wrong.
//printf("%i---", sum);
     for (int d = 1; d <= ll; d += 2)       // gets sum of every other other value from right.
    {

          long xa = pow(10, d);
          int ll2 = find_num_length(cn % xa);
          long xb = pow(10, ll2 - 1);
          int y;
          int nu = ((cn % xa) / xb);
          sum += nu;
    }
//printf("%i--", sum);
    if ((sum % 10) == 0)        // checks if last digit of the total sum equals zero. if it does, then it is a valid credit card.
    {
        credit = 1;
        printf("yay\n");
    }

    return credit;      // output should be either true or false
}



char type_check(long cn)        // check which bank credit card number belongs to
{
    char type = 'n';

    return type;        // output should be either 'a m or v'
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
    printf("\n%i-", i);
    return i;
}