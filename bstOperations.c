#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

static Node *insert(Node *root, int key)
{
    if (root == NULL) {
        Node *node = malloc(sizeof *node);
        if (node == NULL) {
            perror("Unable to allocate node");
            exit(EXIT_FAILURE);
        }
        node->key = key;
        node->left = node->right = NULL;
        return node;
    }
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

static Node *search(Node *root, int key)
{
    while (root != NULL && root->key != key)
        root = key < root->key ? root->left : root->right;
    return root;
}

static Node *delete_key(Node *root, int key)
{
    if (root == NULL) return NULL;
    if (key < root->key) root->left = delete_key(root->left, key);
    else if (key > root->key) root->right = delete_key(root->right, key);
    else if (root->left == NULL || root->right == NULL) {
        Node *child = root->left != NULL ? root->left : root->right;
        free(root);
        return child;
    } else {
        Node *successor = root->right;
        while (successor->left != NULL) successor = successor->left;
        root->key = successor->key;
        root->right = delete_key(root->right, successor->key);
    }
    return root;
}

static void inorder(const Node *root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

static void clear(Node *root)
{
    if (root == NULL) return;
    clear(root->left);
    clear(root->right);
    free(root);
}

int main(void)
{
    Node *root = NULL;
    int choice, key;
    do {
        printf("\n1 Insert  2 Delete  3 Search  4 Inorder  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Key: ");
            if (scanf("%d", &key) == 1) root = insert(root, key);
            break;
        case 2:
            printf("Key to delete: ");
            if (scanf("%d", &key) == 1) {
                if (search(root, key) == NULL) puts("Key not found.");
                else {
                    root = delete_key(root, key);
                    puts("Key deleted.");
                }
            }
            break;
        case 3:
            printf("Key to search: ");
            if (scanf("%d", &key) == 1)
                puts(search(root, key) != NULL ? "Key found." : "Key not found.");
            break;
        case 4:
            if (root == NULL) puts("Tree is empty.");
            else { inorder(root); putchar('\n'); }
            break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    clear(root);
    return 0;
}
