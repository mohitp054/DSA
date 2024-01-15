#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Player {
    int playerId;
    int playerRank;     // Representing player ranking or score
    char playerName[50];
};


int mergeSortComparisons = 0;
int mergeSortDataTransfers = 0;

int quickSortComparisons = 0;
int quickSortDataTransfers = 0;

const char *predefinedNames[] = {"Faker", "Uzi", "Doinb", "Caps", "Rekkles", "Ssumday", "Jankos", "ShowMaker", "Chovy", "Perkz", "Canyon", "Teddy", "Huanfeng", "SwordArt", "Karsa", "Keria", "Nuguri", "Crisp"};

void generateRandomName(char *name) {
    int randomIndex = rand() % (sizeof(predefinedNames) / sizeof(predefinedNames[0]));
    strcpy(name, predefinedNames[randomIndex]);
}

void merge(struct Player arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

   
    struct Player L[n1], R[n2];

   
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

   
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        mergeSortComparisons++; // Increment comparison count
        if (L[i].playerRank <= R[j].playerRank) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        mergeSortDataTransfers++; // Increment data transfer count
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        mergeSortDataTransfers++; // Increment data transfer count
        i++;
        k++;
    }

    
    while (j < n2) {
        arr[k] = R[j];
        mergeSortDataTransfers++; // Increment data transfer count
        j++;
        k++;
    }
}

void mergeSort(struct Player arr[], int l, int r) {
    if (l < r) {
       
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}


int partition(struct Player arr[], int low, int high) {
    int pivot = arr[high].playerRank;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        quickSortComparisons++; // Increment comparison count
        if (arr[j].playerRank < pivot) {
            i++;
            
            struct Player temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            quickSortDataTransfers += 3; // Increment data transfer count (3 for the swap)
        }
    }
    
    struct Player temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    quickSortDataTransfers += 3; // Increment data transfer count (3 for the swap)

    return (i + 1);
}


void quickSort(struct Player arr[], int low, int high) {
    if (low < high) {
        // Find the partitioning index
        int pi = partition(arr, low, high);

        // Recursively sort the elements before and after the partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to write player data to a file
void writeToFile(struct Player arr[], int n, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(arr, sizeof(struct Player), n, file);
        fclose(file);
        }
}

// Function to read player data from a file
void readFromFile(struct Player arr[], int n, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(arr, sizeof(struct Player), n, file);
        fclose(file);
    }
}

// Function to print player data
void printPlayers(struct Player arr[], int n) {
    printf("Player Information\n");
    for (int i = 0; i < n; i++) {
        printf("[ ID: %d \tName:%s \tRank: %d ]\n", arr[i].playerId, arr[i].playerName, arr[i].playerRank);
    }
}

int main() {
    int n = 10; // Number of players (you can change this based on your data)
    struct Player players[n];

    
    for (int i = 0; i < n; i++) {
        players[i].playerId = i + 1;
        players[i].playerRank = rand() % 1000 + 1; 
        generateRandomName(players[i].playerName); 
       
    }

    writeToFile(players, n, "unsorted_players.dat");
    printf("\nUnsorted Players :\n");
    printPlayers(players, n);

    
    // Perform Merge Sort
    readFromFile(players, n, "unsorted_players.dat");
    mergeSort(players, 0, n - 1);

  
    writeToFile(players, n, "sorted_players_merge_sort.dat");

    
    readFromFile(players, n, "sorted_players_merge_sort.dat");

   
    printf("\nSorted Players (Merge Sort):\n");
    printPlayers(players, n);

    // Print comparison and data transfer counts for Merge Sort
    printf("Merge Sort Comparisons: %d\n", mergeSortComparisons);
    printf("Merge Sort Data Transfers: %d\n", mergeSortDataTransfers);

  
    readFromFile(players, n, "unsorted_players.dat");
    quickSort(players, 0, n - 1);

  
    writeToFile(players, n, "sorted_players_quick_sort.dat");

    readFromFile(players, n, "sorted_players_quick_sort.dat");

   
    printf("\nSorted Players (Quick Sort):\n");
    printPlayers(players, n);

  
    printf("Quick Sort Comparisons: %d\n", quickSortComparisons);
    printf("Quick Sort Data Transfers: %d\n", quickSortDataTransfers);

    printf("\n\n");

    if (quickSortComparisons < mergeSortComparisons) {
        printf("QuickSort has lesser Data Comparisons\n");
    } else if (quickSortComparisons > mergeSortComparisons) {
        printf("MergeSort has lesser Data Comparisons\n");
    } else {
        printf("They have Equal Data Comparisons\n");
    }

    if (quickSortDataTransfers < mergeSortDataTransfers) {
        printf("QuickSort has lesser Data Transfers\n");
    } else if (quickSortDataTransfers > mergeSortDataTransfers) {
        printf("MergeSort has lesser Data Transfers\n");
    } else {
        printf("They have Equal Data Transfers\n");
    }

    return 0;
}
