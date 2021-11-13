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
bool check(int i);
bool checked(int v, bool visit[]);

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
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
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
    for (int j = 0; j < candidate_count; j++)
    {
        // update ranks array for each voter with canidated index
        if (strcmp(candidates[j], name) == 0)
        {
            ranks[rank] = j;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // update preferences 2D array based on ranks array
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // compare opposing candidates
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 1; i < pair_count; i++) 
    { 
        pair k = pairs[i]; 
        int j = i - 1; 
        while (j >= 0 && preferences[pairs[j].winner][pairs[j].loser] > preferences[k.winner][k.loser]) 
        { 
            pairs[j + 1] = pairs[j]; 
            j = j - 1; 
        } 
        pairs[j + 1] = k; 
    } 
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (check(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

bool check(int i)
{
    bool visit[candidate_count];

    for (int j = 0; j < candidate_count; j++)
    {
        visit[j] = false;
    }
    return checked(pairs[i].winner, visit);
}

bool checked(int i, bool visit[])
{
    if (visit[i])
    {
        return true;
    }

    visit[i] = true;

    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[i][j] && checked(j, visit))
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner = true;
    int index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winner = false;
                break;
            }
        }
        
        if (winner == true)
        {
            index = i;
            break;
        }
    }
    
    if (winner == true)
    {
        printf("%s\n", candidates[index]);
    }
}