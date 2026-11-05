#include <stdio.h>

#define MAX_VERTICES 20
#define INF 10000000

int main(void)
{
    int graph[MAX_VERTICES][MAX_VERTICES];
    int distance[MAX_VERTICES], visited[MAX_VERTICES] = {0}, vertices, source;
    printf("Number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &vertices) != 1 || vertices < 1 ||
        vertices > MAX_VERTICES) {
        puts("Invalid number of vertices.");
        return 1;
    }
    puts("Enter the weight matrix (0=no edge; weights must be non-negative):");
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < vertices; ++j)
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                puts("Invalid edge weight.");
                return 1;
            }
    printf("Source vertex (1-%d): ", vertices);
    if (scanf("%d", &source) != 1 || source < 1 || source > vertices) {
        puts("Invalid source vertex.");
        return 1;
    }
    for (int i = 0; i < vertices; ++i) distance[i] = INF;
    distance[source - 1] = 0;

    for (int iteration = 0; iteration < vertices; ++iteration) {
        int current = -1;
        for (int i = 0; i < vertices; ++i)
            if (!visited[i] &&
                (current == -1 || distance[i] < distance[current]))
                current = i;
        if (current == -1 || distance[current] == INF) break;
        visited[current] = 1;
        for (int next = 0; next < vertices; ++next)
            if (!visited[next] && graph[current][next] > 0 &&
                distance[current] + graph[current][next] < distance[next])
                distance[next] = distance[current] + graph[current][next];
    }

    puts("Shortest distances from source:");
    for (int i = 0; i < vertices; ++i) {
        if (distance[i] == INF)
            printf("%d -> %d: unreachable\n", source, i + 1);
        else
            printf("%d -> %d: %d\n", source, i + 1, distance[i]);
    }
    return 0;
}
