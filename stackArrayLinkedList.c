#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static int array_stack[CAPACITY];
static int array_top = -1;
static Node *list_top;

static void push(int value, int use_list)
{
    if (!use_list) {
        if (array_top == CAPACITY - 1) {
            puts("Array stack is full.");
            return;
        }
        array_stack[++array_top] = value;
        return;
    }
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("Unable to allocate node");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = list_top;
    list_top = node;
}

static void pop(int use_list)
{
    if (!use_list) {
        if (array_top == -1) puts("Array stack is empty.");
        else printf("Removed: %d\n", array_stack[array_top--]);
        return;
    }
    if (list_top == NULL) {
        puts("Linked stack is empty.");
        return;
    }
    Node *old = list_top;
    printf("Removed: %d\n", old->value);
    list_top = old->next;
    free(old);
}

static void display(int use_list)
{
    if (!use_list) {
        if (array_top == -1) puts("Array stack is empty.");
        for (int i = array_top; i >= 0; --i) printf("%d\n", array_stack[i]);
        return;
    }
    if (list_top == NULL) puts("Linked stack is empty.");
    for (Node *node = list_top; node != NULL; node = node->next)
        printf("%d\n", node->value);
}

int main(void)
{
    int choice, type, value;
    do {
        printf("\n1 Push  2 Pop  3 Display  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice >= 1 && choice <= 3) {
            printf("Implementation (1 array, 2 linked list): ");
            if (scanf("%d", &type) != 1 || (type != 1 && type != 2)) {
                puts("Invalid implementation.");
                continue;
            }
            if (choice == 1) {
                printf("Value: ");
                if (scanf("%d", &value) == 1) push(value, type == 2);
            } else if (choice == 2) {
                pop(type == 2);
            } else {
                display(type == 2);
            }
        } else if (choice != 0) {
            puts("Invalid choice.");
        }
    } while (choice != 0);
    while (list_top != NULL) {
        Node *next = list_top->next;
        free(list_top);
        list_top = next;
    }
    return 0;
}
