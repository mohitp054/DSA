#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct player {
    char summonerName[20];
    char role[15];
    int teamNumber;
    struct player* right;
};

struct player *newptr, *first, *last, *temp, *prev, *next;

int numberOfPlayers = 0;

int create() {
    char ch;
    while (1) {
        newptr = (struct player*)malloc(sizeof(struct player));
        if (newptr == NULL) {
            printf("Memory allocation error");
            return 0;
        }
        printf("\nEnter Summoner Name: ");
        scanf("%s", &newptr->summonerName);
        printf("Enter Role: ");
        scanf("%s", &newptr->role);
        printf("Enter Team Number: ");
        scanf("%d", &newptr->teamNumber);

        numberOfPlayers++;
        newptr->right = NULL;

        if (first == NULL)
            first = temp = newptr;
        else {
            temp->right = newptr;
            temp = temp->right;
        }

        printf("Want to add more players (Y/N)? ");
        ch = getch();
        if (ch == 'n' || ch == 'N')
            return (0);

        temp = first;
        while (temp->right != NULL) {
            temp = temp->right;
            last = temp;
        }
    }
}

void display() {
    temp = first;
    if (temp == NULL) {
        printf("There are no players\n");
        return;
    }

    while (temp != NULL) {
        printf("[%s - %s - Team %d]--->", temp->summonerName, temp->role, temp->teamNumber);
        temp = temp->right;
    }

    printf("NULL \n");
}

// Add other functions accordingly, modifying the structure and variables as needed.

void main() {
    int opt;
    opt = 0;
    first = temp = NULL;

    while (1) {
        printf("\n");
        printf("+---------League of Legends Esports Menu---------+\n");
        printf("| 1. Create Players                             |\n");
        printf("| 2. Display Players                            |\n");
        // Add other menu options accordingly
        printf("| 9. Search Player                              |\n");
        printf("| 10. Exit                                      |\n");
        printf("+-----------------------------------------------+\n");
        printf("Enter your option: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: create(); break;
            case 2: display(); break;
            // Add cases for other menu options
            case 9: search(); break;
            case 10: exit_program();
        }

        getch();
    }
}
