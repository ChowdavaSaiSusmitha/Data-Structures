#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

static Node *head;
static Node *tail;

static void append(int value)
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("Unable to allocate node");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->prev = tail;
    node->next = NULL;
    if (tail != NULL)
        tail->next = node;
    else
        head = node;
    tail = node;
}

static void delete_value(int value)
{
    Node *node = head;
    while (node != NULL && node->value != value)
        node = node->next;
    if (node == NULL) {
        puts("Value not found.");
        return;
    }
    if (node->prev != NULL) node->prev->next = node->next;
    else head = node->next;
    if (node->next != NULL) node->next->prev = node->prev;
    else tail = node->prev;
    free(node);
    puts("Node removed.");
}

static void display_forward(void)
{
    Node *node = head;
    if (node == NULL) puts("List is empty.");
    while (node != NULL) {
        printf("%d <-> ", node->value);
        node = node->next;
    }
    puts("NULL");
}

static void display_backward(void)
{
    Node *node = tail;
    if (node == NULL) puts("List is empty.");
    while (node != NULL) {
        printf("%d <-> ", node->value);
        node = node->prev;
    }
    puts("NULL");
}

static void clear(void)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
    tail = NULL;
}

int main(void)
{
    int choice, value;
    do {
        printf("\n1 Insert at end  2 Delete value  3 Forward  4 Backward  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Value: ");
            if (scanf("%d", &value) == 1) append(value);
            break;
        case 2:
            printf("Value to delete: ");
            if (scanf("%d", &value) == 1) delete_value(value);
            break;
        case 3: display_forward(); break;
        case 4: display_backward(); break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    clear();
    return 0;
}
