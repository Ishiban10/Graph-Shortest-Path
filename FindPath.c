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

int main(int argc, char* argv[]) {

    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // gets number in first line which is the number of vertices and then saves it
    char buffForVert[10];
    fgets(buffForVert, 10, in);
    int vertices = atoi(buffForVert);

    // creates new graph
    Graph G = newGraph(vertices);

    int v1, v2;
    char line[20];
    while (fgets(line, 20, in)) {
        if (sscanf(line, "%i %i", &v1, &v2) == 2) {
            if (v1 == 0 && v2 == 0) {
                break;
            } else {
                addEdge(G, v1, v2);
            }   
        }
    }

    //print graph to output file
    printGraph(out, G);
    fprintf(out, "\n");
    int pathCounts = 0;
    List shortestPath = newList();
    int source, destination;
    while (fgets(line, 20, in)) {
        if (sscanf(line, "%i %i", &source, &destination) == 2) {
            if (source == 0 && destination == 0) {
                break;
            } else {
                BFS(G, source);
                getPath(shortestPath, G, destination);
            
                int lenShortestPath = length(shortestPath);

                bool impossible = false;
                moveFront(shortestPath);
                for (int i = 0; i < lenShortestPath; i++) {
                    if (get(shortestPath) == NIL) {
                        impossible = true;
                        break;
                    }
                    moveNext(shortestPath);
                }

                if (impossible) {
                    fprintf(out, "The distance from %i to %i is infinity\n", source, destination);
                    fprintf(out, "No %i-%i path exists\n", source, destination);
                }
                else {
                    fprintf(out, "The distance from %i to %i is %i\n", source, destination, lenShortestPath-1);
                    fprintf(out, "A shortest %i-%i path is: ", source, destination);
                    moveFront(shortestPath);
                    for (int i = 0; i < lenShortestPath; i++) {
                        fprintf(out, "%i ", get(shortestPath));
                        moveNext(shortestPath);
                    }
                    fprintf(out, "\n");
		    pathCounts += 1;
                }
                clear(shortestPath);
            }   
        }
    }
   // fprintf(out, "Number of shortest paths: %i\n", pathCounts);
    freeGraph(&G);
    freeList(&shortestPath);
    return 0;
}
