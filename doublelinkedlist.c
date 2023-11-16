#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct player {
    char summonerName[10];
    struct player *right;
    struct player *left;
} *temp, *prev, *first, *last, *newptr, *next;

int numOfPlayers = 0;

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
        numOfPlayers++;
        newptr->right = NULL;
        newptr->left = NULL;
        if (first == NULL)
            first = temp = newptr;
        else {
            temp->right = newptr;
            newptr->left = temp;
            temp = temp->right;
        }
        printf("Want to add more Players(Y/N) : ");
        ch = getch();
        if (ch == 'n' || ch == 'N') {
            temp = first;
            while (temp->right != NULL) {
                temp = temp->right;
                last = temp;
            }	
            last->right = first;
            return (0);
        }
    }
}

void display_forward() {
    if (first == NULL) {
        printf("There are no players\n");
        return;
    }
    temp = first;
    printf("Forward Display of Players : \n");
    printf("NULL");
    while (temp != NULL) {
        printf("<--[%s]-->", temp->summonerName);
        temp = temp->right;
    }
    printf("NULL\n");
}

void display_backward() {
    if (first == NULL) {
        printf("There are no players\n");
        return;
    }
    temp = first;
    printf("Reverse Display of Players : \n");
    while (temp->right != NULL) {
        temp = temp->right;
        last = temp;
    }
    temp = last;
    printf("NULL");
    while (temp != NULL) {
        printf("<--[%s]-->", temp->summonerName);
        temp = temp->left;	
    }
    printf("NULL\n");
}

void search() {
    if (first == NULL) {
        printf("There are no players\n");
        return;
    }
    char search_name[10];
    printf("Enter Summoner Name to be Searched : ");
    scanf("%s", &search_name);
    temp = first;
    int pos = 0;
    int foundFlag = 0;
    while (temp->right != NULL) {
        pos++;
        if (strcmpi(search_name, temp->summonerName) == 0) {
            printf("Player found at position : %d ", pos);
            foundFlag = 1;
            break;
        }
        temp = temp->right;
    }
    if (foundFlag == 0) {
        printf("Player is not in List");
    }
}

void insert_begining() {
    newptr = (struct player*)malloc(sizeof(struct player));
    if (newptr == NULL) {
        printf("Memory allocation error");
        return 0;
    }  	
    printf("\nEnter Summoner Name: ");
    scanf("%s", &newptr->summonerName);
    numOfPlayers++;
    newptr->left = NULL;
    first->left = newptr;
    newptr->right = first;
    first = newptr;
    printf("\nPlayer Added At Begining");
}

void insert_end() {
    newptr = (struct player*)malloc(sizeof(struct player));
    if (newptr == NULL) {
        printf("Memory allocation error");
        return 0;
    }  	
    printf("\nEnter Summoner Name: ");
    scanf("%s", &newptr->summonerName);
    numOfPlayers++;
    newptr->right = NULL;
    last->right = newptr;
    newptr->left = last;
    last = newptr;
    printf("\nPlayer Added At End");
}

void delete_begining() {
    if (first == NULL) {
        printf("There are no players\n");
        return;
    }
    temp = first;
    first = first->right;
    first->left = NULL;
    temp->right = NULL;
    free(temp);
    numOfPlayers--;
    printf("\nPlayer Deleted from Begining");
}

void delete_end() {
    if (first == NULL) {
        printf("There are no players\n");
        return;
    }
    temp = last;
    last = last->left;
    last->right = NULL;
    temp->left = NULL;
    numOfPlayers--;
    free(temp);
    printf("\nPlayer Deleted from End");
}

void delete_middle() {
    if (first == NULL) {
        printf("\nThere are no players");
    } else {
        int pos, c;
        c = 0;
        printf("Enter the position of the player you want to delete : ");
        scanf("%d", &pos);

        temp = first;
        while (temp->right != NULL) {
            c++;
            if (c == pos) {
                prev = temp->left;
                next = temp->right;
                prev->right = next;
                next->left = prev;
                temp->left = NULL;
                temp->right = NULL;  
                free(temp);
                printf("\nPlayer at position %d deleted\n", pos);
                numOfPlayers--;
                break;
            }
            temp = temp->right;
        }
    }
}

void insert_middle() {
    int pos, c;
    c = 0;
    newptr = (struct player*)malloc(sizeof(struct player));
    if (newptr == NULL) {
        printf("Memory allocation error");
        return 0;
    } 
    printf("\nEnter the position at which to insert Player : ");
    scanf("%d", &pos);	  	
    printf("\nEnter Summoner Name : ");
    scanf("%s", &newptr->summonerName);
    numOfPlayers++;
    temp = first;
    while (temp->right != NULL) {
        c++;
        if (c == pos) {
            prev = temp->left;
            prev->right = newptr;
            newptr->left = prev;
            temp->left = newptr;
            newptr->right = temp;
        }
        temp = temp->right;
    }
}

void exit_program() {
    temp = first;
    while (temp != NULL) {
        struct player* nextNode = temp->right;
        free(temp);
        temp = nextNode;
    }
    exit(0);
}

void main() {
    int opt;
    opt = 0;
    first = temp = NULL;
    while (1) {
        printf("\n");
        printf("+---------League of Legends Esports Menu---------+\n");
        printf("| 1. Create Players                             |\n");
        printf("| 2. Display Players Forward                    |\n");
        printf("| 2. Display Players Forward                    |\n");
        printf("| 3. Display Players Reverse                    |\n");
        printf("| 4. Insert Player at Beginning                 |\n");
        printf("| 5. Insert Player in the Middle                |\n");
        printf("| 6. Insert Player at the End                   |\n");
        printf("| 7. Delete Player at Beginning                 |\n");
        printf("| 8. Delete Player in the Middle                |\n");
        printf("| 9. Delete Player at the End                   |\n");
        printf("| 10. Search Player                             |\n");
        printf("| 11. Exit                                      |\n");
        printf("+-----------------------------------------------+\n");
        printf("Enter your option: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: create(); break;
            case 2: display_forward(); break;
            case 3: display_backward(); break;
            case 4: insert_begining(); break;
            case 5: numOfPlayers >= 2 ? insert_middle() : printf("\nNeed More Than 1 Node\n"); break;
            case 6: insert_end(); break;
            case 7: delete_begining(); break;
            case 8: numOfPlayers >= 2 ? delete_middle() : printf("\nNeed More Than 1 Node\n"); break;
            case 9: delete_end(); break;
            case 10: search(); break;
            case 11: exit_program();
        }
        getch();
    }
}
