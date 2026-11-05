#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static Node *tail;

static void insert_end(int value)
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("Unable to allocate node");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    if (tail == NULL) {
        node->next = node;
        tail = node;
    } else {
        node->next = tail->next;
        tail->next = node;
        tail = node;
    }
}

static void delete_value(int value)
{
    if (tail == NULL) {
        puts("List is empty.");
        return;
    }
    Node *previous = tail;
    Node *current = tail->next;
    do {
        if (current->value == value) {
            if (current == previous) {
                tail = NULL;
            } else {
                previous->next = current->next;
                if (current == tail) tail = previous;
            }
            free(current);
            puts("Node removed.");
            return;
        }
        previous = current;
        current = current->next;
    } while (current != tail->next);
    puts("Value not found.");
}

static void display(void)
{
    if (tail == NULL) {
        puts("List is empty.");
        return;
    }
    Node *current = tail->next;
    do {
        printf("%d -> ", current->value);
        current = current->next;
    } while (current != tail->next);
    puts("(back to start)");
}

static void clear(void)
{
    if (tail == NULL) return;
    Node *start = tail->next;
    tail->next = NULL;
    while (start != NULL) {
        Node *next = start->next;
        free(start);
        start = next;
    }
    tail = NULL;
}

int main(void)
{
    int choice, value;
    do {
        printf("\n1 Insert at end  2 Delete value  3 Display  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Value: ");
            if (scanf("%d", &value) == 1) insert_end(value);
            break;
        case 2:
            printf("Value to delete: ");
            if (scanf("%d", &value) == 1) delete_value(value);
            break;
        case 3: display(); break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    clear();
    return 0;
}
