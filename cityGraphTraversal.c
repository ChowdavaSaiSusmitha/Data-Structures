#include <stdio.h>

#define MAX_CITIES 20

static int graph[MAX_CITIES][MAX_CITIES];
static int visited[MAX_CITIES];
static int city_count;

static void depth_first(int start)
{
    visited[start] = 1;
    printf("%d ", start + 1);
    for (int next = 0; next < city_count; ++next)
        if (graph[start][next] && !visited[next])
            depth_first(next);
}

static void breadth_first(int start)
{
    int queue[MAX_CITIES], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current + 1);
        for (int next = 0; next < city_count; ++next)
            if (graph[current][next] && !visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
    }
}

int main(void)
{
    int start;
    printf("Number of cities (1-%d): ", MAX_CITIES);
    if (scanf("%d", &city_count) != 1 || city_count < 1 ||
        city_count > MAX_CITIES) {
        puts("Invalid number of cities.");
        return 1;
    }
    puts("Enter the adjacency matrix (0=no edge, 1=edge):");
    for (int i = 0; i < city_count; ++i)
        for (int j = 0; j < city_count; ++j)
            if (scanf("%d", &graph[i][j]) != 1 ||
                (graph[i][j] != 0 && graph[i][j] != 1)) {
                puts("Matrix entries must be 0 or 1.");
                return 1;
            }
    printf("Starting city (1-%d): ", city_count);
    if (scanf("%d", &start) != 1 || start < 1 || start > city_count) {
        puts("Invalid starting city.");
        return 1;
    }

    puts("Cities reachable using BFS:");
    breadth_first(start - 1);
    putchar('\n');
    for (int i = 0; i < city_count; ++i) visited[i] = 0;
    puts("Cities reachable using DFS:");
    depth_first(start - 1);
    putchar('\n');
    return 0;
}
