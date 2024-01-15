#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct player {
    char summonerName[20];
    struct player* right;
} *newptr, *first, *last, *temp, *prev, *next;

int create() {
    char ch;
    while (1) {
        newptr = (struct player*)malloc(sizeof(struct player));
        if (newptr == NULL) {
            printf("Memory allocation error");
            return 0;
        }
        printf("\nEnter Summoner Name of player: ");
        scanf("%s", &newptr->summonerName);
        newptr->right = NULL;
        if (first == NULL)
            first = last = newptr;
        else {
            temp->right = newptr;
            temp = temp->right;
        }
        printf("Want to add more players (Y/N): ");
        ch = getch();
        if (ch == 'n' || ch == 'N') {
            temp = first;
            while (temp->right != NULL) {
                temp = temp->right;
                last = temp;
            }
            last->right = first;
            return(0);
        }
    }
}

void display() {
    temp = first;
    if (temp == NULL) {
        printf("There are no players\n");
        return;
    }
    do {
        printf("[%s]--->", temp->summonerName);
        temp = temp->right;
    } while (temp != first);
    printf("(%s)", last->right->summonerName);
}

void insert_beginning() {
    newptr = (struct player*)malloc(sizeof(struct player));
    if (newptr == NULL) {
        printf("Memory allocation error");
        return 0;
    }
    printf("\nEnter Summoner Name: ");
    scanf("%s", &newptr->summonerName);
    newptr->right = NULL;
    if (first == NULL) {
        first = last = newptr;
    }
    else {
        newptr->right = first;
        first = newptr;
    }
    last->right = first;
}

void insert_end() {
    newptr = (struct player*)malloc(sizeof(struct player));
    if (newptr == NULL) {
        printf("Memory allocation error");
        return 0;
    }
    printf("\nEnter Summoner Name: ");
    scanf("%s", &newptr->summonerName);
    newptr->right = NULL;
    last->right = newptr;
    last = newptr;
    last->right = first;
}

void insert_middle() {
    int pos, c;
    c = 0;
    newptr = (struct player*)malloc(sizeof(struct player));
    printf("Enter Position for player to be inserted : ");
    scanf("%d", &pos);
    printf("\nEnter Summoner Name: ");
    scanf("%s", &newptr->summonerName);
    temp = first;
    while (temp != NULL) {
        c++;
        if (c == pos - 1) {
            next = temp->right;
            newptr->right = next;
            temp->right = newptr;
            break;
        }
        temp = temp->right;
    }
}

void delete_beginning() {
    if (first == NULL) {
        printf("\nThere are no Players");
    }
    else {
        temp = first;
        first = first->right;
        last->right = first;
        free(temp);
        printf("\nFirst Player deleted\n");
    }
}

void delete_end() {
    if (first == NULL) {
        printf("\nThere are no Players");
        return;
    }
    temp = first;
    while (temp != last) {
        prev = temp;
        temp = temp->right;
    }
    prev->right = NULL;
    last = prev;
    last->right = first;
    printf("\nLast Player deleted\n");
    free(temp);
}

void delete_middle() {
    if (first == NULL) {
        printf("\nThere are no Players");
    }
    else {
        int pos, c;
        c = 0;
        printf("Enter the position of the player you want to delete: ");
        scanf("%d", &pos);

        temp = first;
        while (temp->right != NULL) {
            c++;
            if (c == pos - 1) {
                next = temp->right->right;
                free(temp->right);
                temp->right = next;
                printf("\nPlayer at position %d deleted\n", pos);
                break;
            }
            temp = temp->right;
        }
    }
}

void search() {
    char search_name[25];
    int pos, foundFlag = 0;
    pos = 0;
    temp = first;
    printf("\nEnter Summoner Name of the player you want to find : ");
    scanf("%s", &search_name);

    do {
        pos++;
        if (strcmpi(search_name, temp->summonerName) == 0) {
            foundFlag = 1;
            printf("\nPlayer Found at %d", pos);
            break;
        }
        temp = temp->right;

    } while (temp != first);

    if (foundFlag == 0) {
        printf("\n\tNo such player found!");
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
        printf(" +---------League of Legends Player Menu---------+\n");
        printf(" | 1. Create Players                            |\n");
        printf(" | 2. Display Players                           |\n");
        printf(" | 3. Insert Player at Beginning                |\n");
        printf(" | 4. Insert Player in the Middle               |\n");
        printf(" | 5. Insert Player at End                      |\n");
        printf(" | 6. Delete Player at Beginning                |\n");
        printf(" | 7. Delete Player in the Middle               |\n");
        printf(" | 8. Delete Player at End                      |\n");
        printf(" | 9. Search for a Player                      |\n");
        printf(" | 10. Exit                                     |\n");
        printf(" +----------------------------------------------+\n");
        printf("Enter your option: ");
        scanf("%d", &opt);

        switch (opt) {
        case 1:
            create();
            break;
        case 2:
            display();
            break;
        case 3:
            insert_beginning();
            break;
        case 4:
            insert_middle();
            break;
        case 5:
            insert_end();
            break;
        case 6:
            delete_beginning();
            break;
        case 7:
            delete_middle();
            break;
        case 8:
            delete_end();
            break;
        case 9:
            search();
            break;
        case 10:
            exit_program();
        }
        getch();
    }
}
