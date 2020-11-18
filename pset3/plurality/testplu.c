#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner();

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
    return 0;       //unneccesary
}

// Update vote totals given a new vote
bool vote(string name)
{
    int cc = 0;
    while (candidates[cc].name != '\0')
    {
        cc++;
    }
    for (int i = 0; i < cc; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // TODO
    return false;
}

// Print the winner (or winners) of the election
void print_winner()
{
    int cc = 0;
    while (candidates[cc].name != '\0')
    {
        cc++;
    }
    string final[cc];
    int p = 0;
    final[0] = candidates[0].name;      // puts first name in final.. which is what the "winner" is stored in
    int finalnum = candidates[0].votes; // storing the highest value (first one for starting out)
    for (int i = 0; i < (cc - 1); i++)
    {
        if (candidates[i + 1].votes > finalnum)     // if next candidate has more votes than the current winner, then replace
        {
            final[0] = candidates[i + 1].name;
            finalnum = candidates[i + 1].votes;
            for (int j = 1; j < (p + 1); j++)      // clears the previous "winners"
            {
                if (strcmp(final[0], final[j]) != 0)
                {
                    final[j] = "";
                }
            }
        }
        else if (candidates[i + 1].votes < finalnum)
        {
        }
        else        // if equals.. store both names in final
        {
            final[p + 1] = candidates[i + 1].name;
            p++;
        }

    }
    for (int k = 0; k < (p + 1); k++)
    {
        for (int i = 0; i < cc; i++)
        {
            if ((strcmp(final[k], candidates[i].name) == 0))
            {
                printf("%s\n", final[k]);
            }
        }
    }
    return;
}

