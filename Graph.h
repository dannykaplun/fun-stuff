//Daniel Kaplun. This is the header file for the Graph ADT (Graph.h implementing Depth First Search)

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "List.h"

#define NIL 0
#define UNDEF -2
#define white 0
#define grey 1
#define black 2
// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);


/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);

//int helper (List L, int v);; //possible helper for addEdge and addArc

void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List L); /* Pre: length(S)==getOrder(G) *//*** Other operations ***/
//void visit(Graph G, List L, int u);

Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);



#endif










