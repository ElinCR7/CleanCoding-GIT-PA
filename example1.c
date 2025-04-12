#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    int* visited;
    Node** adjacency_lists;
} Graph;

// ======== UTILITARE ========

Node* create_node(int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->visited = calloc(vertices, sizeof(int));
    graph->adjacency_lists = malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
    }
    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(Graph* graph, int edge_count) {
    int src, dest;
    printf("Introdu %d muchii (nodurile sunt indexate de la 0):\n", edge_count);
    for (int i = 0; i < edge_count; i++) {
        printf("Muchia %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void reset_visited(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// ======== DFS ========

int found = 0;

void DFS(Graph* graph, int current, int target) {
    graph->visited[current] = 1;

    if (current == target) {
        found = 1;
        return;
    }

    Node* temp = graph->adjacency_lists[current];
    while (temp) {
        if (!graph->visited[temp->data]) {
            DFS(graph, temp->data, target);
        }
        temp = temp->next;
    }
}

// ======== MAIN ========

int main() {
    int vertices, edges;
    printf("Cate noduri are graful? ");
    scanf("%d", &vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &edges);

    Graph* graph = create_graph(vertices);
    insert_edges(graph, edges);

    int src, dest;
    printf("Verificam daca exista drum intre doua restaurante.\n");
    printf("Introdu primul restaurant: ");
    scanf("%d", &src);
    printf("Introdu al doilea restaurant: ");
    scanf("%d", &dest);

    DFS(graph, src, dest);

    if (found)
        printf("Exista drum intre restaurantele %d si %d.\n", src, dest);
    else
        printf("NU exista drum intre restaurantele %d si %d.\n", src, dest);

    return 0;
}
