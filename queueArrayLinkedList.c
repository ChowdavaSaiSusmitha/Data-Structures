#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static int items[CAPACITY], front = 0, count;
static Node *list_front, *list_rear;

static void enqueue(int value, int use_list)
{
    if (!use_list) {
        if (count == CAPACITY) {
            puts("Array queue is full.");
            return;
        }
        items[(front + count) % CAPACITY] = value;
        ++count;
        return;
    }
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("Unable to allocate node");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    if (list_rear != NULL) list_rear->next = node;
    else list_front = node;
    list_rear = node;
}

static void dequeue(int use_list)
{
    if (!use_list) {
        if (count == 0) {
            puts("Array queue is empty.");
            return;
        }
        printf("Removed: %d\n", items[front]);
        front = (front + 1) % CAPACITY;
        --count;
        return;
    }
    if (list_front == NULL) {
        puts("Linked queue is empty.");
        return;
    }
    Node *old = list_front;
    printf("Removed: %d\n", old->value);
    list_front = old->next;
    if (list_front == NULL) list_rear = NULL;
    free(old);
}

static void display(int use_list)
{
    if (!use_list) {
        if (count == 0) puts("Array queue is empty.");
        for (int i = 0; i < count; ++i)
            printf("%d ", items[(front + i) % CAPACITY]);
        putchar('\n');
        return;
    }
    if (list_front == NULL) puts("Linked queue is empty.");
    for (Node *node = list_front; node != NULL; node = node->next)
        printf("%d ", node->value);
    putchar('\n');
}

int main(void)
{
    int choice, type, value;
    do {
        printf("\n1 Enqueue  2 Dequeue  3 Display  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice >= 1 && choice <= 3) {
            printf("Implementation (1 array, 2 linked list): ");
            if (scanf("%d", &type) != 1 || (type != 1 && type != 2)) {
                puts("Invalid implementation.");
                continue;
            }
            if (choice == 1) {
                printf("Value: ");
                if (scanf("%d", &value) == 1) enqueue(value, type == 2);
            } else if (choice == 2) {
                dequeue(type == 2);
            } else {
                display(type == 2);
            }
        } else if (choice != 0) {
            puts("Invalid choice.");
        }
    } while (choice != 0);
    while (list_front != NULL) {
        Node *next = list_front->next;
        free(list_front);
        list_front = next;
    }
    return 0;
}
