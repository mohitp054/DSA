#include <stdio.h>
#include <stdlib.h>

struct esportsPlayer {
    int playerId;
    char playerName[50];
    char teamName[50];
    char position[20];
};

struct TreeNode {
    struct esportsPlayer data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new esports player node
struct TreeNode* createNode(struct esportsPlayer data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert an esports player into the BST
struct TreeNode* insert(struct TreeNode* root, struct esportsPlayer data) {
    if (root == NULL)
        return createNode(data);

    if (data.playerId < root->data.playerId)
        root->left = insert(root->left, data);
    else if (data.playerId > root->data.playerId)
        root->right = insert(root->right, data);

    return root;
}

// Function to perform in-order traversal
void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("[ID: %d, Name: %s, Team: %s, Position: %s]\n", 
               root->data.playerId, root->data.playerName, root->data.teamName, root->data.position);
        inOrderTraversal(root->right);
    }
}

// Function to perform pre-order traversal
void preOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("[ID: %d, Name: %s, Team: %s, Position: %s]\n", 
               root->data.playerId, root->data.playerName, root->data.teamName, root->data.position);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Function to perform post-order traversal
void postOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("[ID: %d, Name: %s, Team: %s, Position: %s]\n", 
               root->data.playerId, root->data.playerName, root->data.teamName, root->data.position);
    }
}

// Function to search for a player in the BST
struct TreeNode* search(struct TreeNode* root, int playerId) {
    if (root == NULL || root->data.playerId == playerId)
        return root;

    if (playerId < root->data.playerId)
        return search(root->left, playerId);

    return search(root->right, playerId);
}

// Function to find the node with the minimum value in a BST
struct TreeNode* findMin(struct TreeNode* node) {
    while (node->left != NULL)
        node = node->left;

    return node;
}

// Function to delete a player from the BST
struct TreeNode* deleteNode(struct TreeNode* root, int playerId) {
    if (root == NULL)
        return root;

    if (playerId < root->data.playerId)
        root->left = deleteNode(root->left, playerId);
    else if (playerId > root->data.playerId)
        root->right = deleteNode(root->right, playerId);
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.playerId);
    }
    return root;
}

// Function to calculate the height of the BST
int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    struct TreeNode* root = NULL;
    int choice, playerId;
    struct esportsPlayer data;

    do {
        printf("\n+---------- Menu ------------+\n");
        printf("| 1. Add Player              |\n");
        printf("| 2. Remove Player           |\n");
        printf("| 3. Search Player           |\n");
        printf("| 4. Calculate Height of BST |\n");
        printf("| 5. In-order Traversal      |\n");
        printf("| 6. Pre-order Traversal     |\n");
        printf("| 7. Post-order Traversal    |\n");
        printf("| 8. Exit                    |\n");
        printf("+----------------------------+\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter player ID: ");
                scanf("%d", &data.playerId);
                printf("Enter player name: ");
                scanf("%s", data.playerName);
                printf("Enter team name: ");
                scanf("%s", data.teamName);
                printf("Enter player position: ");
                scanf("%s", data.position);
                root = insert(root, data);
                break;

            case 2:
                printf("Enter player ID to remove: ");
                scanf("%d", &playerId);
                root = deleteNode(root, playerId);
                break;

            case 3:
                printf("Enter player ID to search: ");
                scanf("%d", &playerId);
                struct TreeNode* result = search(root, playerId);
                if (result != NULL)
                    printf("Player Found! ID: %d, Name: %s, Team: %s, Position: %s\n", 
                           result->data.playerId, result->data.playerName, result->data.teamName, result->data.position);
                else
                    printf("Player Not Found!\n");
                break;

            case 4:
                printf("Height of the BST: %d\n", height(root));
                break;

            case 5:
                printf("In-order Traversal:\n");
                inOrderTraversal(root);
                break;

            case 6:
                printf("Pre-order Traversal:\n");
                preOrderTraversal(root);
                break;

            case 7:
                printf("Post-order Traversal:\n");
                postOrderTraversal(root);
                break;

            case 8:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 8);

    return 0;
}
