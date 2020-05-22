//Daniel Kaplun. This is the Graph ADT implementing Graph Theory (Graph.c using Depth First Search)

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
//#include "List.h"



void visit(Graph G, List S, int u, int* time);

typedef struct GraphObj
{
   List *adjacent; 
   int order; //the number of vertices
   int size; //the number of edges
   int source;//label of the vertex that was most recently used as source for BFS
   int *color; //An array of ints (or chars, or strings) 
   int *parent; //An array 
   int *discover;
   int *finish;

}GraphObj;

/*** Constructors-Destructors ***/

//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a G having
//n vertices and no edges. 
Graph newGraph(int n){
    printf("Making a new graph in newGraph function\n");
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->color = malloc(sizeof(int) * (n + 1));
    G->parent = malloc(sizeof(int) * (n + 1));
    G->adjacent = malloc(sizeof(List) * (n+1));
    G->discover = malloc(sizeof(int) * (n + 1));
    G->finish = malloc(sizeof(int) * (n + 1));
    G->order = n;
	G->size = 0;
	G->source = NIL;

	for(int i = 0; i<n+1; i++){
		G->adjacent[i] = newList();
		G->parent[i] = NIL;
		G->color[i] = white;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
	}
   printf("leaving new graph\n");
	return G;
}

// Function freeGraph() frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
	for (int i = 0; i <= getOrder(*pG); i++){
		freeList(&(*pG)->adjacent[i]);
	}
	free((*pG)->adjacent);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);

	free(*pG);
	*pG = NULL;
   printf("leaving free graph\n");
}


/*** Access functions ***/
//Functions getOrder() and getSize() return the corresponding
int getOrder(Graph G){  //number of vertices
    if(G == NULL){
        printf("exiting from getOrder with G being NULL\n");
        exit(1);
    }
    return G->order;
}
//------------
int getSize(Graph G){
        if(G == NULL){
        printf("exiting from getSize with G being NULL\n");
        exit(1);
    }
    return G->size;
}
//------------
int getSource(Graph G){
    if(G == NULL){
        printf("exiting from getSource with G being NULL\n");
        exit(1);
    }
    return G->source;
}
//------------
// Function getParent() will return the parent of vertex u in the BreadthFirst tree created by BFS(), 
// or NIL if BFS() has not yet been called.
int getParent(Graph G, int u){
    //printf("u is: %d\n", u);
    if (G == NULL){
		printf("exiting with null from getParent\n");
		exit(1);
	}
    if(u < 1 || u > getOrder(G)){
        printf("exiting with null from getParent #\n");
		exit(1);
    }
	return G->parent[u];
}
//------------
int getDiscover(Graph G, int u) {
    if(G == NULL) {
        printf("exiting with null from getDiscover\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("exting with null from getDiscover\n");
		exit(1);
    }
    return G->discover[u];
}
//--------------
int getFinish(Graph G, int u) {
    if(G == NULL) {
        printf("exiting with null from getFinish\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("exting with null from getFinish\n");
		exit(1);
    }
    return G->finish[u];
}

/*** Manipulation procedures ***/
//Function makeNull() deletes all edges of G, restoring it to its original
// (no edge) state.
void makeNull(Graph G){
    if(G == NULL) {
        printf("Exiting makeNull because of null graph\n");
        exit(1);
    }

    for(int i = 0; i <= getOrder(G); i++) {
        clear(G->adjacent[i]);
    }
    return;
}

// addEdge() inserts a new edge joining u to v, i.e. u is 
// added to the adjacency List of v, and v to the adjacency List of u. Your program is
// required to maintain these lists in sorted order by increasing labels. 
void addEdge(Graph G, int u, int v){
    if(G == NULL) {
        printf ("exiting with null bc graph is null at addEdge\n");
        exit(1);
    }

    if(u < 1 || u > getOrder(G)){
        printf("exiting with null because u<1 or u>n at addEdge\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        printf("Exiting with null because v<1 or v>n at addEdge\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;   
   //printf("leaving addedge\n");
}


//addArc() inserts a new directed edge
// from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v). Both addEdge()
// and addArc() have the precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v){

    if(G == NULL) {
        printf ("exiting with null bc graph is null at addArc\n");
        exit(1);
    }

    if(u < 1 || u > getOrder(G)){
        printf("exiting with null because u<1 or u>n at addArc\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        printf("Exiting with null because v<1 or v>n at addArc\n");
        exit(1);
    }
//-----------------------------------

    moveFront(G->adjacent[u]);
	while(index(G->adjacent[u]) > -1 && v > get(G->adjacent[u])) {  //find where v is greater then the value of adjacent[u]
		moveNext(G->adjacent[u]);                                   //keep it moving
	}
	if(index(G->adjacent[u]) == -1){                                
		append(G->adjacent[u], v);  //make sure to orint in append to find seg fault
    }
	else{
		insertBefore(G->adjacent[u], v); //test inserbefore for seg faults
    }
	G->size++;
   
}
//DFS AND VISIT HERE----------------------------$$$$$$$$$$$$------

void DFS(Graph G, List L) {
    if (G == NULL) { 
        printf("exiting with null from DFS\n");
        exit(1);
    }
    
    //if (length(L) == getOrder(G)) {
        for (int i = 1; i < getOrder(G)+1; i++) { //getOrder(G)+1?
            G->color[i] = white;
            G->parent[i] = NIL;
            G->discover[i] = UNDEF;
            G->finish[i] = UNDEF;
        }
        int u;
        
        int time = 0;
        moveFront(L);

        while (index(L) != -1) {
            u = get(L);
            if (G->color[u] == white) {
                visit(G, L, u, &time);
            }
            moveNext(L);
        }

        //delete original values in stack
        for (int i = 1; i < getOrder(G)+1; i++) {
            deleteBack(L);
        }
 

} 
//---------------------
void visit(Graph G, List S, int u, int* time) {

    
    G->discover[u] = ++(*time);
    G->color[u] = grey;

    List tempList = G->adjacent[u];
    moveFront(tempList);

    while (index(tempList) != -1) {

        int value = get(tempList);

        if (G->color[value] == white) {
            G->parent[value] = u;
            visit(G, S, value, time);
        }
        moveNext(tempList);
    }

    G->color[u] = black;  
    
    G->finish[u] = ++(*time);
    prepend(S, u);  

}
//-------------END DFS AND VISIT FUNCTIONS HERE-----
/*** Other operations ***/

//-----------------------------------
Graph transpose(Graph G) {
    Graph transposed = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->adjacent[i]);

        if (length(G->adjacent[i]) == 0) {     //in case its at empty spot
            continue;
        }

        else {                                 //most of it will go in here, when length is not zero
        
            while (index(G->adjacent[i]) != -1) {
                addArc(transposed, get(G->adjacent[i]), i);         //creating edges here backwards
                moveNext(G->adjacent[i]);
            }
        }
    }
    return transposed;
}
//-----------------------------------
Graph copyGraph(Graph G) {
    Graph copied = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++){
        moveFront(G->adjacent[i]);
        if (length(G->adjacent[i]) == 0) {     //in case its at empty spot
            continue;
        }

        else {         //most of it will go in here, when length is not zero

            while (index(G->adjacent[i]) != -1) {
                addArc(copied, i, get(G->adjacent[i]));         //creating edges here, exact same as graph passed in
                moveNext(G->adjacent[i]);
            }
        }
    }
   return copied;

}
//-----------------------------------
void printGraph(FILE* out, Graph G){
	if(G == NULL) {
		printf("exiting will null from print graph");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
        moveFront(G->adjacent[i]);
		for (int j = 0; j < length(G->adjacent[i]); j++)
        {
            fprintf(out, "%d ",get(G->adjacent[i]));
            moveNext(G->adjacent[i]);
        }
		fprintf(out, "\n");
    }
}
