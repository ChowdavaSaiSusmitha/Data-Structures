#include <stdio.h>

#define CAPACITY 10

typedef struct {
    int data[CAPACITY];
    int front;
    int size;
} Deque;

static int insert_front(Deque *deque, int value)
{
    if (deque->size == CAPACITY) return 0;
    deque->front = (deque->front - 1 + CAPACITY) % CAPACITY;
    deque->data[deque->front] = value;
    ++deque->size;
    return 1;
}

static int insert_rear(Deque *deque, int value)
{
    if (deque->size == CAPACITY) return 0;
    int rear = (deque->front + deque->size) % CAPACITY;
    deque->data[rear] = value;
    ++deque->size;
    return 1;
}

static int remove_front(Deque *deque, int *value)
{
    if (deque->size == 0) return 0;
    *value = deque->data[deque->front];
    deque->front = (deque->front + 1) % CAPACITY;
    --deque->size;
    return 1;
}

static int remove_rear(Deque *deque, int *value)
{
    if (deque->size == 0) return 0;
    int rear = (deque->front + deque->size - 1) % CAPACITY;
    *value = deque->data[rear];
    --deque->size;
    return 1;
}

static void display(const Deque *deque)
{
    if (deque->size == 0) puts("Deque is empty.");
    for (int i = 0; i < deque->size; ++i)
        printf("%d ", deque->data[(deque->front + i) % CAPACITY]);
    putchar('\n');
}

int main(void)
{
    Deque deque = {{0}, 0, 0};
    int choice, value;
    do {
        printf("\n1 Insert front  2 Insert rear  3 Remove front\n"
               "4 Remove rear   5 Display       0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
        case 2:
            printf("Value: ");
            if (scanf("%d", &value) == 1) {
                int inserted = choice == 1 ? insert_front(&deque, value)
                                           : insert_rear(&deque, value);
                puts(inserted ? "Inserted." : "Deque is full.");
            }
            break;
        case 3:
        case 4:
            if ((choice == 3 ? remove_front(&deque, &value)
                             : remove_rear(&deque, &value)))
                printf("Removed: %d\n", value);
            else
                puts("Deque is empty.");
            break;
        case 5: display(&deque); break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    return 0;
}
