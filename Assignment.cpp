#include <stdio.h>

// Structure for League of Legends player
struct lolPlayer {
    int id;
    char playerName[20];
    int gameSchedule[2][2]; // 2 days, 2 time slots for gaming sessions
};

// Global array of players
struct lolPlayer players[100];
int playerCount = 0;

// Function to add a new player
void addPlayerData(int id) {
    struct lolPlayer *p = &players[playerCount++];
    p->id = id;
    printf("Enter the Name of Player %d\n", id);
    scanf("%s", p->playerName);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("\nEnter Gaming Schedule for day %d and time slot %d\n", i + 1, j + 1);
            scanf("%d", &p->gameSchedule[i][j]);
        }
    }
}

// Function to show the data of a single player
void showPlayerData(struct lolPlayer *p) {
    printf("\n-------------Player %d----------------", p->id);
    printf("\nName : %s \nID   :%d\n", p->playerName, p->id);
    printf("Day Time Slot Gaming Schedule:\n");
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("[ %dhrs ]", p->gameSchedule[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
}

// Function to perform linear search on player names
void searchPlayer(char *searchName) {
    int i;
    for (i = 0; i < playerCount; ++i) {
        if (!strcmp(players[i].playerName, searchName)) {
            printf("\nPlayer Found!!");
            showPlayerData(&players[i]);
            return;
        }
    }
    // when given name does not match
    printf("Player Not Present with Name %s\n", searchName);
}

// Function to delete a player based on ID
void deletePlayer(int id) {
    int i, j;

    // Find the index of the player with the given ID
    int deleteIndex = -1;
    for (i = 0; i < playerCount; ++i) {
        if (players[i].id == id) {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex == -1) {
        printf("Player Not Found with ID %d\n", id);
        return;
    }

    // Shift the array to remove the deleted player
    for (j = deleteIndex; j < playerCount - 1; j++) {
        players[j] = players[j + 1];
    }

    // Decrement the count of players
    playerCount--;

    printf("\nPlayer ID %d has been deleted.", id);
}

// Function to perform matrix addition
void matrixAddition(struct lolPlayer *p1, struct lolPlayer *p2, int result[2][2]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result[i][j] = p1->gameSchedule[i][j] + p2->gameSchedule[i][j];
        }
    }
}

// Function to perform matrix subtraction
void matrixSubtraction(struct lolPlayer *p1, struct lolPlayer *p2, int result[2][2]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result[i][j] = p1->gameSchedule[i][j] - p2->gameSchedule[i][j];
        }
    }
}

int main() {
    int choice;

    do {
        // Menu on player management
        printf("\n+-------------Menu------------+\n");
        printf("| 1.Add Player                |\n");
        printf("| 2.Show Players              |\n");
        printf("| 3.Delete Player             |\n");
        printf("| 4.Search Player             |\n");
        printf("| 5.Matrix Addition           |\n");
        printf("| 6.Matrix Subtraction        |\n");
        printf("| 7.Exit Program              |\n");
        printf("+-----------------------------+\n");
        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        // choice based if-else-if ladder
        if (choice == 1) {
            addPlayerData(playerCount + 1);
        } else if (choice == 2) {
            for (int i = 0; i < playerCount; i++)
                showPlayerData(&players[i]);
        } else if (choice == 3) {
            int delId;
            printf("Enter ID of player to be deleted : ");
            scanf("%d", &delId);
            deletePlayer(delId);
        } else if (choice == 4) {
            char searchName[20];
            printf("Enter name of the player you want to find : ");
            scanf("%s", searchName);
            searchPlayer(searchName);
        } else if (choice == 5 || choice == 6) {
            // obtaining 2 IDs to perform matrix operations
            int id1, id2;
            printf("\nEnter Existing ID of first player : ");
            scanf("%d", &id1);
            struct lolPlayer *p1 = &players[id1 - 1];
            printf("\nEnter Existing ID of second player : ");
            scanf("%d", &id2);
            struct lolPlayer *p2 = &players[id2 - 1];

            int result[2][2];

            if (choice == 2) {
                matrixAddition(p1, p2, result);
                printf("\nThe Sum of Hours for Player %d and Player %d is \n", p1->id, p2->id);
            } else {
                matrixSubtraction(p1, p2, result);
                printf("\nThe Difference of Hours for Player %d and Player %d is \n", p1->id, p2->id);
            }

            // Displaying the result matrix
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    printf("[%5dhrs]", result[i][j]);
                }
                printf("\n");
            }
        }
        // do-while running till exit condition of (7)
    } while (choice < 2);

    return 0;
}
