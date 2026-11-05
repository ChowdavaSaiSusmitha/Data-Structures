#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 32

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

static void inorder_iterative(const Node *root)
{
    const Node *stack[STACK_CAPACITY], *current = root;
    int top = -1;
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            if (top == STACK_CAPACITY - 1) {
                puts("Traversal stack capacity exceeded.");
                return;
            }
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->key);
        current = current->right;
    }
    putchar('\n');
}

static void preorder_iterative(const Node *root)
{
    const Node *stack[STACK_CAPACITY];
    int top = -1;
    if (root != NULL) stack[++top] = root;
    while (top >= 0) {
        const Node *node = stack[top--];
        printf("%d ", node->key);
        if (node->right != NULL) {
            if (top == STACK_CAPACITY - 1) {
                puts("\nTraversal stack capacity exceeded.");
                return;
            }
            stack[++top] = node->right;
        }
        if (node->left != NULL) {
            if (top == STACK_CAPACITY - 1) {
                puts("\nTraversal stack capacity exceeded.");
                return;
            }
            stack[++top] = node->left;
        }
    }
    putchar('\n');
}

static void postorder_iterative(const Node *root)
{
    const Node *stack[STACK_CAPACITY], *last_visited = NULL, *current = root;
    int top = -1;
    while (current != NULL || top >= 0) {
        if (current != NULL) {
            if (top == STACK_CAPACITY - 1) {
                puts("Traversal stack capacity exceeded.");
                return;
            }
            stack[++top] = current;
            current = current->left;
        } else {
            const Node *peek = stack[top];
            if (peek->right != NULL && last_visited != peek->right) {
                current = peek->right;
            } else {
                printf("%d ", peek->key);
                last_visited = stack[top--];
            }
        }
    }
    putchar('\n');
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
    const int values[] = {6, 9, 2, 5, 8, 14, 7};
    Node *root = NULL;
    for (size_t i = 0; i < sizeof values / sizeof values[0]; ++i)
        root = insert(root, values[i]);

    int choice;
    do {
        printf("\nBST loaded; duplicate syllabus values are ignored.\n"
               "1 Inorder  2 Preorder  3 Postorder  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1: inorder_iterative(root); break;
        case 2: preorder_iterative(root); break;
        case 3: postorder_iterative(root); break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    clear(root);
    return 0;
}
