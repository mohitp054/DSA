#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct player{
    char summonerName[20];
    struct player *right;
}*newptr,*first,*last,*temp,*prev,*next;

int numberOfPlayers = 0;

int create(){
    char ch;
	while(1)
	{
		newptr = (struct player*) malloc(sizeof(struct player));
		if(newptr == NULL){
			printf("Memory allocation error");
			return 0;
		}
		printf("\nEnter Summoner Name of the player: ");
		scanf("%s", newptr->summonerName);
		numberOfPlayers++;
		newptr->right = NULL;
		if(first == NULL)
		    first = temp = newptr;
		else
		{
			temp->right = newptr;
			temp = temp->right;
		}
		printf("Want to add more players? (Y/N): ");
		ch = getch();
		if(ch == 'n' || ch == 'N')
			return 0;

		temp = first;
		while(temp->right != NULL)
		{
			temp = temp->right;
			last = temp;
		}	      
	}
}

void display(){
    temp = first;
    if(temp == NULL){
        printf("There are no players\n"); 
        return;
    }
    while(temp != NULL) {
        printf("[%s]--->", temp->summonerName);
        temp = temp->right;
    }
    printf("NULL \n");
}

void insert_beginning(){
	newptr = (struct player *)malloc(sizeof(struct player));
	if(newptr == NULL){
		printf("Memory allocation error");
		return;
	}
	printf("\nEnter Summoner Name of new player: ");
	scanf("%s", newptr->summonerName);
	numberOfPlayers++;
	newptr->right = NULL;
	if(first == NULL)
	{
		first = last = newptr;
    }
	else
	{
		newptr->right = first;
		first = newptr;
	}
}

void insert_end(){
	newptr = (struct player*)malloc(sizeof(struct player));
	if(newptr == NULL){
		printf("Memory allocation error");
		return;
	}
	printf("\nEnter Summoner Name of new player: ");
	scanf("%s", newptr->summonerName);
	numberOfPlayers++;
	newptr->right = NULL;
	temp = first;
	while(temp != NULL){
		last = temp;
		temp = temp->right;
	}
	last->right = newptr;
	newptr->right = NULL;
}

void insert_middle(){
	int pos, c; c = 0;
	newptr = (struct player*)malloc(sizeof(struct player));
	if(newptr == NULL){
		printf("Memory allocation error");
		return ;
	}
	printf("Enter Position for player to be inserted: ");
	scanf("%d", &pos);
	printf("\nEnter Summoner Name of new player: ");
	scanf("%s", newptr->summonerName);
	numberOfPlayers++;
	temp = first;
	while (temp != NULL)
	{
		c++;
		if(c == pos-1){
		   next = temp->right;
		   newptr->right = next;
		   temp->right = newptr;
		   break;
		}
		temp = temp->right;
	}
}

void delete_beginning(){
	if(first == NULL){
		printf("\nThere are no players");
	}
	else{
		temp = first;
		first = first->right;
		free(temp);
		numberOfPlayers--;
		printf("\nFirst player deleted\n");
	}
}

void delete_end(){
	if(first == NULL){
		printf("\nThere are no players");
		return;
	}
	temp = first;
	while(temp->right != NULL)
	{
		prev = temp;
		temp = temp->right;
		last = temp;
	}	     
	prev->right = NULL;
	last = prev;
    printf("\nLast player deleted\n");
	numberOfPlayers--;
	free(temp);
}

void delete_middle(){
    if(first == NULL){
        printf("\nThere are no players");
    }
    else{
        int pos, c; c = 0;
        printf("Enter the position of the player you want to delete: ");
        scanf("%d", &pos);

        temp = first;
        while(temp->right != NULL){
            c++;
            if(c == pos - 1){
                prev = temp;
                next = temp->right->right;
                free(temp->right);
                prev->right = next;
                printf("\nPlayer at position %d deleted\n", pos);
				numberOfPlayers--;
                break;
            }
            temp = temp->right;
        }
    }
}

void search(){
	char search_name[25];
	int pos, foundFlag = 0; pos = 0;
	temp = first;
	printf("\nEnter summoner name of the player you want to find: ");
	scanf("%s", search_name);
	while(temp != NULL){
		pos++;
		if(strcmpi(search_name, temp->summonerName) == 0){
			foundFlag = 1;
			printf("\nPlayer Found at %d", pos);
		}
		temp = temp->right;	
	}
	if(foundFlag == 0){
		printf("\nNo such player found!");
	}
}

void exit_program(){
    temp = first;
    while (temp != NULL) {
        struct player* nextNode = temp->right;
        free(temp);
        temp = nextNode;
    }
	exit(0);
}

int main()
{
    
	int opt;
	opt = 0;
	first = temp = NULL;
	while(1)
	{
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
		printf(" | 9. Search for a Player                       |\n");
		printf(" | 10. Exit                                     |\n");
		printf(" +----------------------------------------------+\n");
		printf("Enter your option: ");
		scanf("%d", &opt);

		switch(opt)
		{
			case 1: create(); break;
			case 2: display(); break;
			case 3: insert_beginning(); break;
			case 4: numberOfPlayers >= 2 ? insert_middle() : printf("\nNeed More Than 1 Player\n"); break;
			case 5: insert_end(); break;
			case 6: delete_beginning(); break;
			case 7: numberOfPlayers >= 2 ? delete_middle() : printf("\nNeed More Than 1 Player\n"); break;
			case 8: delete_end(); break;
			case 9: search(); break;
			case 10: exit_program();
		}
    }
}



