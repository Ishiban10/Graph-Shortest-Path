//-----------------------//
// Name: Ishaan Das      //
// CruzID: isdas         //
// Assignment Name: pa2  // 
//-----------------------//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"

typedef struct GraphObj {
    List* lists;
    char* colors;
    int* parents;
    int* distances;
    int order;
    int size;
    int recentSource;
} GraphObj;

Graph newGraph(int n) {
    Graph new = malloc(sizeof(GraphObj));
    if (new != NULL) {
        new->lists = malloc((n+1) * sizeof(List));
	for (int i = 0; i <= n; i++) {
		new->lists[i] = newList();
	}	
	
        new->colors = malloc((n+1) * sizeof(char));
        //memset(new->colors, 'w', n+1);

        new->parents = malloc((n+1) * sizeof(int));
        //memset(new->parents, NIL, n+1);

        new->distances = malloc((n+1) * sizeof(int));
        //memset(new->distances, INF, n+1);

        new->order = n;

        new->size = 0;

        new->recentSource = NIL;

        return new;
    } else {
        printf("Graph Error: calling newGraph() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void freeGraph(Graph* pG) {
    if ((*pG) != NULL) {
        int len = (*pG)->order;
        for (int i  = 0; i <= len; i++) {
            freeList(&((*pG)->lists[i]));
        }
	
	free((*pG)->lists);
        free((*pG)->colors);
        free((*pG)->parents);
        free((*pG)->distances);

        free(*pG);
        *pG = NULL;
    } else {
        printf("Graph Error: calling freeGraph() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getOrder(Graph G) {
    if (G != NULL) {
        return G->order;
    } else {
        printf("Graph Error: calling getOrder() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getSize(Graph G) {
    if (G != NULL) {
        return G->size;
    } else {
        printf("Graph Error: calling getSize() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getSource(Graph G) {
    if (G != NULL) {
        return G->recentSource;
    } else {
        printf("Graph Error: calling getSource() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getParent(Graph G, int u) {
    if (G != NULL) {
        if ((1 <= u && u <= getOrder(G))) {
	    if (getSource(G) != NIL) {
                return G->parents[u];
	    } else {
		return NIL;	
	    }
        } else {
            printf("Graph Error: calling getParent() when vertex out of range\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Graph Error: calling getParent() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getDist(Graph G, int u) {
    if (G != NULL) {
        if ((1 <= u && u <= getOrder(G))) {
            if (getSource(G) != NIL) {       
                return G->distances[u];
	    } else {
		return INF;
	    }
        } else {
            printf("Graph Error: calling getDist() when vertex out of range\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Graph Error: calling getDist() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void getPath(List L, Graph G, int u) {
    if (G != NULL) {
        if (getSource(G) != NIL) {
            if ((1 <= u && u <= getOrder(G))) {
                if (L != NULL) {
                    // need to figure it out and insert here --> it's going to be the printPath, except instead of printing you append to List
                    if (u == G->recentSource) {
                        append(L, G->recentSource);
                    } else if (G->parents[u] == NIL) {
                        append(L, NIL);
                    } else {
                        getPath(L, G, G->parents[u]);
                        append(L, u);
                    }

                } else {
                    printf("Graph Error: calling getPath() on a NULL List reference\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("Graph Error: calling getPath() when vertex out of range\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Graph Error: calling getPath() when source is NIL\n");
            exit(EXIT_FAILURE);
        }

    } else {
        printf("Graph Error: calling getPath() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void makeNull(Graph G) {
    if (G != NULL) {    
        int len = G->order;
        for (int i = 0; i <= len; i++) {
            clear(G->lists[i]);
        }
        G->size = 0;
    } else {
        printf("Graph Error: calling makeNull() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void addEdge(Graph G, int u, int v) {
    if (G != NULL) {
        if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
	    bool addU = true;
	    bool addV = true;
	    int lenU = length(G->lists[u]);
	    int lenV = length(G->lists[v]);
	    if (lenU >= 1) {
	   	 moveFront(G->lists[u]);
	   	 for (int i = 0; i < lenU; i++) {
			if (get(G->lists[u]) == v) {
		    	    addU = false;
		   	    break;
			}
			moveNext(G->lists[u]);
	    	 }
		moveFront(G->lists[u]);
	    }

	    if (lenV >= 1) {
	   	 moveFront(G->lists[v]);
		 for (int i = 0; i < lenV; i++) {
		 	if (get(G->lists[v]) == u) {
			    addV = false;
			    break;
			}      
			moveNext(G->lists[v]);
		 }
		moveFront(G->lists[v]);
	    }
 	    //moveFront(G->lists[u]);
	    //moveFront(G->lists[v]);	    
		
            //for v to list[u]
            if (addU) {
            if (length(G->lists[u]) == 0) {
		append(G->lists[u], v);
		moveFront(G->lists[u]);
	    } else if (v <= front(G->lists[u])) {
		prepend(G->lists[u], v);
		moveFront(G->lists[u]);
	    } else if (v >= back(G->lists[u])) {
		append(G->lists[u], v);
		moveFront(G->lists[u]);
	    } else {
		while (1) {
		    if (v <= get(G->lists[u])) {
		   	insertBefore(G->lists[u], v);
			break;	
		    }
		    moveNext(G->lists[u]);
		}
		moveFront(G->lists[u]);
	    }
	    }

	    //for u to list[v]
	    if (addV) {
            if (length(G->lists[v]) == 0) {
                append(G->lists[v], u);
                moveFront(G->lists[v]);
            } else if (u <= front(G->lists[v])) {
                prepend(G->lists[v], u);
                moveFront(G->lists[v]);
            } else if (u >= back(G->lists[v])) {
                append(G->lists[v], u);
                moveFront(G->lists[v]);
            } else {
                while (1) {
                    if (u <= get(G->lists[v])) {
                        insertBefore(G->lists[v], u);
                        break;
                    }
                    moveNext(G->lists[v]);	    
                }
                moveFront(G->lists[v]);
            }
	    }

        if (addU && addV) { 
            G->size += 1;
        }
        
        } else {
            printf("Graph Error: calling addEdge() when vertex out of range\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Graph Error: calling addEdge() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void addArc(Graph G, int u, int v) {
    if (G != NULL) {
        if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {

            bool addU = true;
            int lenU = length(G->lists[u]);
            if (lenU >= 1) {
                moveFront(G->lists[u]);
                for (int i = 0; i < lenU; i++) {
                    if (get(G->lists[u]) == v) {
                        addU = false;
                        break;
                    }
                    moveNext(G->lists[u]);
                    }
                moveFront(G->lists[u]);
            }


            if (addU) {
                if (length(G->lists[u]) == 0) {
                    append(G->lists[u], v);
                    moveFront(G->lists[u]);
                } else if (v <= front(G->lists[u])) {
                    prepend(G->lists[u], v);
                    moveFront(G->lists[u]);
                } else if (v >= back(G->lists[u])) {
                    append(G->lists[u], v);
                    moveFront(G->lists[u]);
                } else {
                    while (1) {
                        if (v <= get(G->lists[u])) {
                        insertBefore(G->lists[u], v);
                        break;
                        }
                        moveNext(G->lists[u]);
                    }
                    moveFront(G->lists[u]);
                }
                G->size += 1;
            }

        } else {
            printf("Graph Error: calling addArc() when vertex out of range\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Graph Error: calling addArc() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}


void BFS(Graph G, int s) {
    if (G != NULL) {
        //intitlize colors, distance, parents arrays
       // memset(G->colors, 'w', G->order+1);
       //  memset(G->distances, INF, G->order+1);
       // memset(G->parents, NIL, G->order+1);
	
	for (int i = 0; i <= G->order; i++) {
	    G->colors[i] = 'w';
	    G->distances[i] = INF;
	    G->parents[i] = NIL;
	}
	
//	for (int i = 0; i <= G->order; i++) {
//		printf("Parent of %i: %i\n", i, G->parents[i]);
//		printf("Color of %i: %c\n", i, G->colors[i]);
//		printf("Distance of %i: %i\n", i, G->distances[i]);
//	}

        //discover the source
        G->recentSource = s;
        G->colors[s] = 'g';
        G->distances[s] = 0;
        G->parents[s] = NIL;

        List Q = newList();
        append(Q, s);

        int dequeued;
        int found;
        while(length(Q) != 0) {
            dequeued = front(Q);
            deleteFront(Q);
	    if (length(G->lists[dequeued]) > 0) {
                moveFront(G->lists[dequeued]);
                for (int i = 0; i < length(G->lists[dequeued]); i++) {
                    found = get(G->lists[dequeued]);

                    if (G->colors[found] == 'w') {
                        G->colors[found] = 'g';
                        G->distances[found] = G->distances[dequeued] + 1;
                        G->parents[found] = dequeued;
                        append(Q, found);
                    }

                    moveNext(G->lists[dequeued]);
                }
	    }
            G->colors[dequeued] = 'b';
        }
	freeList(&Q);
    } else {
        printf("Graph Error: calling BFS() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}


void printGraph(FILE* out, Graph G) {
    if (out != NULL) {
        if (G != NULL) {
                int found;
                for (int o = 1; o <= G->order; o++) {
                    fprintf(out, "%i: ", o);
                    int len = length(G->lists[o]);
                    if (len > 0) {
    		        moveFront(G->lists[o]);
                        for (int l = 0; l < len; l++) {
                            found = get(G->lists[o]);
                            fprintf(out, "%i ", found);
                            moveNext(G->lists[o]);
                        }
		    } 
                    fprintf(out, "\n");
                }
        } else {
            printf("Graph Error: calling printGraph() on a NULL Graph reference\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Graph Error: calling printGraph() on a NULL output file reference\n");
        exit(EXIT_FAILURE);
    }
}
