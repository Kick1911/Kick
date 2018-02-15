#include <stdio.h>
#include <malloc.h>

typedef struct graph{
	int E;
	struct graph** V;
}graph;

typedef graph* Graph;

void alloc_graph(Graph* g, size_t size){
	*g = (Graph)malloc(sizeof(graph));
	if(size)
		(*g)->V = (Graph*)malloc(sizeof(Graph) * size);
}

int main(int argc, char** argv){
	Graph g;
	/* Allocate memory */
	alloc_graph(&g, 5);
	alloc_graph(g->V, 0);
	alloc_graph(g->V + 4, 0);

	/* Use */
	g->V[0]->E = 6;
	g->V[4]->E = 11;
	printf("%d\n", g->V[0]->E);
	printf("%d\n", g->V[4]->E);

	/* Free memory */
	free(g->V[0]);
	free(g->V[4]);
	free(g->V);
	free(g);
	return 0;
}
