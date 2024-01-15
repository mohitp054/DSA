#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Player {
    char summonerName[50];
    int rank;
    
};

struct Team {
    char teamName[50];
    int wins;
    int losses;
    
};

int comparisons = 0;
int dataTransfers = 0;

void resetMetrics()
{
    comparisons = 0;
    dataTransfers = 0;
}

void printMetrics(const char *operation)
{
    printf("\nMetrics for %s:\n", operation);
    printf("Total Element Comparisons: %d\n", comparisons);
    printf("Total Data Transfer Operations: %d\n", dataTransfers);
}

void printArray(struct Team teams[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("[%s - Wins: %d, Losses: %d] ", teams[i].teamName, teams[i].wins, teams[i].losses);
    }
}

void teamBinarySearch(struct Team teams[], int n)
{
    resetMetrics();
    
    char searchTeam[50];
    printf("\nEnter the team name to search: ");
    scanf("%s", searchTeam);

    int low = 0;
    int high = n - 1;
    int found = 0;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        comparisons++;

        int cmpResult = strcmp(searchTeam, teams[mid].teamName);

        if (cmpResult == 0)
        {
            printf("\n\nTeam found: %s (Wins: %d, Losses: %d)\n", teams[mid].teamName, teams[mid].wins, teams[mid].losses);
            printMetrics("Team Binary Search");
            found = 1;
            return;
        }
        else if (cmpResult > 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (!found)
    {
        printf("\n\nTeam not found.\n");
    }
}

void teamBubbleSort(struct Team teams[], int n)
{
    resetMetrics();
    // Assume sorting based on wins in descending order
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            if (teams[j].wins < teams[j + 1].wins)
            {
                dataTransfers += 3;
                // Swap teams
                struct Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
    printf("\nTeams sorted based on wins (descending order):\n");
    printArray(teams, n);
    printMetrics("Team Bubble Sort");
}

void teamLinearSearch(struct Team teams[], int n)
{
    resetMetrics();
    char searchTeam[50];
    printf("\nEnter the team name to search: ");
    scanf("%s", searchTeam);

    int foundAt = -1;
    for (int i = 0; i < n; ++i)
    {
        comparisons++;
        if (strcmp(searchTeam, teams[i].teamName) == 0)
        {
            foundAt = i;
            break;
        }
    }

    if (foundAt != -1)
    {
        printf("\nTeam is present at index %d\n", foundAt);
        printMetrics("Team Linear Search");
    }
    else
    {
        printf("\nTeam is not present in the array\n");
    }
}

int main()
{
    struct Team lolTeams[] = {
        {"Team1", 20, 5},
        {"Team2", 18, 7},
        {"Team3", 15, 10},
        {"Team4", 22, 3},
        {"Team5", 17, 8},
    };

    int opt;
    opt = 0;
    int numTeams = sizeof(lolTeams) / sizeof(lolTeams[0]);

    while (1)
    {
        printf("\n");
        printf(" +------------League of Legends Esports Menu------------+\n");
        printf(" | 1. Team Binary Search                               |\n");
        printf(" | 2. Team Bubble Sort                                 |\n");
        printf(" | 3. Team Linear Search                                |\n");
        printf(" | 4. Exit                                              |\n");
        printf(" +------------------------------------------------------+\n");
        printf("Enter your option: ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            teamBinarySearch(lolTeams, numTeams);
            break;
        case 2:
            teamBubbleSort(lolTeams, numTeams);
            break;
        case 3:
            teamLinearSearch(lolTeams, numTeams);
            break;
        case 4:
            exit(0);
        }
    }

    return 0;
}