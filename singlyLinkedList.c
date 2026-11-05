#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static Node *head;

static Node *make_node(int value)
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("Unable to allocate node");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static void insert_front(int value)
{
    Node *node = make_node(value);
    node->next = head;
    head = node;
}

static void insert_back(int value)
{
    Node *node = make_node(value);
    Node **link = &head;
    while (*link != NULL)
        link = &(*link)->next;
    *link = node;
}

static void delete_front(void)
{
    if (head == NULL) {
        puts("List is empty.");
        return;
    }
    Node *old = head;
    head = head->next;
    free(old);
    puts("First node removed.");
}

static void delete_value(int value)
{
    Node **link = &head;
    while (*link != NULL && (*link)->value != value)
        link = &(*link)->next;
    if (*link == NULL) {
        puts("Value not found.");
        return;
    }
    Node *old = *link;
    *link = old->next;
    free(old);
    puts("Node removed.");
}

static void display(void)
{
    Node *current = head;
    if (current == NULL) {
        puts("List is empty.");
        return;
    }
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
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
}

int main(void)
{
    int choice, value;
    do {
        printf("\n1 Insert front  2 Insert end  3 Delete first  4 Delete value\n"
               "5 Display       0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1)
            break;
        switch (choice) {
        case 1:
            printf("Value: ");
            if (scanf("%d", &value) == 1) insert_front(value);
            break;
        case 2:
            printf("Value: ");
            if (scanf("%d", &value) == 1) insert_back(value);
            break;
        case 3: delete_front(); break;
        case 4:
            printf("Value to delete: ");
            if (scanf("%d", &value) == 1) delete_value(value);
            break;
        case 5: display(); break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    clear();
    return 0;
}
