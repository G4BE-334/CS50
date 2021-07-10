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
void print_winner(void);

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
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate comparison1;
    candidate comparison2;
    candidate comparison3;
    candidate comparison4;
    comparison2.votes = 0;
    bool tie = false;
    bool tie2 = false;
    for (int i = 0; i < candidate_count; i++)
    {
        candidate nextcandidate = candidates[i + 1];
        if (i == candidate_count - 1)
        {
            nextcandidate = candidates[0];
        }
        if (candidates[i].votes >= nextcandidate.votes)
        {
            comparison1.name = candidates[i].name;
            comparison1.votes = candidates[i].votes;
        }
        else if (candidates[i].votes < nextcandidate.votes)
        {
            comparison1.name = nextcandidate.name;
            comparison1.votes = nextcandidate.votes;        
        }
        if (comparison1.votes > comparison2.votes)
        {
            comparison2.votes = comparison1.votes;
            comparison2.name = comparison1.name;
            if (tie)
            {
                tie = false;
                tie2 = false;
            }
        }
        else if (comparison1.votes == comparison2.votes && !tie)
        {
            comparison3.name = comparison1.name;
            comparison3.votes = comparison1.votes;
            tie = true;
        }
        if (tie && comparison1.votes == comparison3.votes && comparison1.name != comparison3.name)
        {
            comparison4.name = comparison1.name;
            comparison4.votes = comparison1.votes;
            tie2 = true;
        }
    }
    printf("%s\n", comparison2.name);
    if (tie)
    {
        printf("%s\n", comparison3.name);
    }
    if (tie2)
    {
        printf("%s\n", comparison4.name);
    }
    // TODO
    return;
}
