#include <stdio.h>

#define MAX_VERTICES 20
#define INF 10000000

int main(void)
{
    int distance[MAX_VERTICES][MAX_VERTICES];
    int vertices;
    printf("Number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &vertices) != 1 || vertices < 1 ||
        vertices > MAX_VERTICES) {
        puts("Invalid number of vertices.");
        return 1;
    }
    puts("Enter the directed weight matrix (-1 for no edge; diagonal is 0):");
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < vertices; ++j) {
            int weight;
            if (scanf("%d", &weight) != 1 || (i == j && weight != 0) ||
                (i != j && weight < -1)) {
                puts("Invalid matrix value.");
                return 1;
            }
            distance[i][j] = weight == -1 ? INF : weight;
        }

    for (int via = 0; via < vertices; ++via)
        for (int from = 0; from < vertices; ++from)
            for (int to = 0; to < vertices; ++to)
                if (distance[from][via] != INF &&
                    distance[via][to] != INF &&
                    distance[from][via] + distance[via][to] < distance[from][to])
                    distance[from][to] =
                        distance[from][via] + distance[via][to];

    puts("All-pairs shortest-distance matrix:");
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j)
            if (distance[i][j] == INF) printf("INF ");
            else printf("%d ", distance[i][j]);
        putchar('\n');
    }
    return 0;
}
