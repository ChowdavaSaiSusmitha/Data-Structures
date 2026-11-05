#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11
#define KEY_COUNT 7

typedef struct Node {
    int key;
    struct Node *next;
} Node;

static int hash_key(int key)
{
    int index = key % TABLE_SIZE;
    return index < 0 ? index + TABLE_SIZE : index;
}

static void print_table(const int table[TABLE_SIZE], const int used[TABLE_SIZE])
{
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("%2d: ", i);
        if (used[i]) printf("%d", table[i]);
        else printf("-");
        putchar('\n');
    }
}

static void linear_probe(const int keys[KEY_COUNT])
{
    int table[TABLE_SIZE] = {0}, used[TABLE_SIZE] = {0};
    for (int k = 0; k < KEY_COUNT; ++k) {
        int base = hash_key(keys[k]), step;
        for (step = 0; step < TABLE_SIZE; ++step) {
            int slot = (base + step) % TABLE_SIZE;
            if (!used[slot]) {
                table[slot] = keys[k];
                used[slot] = 1;
                break;
            }
        }
        if (step == TABLE_SIZE) puts("Table is full; a key was skipped.");
    }
    puts("\nLinear probing:");
    print_table(table, used);
}

static void quadratic_probe(const int keys[KEY_COUNT])
{
    int table[TABLE_SIZE] = {0}, used[TABLE_SIZE] = {0};
    for (int k = 0; k < KEY_COUNT; ++k) {
        int base = hash_key(keys[k]), step;
        for (step = 0; step < TABLE_SIZE; ++step) {
            int slot = (base + step * step) % TABLE_SIZE;
            if (!used[slot]) {
                table[slot] = keys[k];
                used[slot] = 1;
                break;
            }
        }
        if (step == TABLE_SIZE)
            printf("Could not place %d with quadratic probing.\n", keys[k]);
    }
    puts("\nQuadratic probing:");
    print_table(table, used);
}

static void separate_chaining(const int keys[KEY_COUNT])
{
    Node *buckets[TABLE_SIZE] = {NULL};
    for (int k = 0; k < KEY_COUNT; ++k) {
        int slot = hash_key(keys[k]);
        Node *node = malloc(sizeof *node);
        if (node == NULL) {
            perror("Unable to allocate node");
            for (int i = 0; i < TABLE_SIZE; ++i)
                while (buckets[i] != NULL) {
                    Node *next = buckets[i]->next;
                    free(buckets[i]);
                    buckets[i] = next;
                }
            exit(EXIT_FAILURE);
        }
        node->key = keys[k];
        node->next = buckets[slot];
        buckets[slot] = node;
    }
    puts("\nSeparate chaining:");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("%2d: ", i);
        for (Node *node = buckets[i]; node != NULL; node = node->next)
            printf("%d -> ", node->key);
        puts("NULL");
    }
    for (int i = 0; i < TABLE_SIZE; ++i)
        while (buckets[i] != NULL) {
            Node *next = buckets[i]->next;
            free(buckets[i]);
            buckets[i] = next;
        }
}

int main(void)
{
    int keys[KEY_COUNT];
    printf("Enter %d integer keys: ", KEY_COUNT);
    for (int i = 0; i < KEY_COUNT; ++i)
        if (scanf("%d", &keys[i]) != 1) {
            puts("Invalid input.");
            return 1;
        }
    linear_probe(keys);
    quadratic_probe(keys);
    separate_chaining(keys);
    return 0;
}
