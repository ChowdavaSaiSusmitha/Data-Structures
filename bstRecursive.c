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

static void inorder(const Node *root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

static void preorder(const Node *root)
{
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

static void postorder(const Node *root)
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

static int contains(const Node *root, int key)
{
    while (root != NULL && root->key != key)
        root = key < root->key ? root->left : root->right;
    return root != NULL;
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
    const int values[] = {1, 3, 4, 12, 14, 15, 8, 7, 2, 5, 9, 11, 6, 18};
    Node *root = NULL;
    for (size_t i = 0; i < sizeof values / sizeof values[0]; ++i)
        root = insert(root, values[i]);

    int choice, key;
    do {
        printf("\nBST loaded with syllabus values.\n"
               "1 Inorder  2 Preorder  3 Postorder  4 Search  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1: inorder(root); putchar('\n'); break;
        case 2: preorder(root); putchar('\n'); break;
        case 3: postorder(root); putchar('\n'); break;
        case 4:
            printf("Integer to search: ");
            if (scanf("%d", &key) == 1)
                puts(contains(root, key) ? "Element is present in the BST."
                                         : "Element is not present in the BST.");
            break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    clear(root);
    return 0;
}
