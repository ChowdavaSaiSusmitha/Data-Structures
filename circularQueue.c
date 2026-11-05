#include <stdio.h>

#define CAPACITY 8

typedef struct {
    int data[CAPACITY];
    int front;
    int size;
} CircularQueue;

static void initialize(CircularQueue *queue)
{
    queue->front = 0;
    queue->size = 0;
}

static int enqueue(CircularQueue *queue, int value)
{
    if (queue->size == CAPACITY) return 0;
    int rear = (queue->front + queue->size) % CAPACITY;
    queue->data[rear] = value;
    ++queue->size;
    return 1;
}

static int dequeue(CircularQueue *queue, int *value)
{
    if (queue->size == 0) return 0;
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % CAPACITY;
    --queue->size;
    return 1;
}

static void display(const CircularQueue *queue)
{
    if (queue->size == 0) puts("Queue is empty.");
    for (int i = 0; i < queue->size; ++i)
        printf("%d ", queue->data[(queue->front + i) % CAPACITY]);
    putchar('\n');
}

int main(void)
{
    CircularQueue queue;
    initialize(&queue);
    int choice, value;
    do {
        printf("\n1 Enqueue  2 Dequeue  3 Display  0 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:
            printf("Value: ");
            if (scanf("%d", &value) == 1)
                puts(enqueue(&queue, value) ? "Inserted." : "Queue is full.");
            break;
        case 2:
            if (dequeue(&queue, &value)) printf("Removed: %d\n", value);
            else puts("Queue is empty.");
            break;
        case 3: display(&queue); break;
        case 0: break;
        default: puts("Invalid choice.");
        }
    } while (choice != 0);
    return 0;
}
