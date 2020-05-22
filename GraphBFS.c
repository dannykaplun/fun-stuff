//Daniel Kaplun This is the Graph ADT implementing Graph Theory (Graph.c using Breadth First Search alg)

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define NIL 0
#define INF -1
#define white 0
#define grey 1
#define black 2
typedef struct GraphObj
{
   List *adjacent; 
   int order; //the number of vertices
   int size; //the number of edges
   int source;//label of the vertex that was most recently used as source for BFS
   int *color; //An array of ints (or chars, or strings) 
   int *parent; //An array 
   int *distance; //An array of ints whose ith element is the distance

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
    G->distance = malloc(sizeof(int) * (n + 1));
    G->adjacent = malloc(sizeof(List) * (n+1));
    G->order = n;
	G->size = 0;
	G->source = NIL;

	for(int i = 0; i<n+1; i++){
		G->adjacent[i] = newList();
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->color[i] = white;
	}
	return G;
}

// Function freeGraph() frees all dynamic memory associated with the Graph
// *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
	for (int i = 0; i <= getOrder(*pG); i++){
		freeList(&(*pG)->adjacent[i]);
	}
	free((*pG)->adjacent);
	free((*pG)->distance);
	free((*pG)->color);
	free((*pG)->parent);
    //--------freeing here--------
	free(*pG);
	*pG = NULL;
}


/*** Access functions ***/
//Functions getOrder() and getSize() return the corresponding
// field values, and getSource() returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called
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
//getDist() returns the
// distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called. 
int getDist(Graph G, int u){
    if(G == NULL) {
        printf("exiting with null from getDist\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("exiting with null from getDist #\n");
		exit(1);
    }
    return G->distance[u];
}
//------------
//Function getPath() appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
// value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must
// be called before getPath(). Functions getParent(), getDist() and getPath() all have the 
// precondition 1<= u <= getOrder(G) .
void getPath(List L, Graph G, int u){

    if(G == NULL || getSource(G) == NIL) {
        printf("exiting from getPath bc graph is null or source is NILL\n"); 
        exit(1);
        }
    if(u < 1 || u > getOrder(G))
    {
        printf("exiting from getPath either u<1 or u>order\n");
        exit(1);
    }
    
    if(u == getSource(G)){
        append(L, u);
    }
    else if(G->parent[u] == NIL){
        prepend(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
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
    //printf("u is %d\n", u);
        printf("exiting with null because u<1 or u>n at addArc\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        printf("Exiting with null because v<1 or v>n at addArc\n");
        exit(1);
    }
//-----------------------------------
    moveFront(G->adjacent[u]);
	while(indexx(G->adjacent[u]) > -1 && v > get(G->adjacent[u])) {  //find where v is greater then the value of adjacent[u]
		moveNext(G->adjacent[u]);                                   //keep it moving
	}
	if(indexx(G->adjacent[u]) == -1){                                
		append(G->adjacent[u], v);  //make sure to orint in append to find seg fault
    }
	else{
		insertBefore(G->adjacent[u], v); //test inserbefore for seg faults
    }
	G->size++;
}
//-------------------------
 // Function BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly. 
void BFS(Graph G, int s){
    if(G == NULL)
    {
        printf("exiting with null bc BFS was called with null graph\n");
        exit(1);
    }
    if(s < 1 || s > getOrder(G))
    {
        printf("exiting with null bc BFS was called with null graph\n");
        exit(1);
    }
    //------------------------------
    for(int i = 0; i < (G->order+1); i++)
    {
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = white;
    }
    List Q = newList();
    G->source = s;
    G->color[s] = grey;
    G->distance[s] = NIL;
    append(Q,s);
    int temp;
    int u; // so we dont redeclare in while loop cuz C is stoopid
    while(length(Q) > 0)
    {
        temp = front(Q);
        deleteFront(Q);

        moveFront(G->adjacent[temp]);


        while(indexx(G->adjacent[temp]) > -1)
        { 
            u = get(G->adjacent[temp]);

            if(G->color[u] == white)
            {
                G->color[u] =  grey;
                G->parent[u] = temp;
                G->distance[u] = G->distance[temp] + 1;
                append(Q,u);
            }
            moveNext(G->adjacent[temp]);
        }
        //printf("going to set to black\n");
        G->color[temp] = black;
    }
    freeList(&Q);
    Q = NULL;
}




//     G->source = s;
//     G->color[s] = grey;
//     G->distance[s] = 0;
//     List Queue = newList();
//     prepend(Queue,s);
//     int tempBack;
//     int u;


//     while(length(Queue) > 0) {
//         tempBack = back(Queue); 
//         deleteBack(Queue); //dequeue
//         moveFront(G->adjacent[tempBack]);
//         printf("tempback is: %d\n", tempBack);
//         printf("printing list for adjacent at indece tempbck");
//         printList(stdout, G->adjacent[tempBack]);
//         //printf("indexx is: %d\n", indexx(G->adjacent[tempBack]) );


//         while(indexx(G->adjacent[tempBack]) > -1) {
//             u = get(G->adjacent[tempBack]);
//             printf("in while loop,, remember, its the indexx. u is: %d\n", u);

//             if(G->color[u] == white) { //if it hasnt been touched yet
//                 printf("yes cc\n");
//                 G->color[u] = grey;
//                 G->distance[u] = G->distance[u] + 1;
//                 G->parent[u] = tempBack;    //found from 1 so 1 is the prepend
//                 prepend(Queue, u); 
//                 // printf("printing list for you again: ");
//                 printList(stdout, G->adjacent[u]);
//                 printf("leaving if in here\n");
//             }
//             printf("moving onnn\n");
//             moveNext(G->adjacent[u]);
//         }
//         //G->color[u] = black;
//         //printf("color is: %d\n", G->color[u]);

//     }
//     printf("going into freeList\n");
//     freeList(&Queue);
//     printf("came out of freeList\n");
//     Queue = NULL;

 

/*** Other operations ***/

// Finally, function printGraph() prints the adjacency list
// representation of G to the file pointed to by out. The format of this representation should match the above
// examples, so all that is required by the client is a single call to printGraph().
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
