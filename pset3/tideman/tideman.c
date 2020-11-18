#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < (candidate_count); i++)
    {
        candidates[i] = argv[i + 1];        // candidates holds candidates names'
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < (candidate_count); i++)
    {
        for (int j = 0; j < (candidate_count - 1); j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < (voter_count); i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];         //MAYBE WE HAVE TO CLEAR RANKS FIRST... has some random numbers in it rn

        // Query for each rank
        for (int j = 0; j < (candidate_count); j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < (candidate_count); i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // update ranks (keeps track of the votes for each candidate)
            ranks[rank] = i;        //'i' is candidate#
            return true;
        }
    }
    return false;
}       //WORKS

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < (candidate_count); i++)
    {
        for (int j = (i + 1); j < (candidate_count); j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;       //plus one to every "couple" in which [candidate] is prefered over [candidate] respectively (take a "ranks" aray of: 3-0-4-1-2)
        }
    }
    return;
}       //WORKS

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < (candidate_count); i++)
    {
        for (int j = 0; j < (candidate_count); j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])      // pairs has an int winner and int loser //i don't thinkt hs < is correct.. wait we care about switiching the i and j right?????
                {
                    // i is winner; j is loser
                    pairs[pair_count].winner = i;        //works.. however, from begining... has a pair (always at the end) of {winner = 0, loser = 0} MAKE SURE CODE AFTER THIS WORKS WITH THAT!!!!
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}       //WORKS

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)       //sort by most voted for first AT END FIGURE OUT HOW TO DO MERGE SORTING HERE.
{
    typedef struct
    {
        int winner_ID;
        int value;
    }
    scores;
    scores score[candidate_count];
    int r = 0;

    // putting values and candidate winners in variable 'score'
    for (int i = 0; i < (candidate_count); i++)
    {
        for (int j = 0; j < (candidate_count); j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    score[r].value = preferences[i][j];
                    score[r].winner_ID = i;     // unnecessary.. only need the value.. the place 'i' in the array will be the id...
                    r++;
                }
            }
        }
    }

// determining the highest value in 'score'
    for (int i = 0; i < (pair_count - 1); i++)      // if not working... make pair_count not minus one.. logic why i have -1 is becuase no point in switching just one
    {
        r = score[i].value;
        int s = 0;
        for (int j = (i + 1); j < (pair_count + 1); j++)
        {
            if (score[j].value > r)
            {
                r = score[j].value;      //keeps max score
                s = j;      //determines place of max score
            }
        }
        if (s != 0)
        {
            // switch order of score
            int t = score[i].value;
            score[i].value = score[s].value;
            score[s].value = t;
            // switch order of pairs
            int pw;
            int pl;
            pw = pairs[i].winner;
            pl = pairs[i].loser;
            pairs[i] = pairs[s];
            pairs[s].winner = pw;
            pairs[s].loser = pl;
        }
    }
    return;
}       //WORKS

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool e;
    bool ee;
    bool eee;
    bool eeee;

    // check if it's safe to implement each 'i'
    for (int i = 0; i < pair_count; i++)
    {
        e = true;
        ee = true;
        eee = true;
        eeee = true;
        if (i > 1)
        {
            // look for the start of a potential loop
            for (int ii = 0; (ii <= i) && (ee = true); ii++)
            {
                if (pairs[ii].loser == pairs[ii + 1].winner)
                {
                    ee = false;     // WILL NOT WORK WITH MULTIPLE POTENTIAL LOOPS... WILL STOP AFTER TEH FIRST IS CHECKED - consider taking this step out
                    // looks to the end of the array for a potential loop
                    for (int iii = ii; (iii < i) && (e == true); iii++)     //not efficient loop.. but it works
                    {
                        if (pairs[iii].loser == pairs[iii + 1].winner)
                        {
                            // checking for end of potential loop
                            int endl = i;
                            for (int iv = ii; iv < i; iv++)
                            {
                                if (pairs[iv].loser != pairs[iv + 1].winner)
                                {
                                    endl = iv;
                                }
                            }

                            //checking for loop
                            for (int iv = ii; (iv < endl); iv++)
                            {
                                //check only if i (the 'pairs' in question) is in a potential loop
                                if (i > ii || i < endl)
                                {
                                    if (pairs[i].loser == pairs[iv].winner)
                                    {
                                        e = false;
                                    }
                                }
                            }
                        }
                        else
                        {
                            // stops loop
                            iii = i;
                        }
                    }
                }
            }

            // repeat same process as above, but in opposite 'direction'
            for (int ii = 0; (ii <= i) && (eeee = true); ii++)
            {
                if (pairs[ii].winner == pairs[ii + 1].loser)
                {
                    eeee = false;
                    for (int iii = ii; (iii < i) && (eee == true); iii++)
                    {
                        if (pairs[iii].winner == pairs[iii + 1].loser)
                        {
                            int endl = i;
                            for (int iv = ii; iv < i; iv++)
                            {
                                if (pairs[iv].winner != pairs[iv + 1].loser)
                                {
                                    endl = iv;
                                }
                            }
                            for (int iv = ii; (iv < endl); iv++)
                            {
                                if (i > ii || i < endl)
                                {
                                    if (pairs[iii + 1].winner == pairs[iv].loser)
                                    {
                                        eee = false;
                                    }
                                }
                            }
                        }
                        else
                        {
                            iii = i;
                        }
                    }
                }
            }
        }
        if ((e == true) && (eee == true))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }


    // my old code.. that ran on wrong logic.. still good code tho so i kept xD
    if (0 == 1)
    {
        // checking 'locked' collumns for true statements (at least one collumn without T's (not including the one we're about to write in))
        for (int i = 0; i < (pair_count); i++)
        {
            int w = 0;
            int r = 50;

            for (int ii = 0; (ii < (candidate_count)); ii++)
            {
                r = 50;
                if (ii != pairs[i].loser)
                {
                    r = 0;
                    for (int iii = 0; iii < (candidate_count); iii++)
                    {
                        if (locked[iii][ii] == true)     // going through each collumn and tallying up the "true"s
                        {
                            r++;
                        }
                    }
                }
                    if (r == 0)
                    {
                        w++;
                    }
            }

            // setting up 'locked'
            if ((w > 0) || (i = 0))     // if i=0 is here, that means if no input and the array is just (0,0).. then it's going to lock that in. at zero zero. .. we could add a line that just cahnges locked[00] to false.
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }       //SOMEHOW THIS LOOP IS INFITNE NEVER ENDING????
    }
    return;
}       //WORKS

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < (candidate_count); i++)
    {
        int r = 0;
        for (int ii = 0; ii < (candidate_count); ii++)
        {
            if (locked[ii][i] == false)
            {
                r++;
            }
        }
        if (r == candidate_count)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}       //WORKS

