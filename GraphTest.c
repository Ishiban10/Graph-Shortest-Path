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

int main(void) {

    Graph G = newGraph(6);
    /*
    addEdge(G,1,2);
    addEdge(G,1,4);
    addEdge(G,2,4);
	printf("size first: %i \n", getSize(G));
    addEdge(G,2,4);
	printf("size second: %i \n", getSize(G));
    addEdge(G,2,3);
    addEdge(G,3,6);
   // addEdge(G,9,10);
    */
	addArc(G, 2, 4);
	printf("Size first: %i\n", getSize(G));
	addArc(G, 2, 4);
	printf("Size second: %i\n", getSize(G));
	addArc(G, 3, 5);
	addArc(G, 5, 6);
	addArc(G, 3, 4);

    printGraph(stdout, G);
   
   // printf("Order: %i\n", getOrder(G)); 
    
    int source = 5;
    int destination = 2; 
    List shortestPath = newList();
    BFS(G,source);
	
//    printf("Parent of %i: %i\n", 1, getParent(G, 1));
//    printf("Parent of %i: %i\n", 6, getParent(G,6));
	
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
        fprintf(stdout, "The distance from %i to %i is infinity\n", source, destination);
        fprintf(stdout, "No %i-%i path exits\n", source, destination);
    } else {
        fprintf(stdout, "The distance from %i to %i is %i\n", source, destination, lenShortestPath-1);
        fprintf(stdout, "The shortest %i-%i path is: ", source, destination);
        moveFront(shortestPath);
        for (int i = 0; i < lenShortestPath; i++) {
            fprintf(stdout, "%i ", get(shortestPath));
            moveNext(shortestPath);
        }
        fprintf(stdout, "\n");
    }
    clear(shortestPath);
   // printList(stdout, shortestPath);

      
    source = 1;
    destination = 2;

  //  List shortestPath = newList();
    BFS(G,source);
    getPath(shortestPath, G, destination);
    
    //printList(stdout, shortestPath);	

    impossible = false;
    moveFront(shortestPath);
    for (int i = 0; i < lenShortestPath; i++) {
   	 if (get(shortestPath) == NIL) {
              impossible = true;
              break;
         }
         moveNext(shortestPath);
    }

   // printList(stdout, shortestPath);
    lenShortestPath = length(shortestPath);

    if (impossible) {
        fprintf(stdout, "The distance from %i to %i is infinity\n", source, destination);
        fprintf(stdout, "No %i-%i path exits\n", source, destination);
    } else {
        fprintf(stdout, "The distance from %i to %i is %i\n", source, destination, lenShortestPath-1);
        fprintf(stdout, "The shortest %i-%i path is: ", source, destination);
        moveFront(shortestPath);
        for (int i = 0; i < lenShortestPath; i++) {
            fprintf(stdout, "%i ", get(shortestPath));
            moveNext(shortestPath);
        }
        fprintf(stdout, "\n");
    }
    clear(shortestPath);
    
    freeGraph(&G);
    freeList(&shortestPath);
	
}
