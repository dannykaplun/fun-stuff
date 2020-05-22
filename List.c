//---------------------
//Daniel Kaplun
//List.c contains the ADT to lexicographically sort files with the functions written 
//---------------------
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"
#define data1 int

//************gonna need some structs I guess, how do they work?

//-------------------------------------
typedef struct NodeObj        //
{                             //
    data1 data;                 //
    struct NodeObj *next;     //
    struct NodeObj *previous; //
} NodeObj;                    //
typedef NodeObj *Node;        // p.i.h
//--------------------------------------
typedef struct ListObj //
{                      //
    Node front;        //
    Node back;         //
    Node cursor;       //
    data1 indexx;         //
    data1 length;        //
} ListObj;             //
//--------------------------------------

//***********************Constructors and Destructors, how do these work?-----------

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(data1 data)                      //
{                                           //
    Node N = (Node)malloc(sizeof(NodeObj)); // p.i.h
    N->data = data;                         //
    N->next = NULL;                         //
    N->previous = NULL;                     //
    return (N);                             //
} //
//-------------------------------------

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pointerNode)                     //
{                                                    //
    if (pointerNode != NULL && *pointerNode != NULL) //
    {                                                //
        free(*pointerNode);                          // p.i.h
        *pointerNode = NULL;                         //
    }                                                //
} 
//---------------------------------------------------

// Returns reference to new empty List object.
List newList(void)                        //
{                                         //
    List list;                            //
    list = (List)malloc(sizeof(ListObj)); // p.i.h with the casting
    list->front = NULL;                   //
    list->back = NULL;                    //
    list->cursor = NULL;                  //
    list->length = 0;                     //
    list->indexx = -1;                     //
    return (list);                        //
} //
//---------------------------------//

// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S

void freeList(List *pL)                     
{                                                    
    if(pL != NULL && *pL != NULL){
        //printf("in here\n");
	while( !isEmpty(*pL)){
		deleteFront(*pL);
	}
		free(*pL);
		*pL = NULL;
	}                                              
} 
//-----------------------------------------------------

//************************END OF CONSTRUCTORS/DESTRUCTORS------------------------------
//ACCESS FUNCTIONS START HERE***********************
data1 isEmpty(List L)                                        //
{                                                          //
    if (L == NULL)                                         //p.i.h                                      
    {                                                      //
        printf("List error bro: isEmpty returned NULL\n"); //
        exit(1);                                           //
    }                                                      //
    return (L->length == 0);                               // p.i.h
} //
//---------------------------------------------------------------
// Returns the number of elements in L.
data1 length(List L)    
{
	if(L == NULL){
		printf("error in length bc its null in list\n");
		exit(1);
	}
    return L->length; 
} 
//---------------------------
// Returns indexx of cursor element if defined, -1 otherwise.
data1 indexx(List L)    //
{
	if(L == NULL){
		printf("error in indexx bc its null in list\n");
		exit(1);
	}
    return L->indexx; 
} //
//-----------------------
// Returns front element of L. Pre: length()>0
data1 front(List L)                                                 
{                                                                 
    if(L == NULL){
		printf("List Error: calling front() on NULL List Reference\n");
		exit(1);
	}
	if(isEmpty(L) ){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}

	return(L->front->data);                                   
} //
//-----------------------------------------------------------------
// Returns back element of L. Pre: length()>0
data1 back(List L)                                                 //
{                                                                //
    if (L->length <= 0)                                          //
    {                                                            //
        printf("exit bro, back function returns length of 0\n"); //
        exit(1);                                                 //
    }                       
    return (L->back->data);                                      //
} //
//-------------------------------------------------------------------
// Returns cursor element of L. Pre: length()>0, indexx()>=0
data1 get(List L)                                                              //
{                                                                            //
    if (L->length <= 0)                                                      //
    {                                                                        //
        printf("get function exiting bc length is equal to 0\n");            //
        exit(1);                                                             //
    }                                                                        //
    if (L->indexx <= -1)                                                      //
    {                                                                        //
        printf("get function exiting bc indexx is equal to or less than -1"); //
        exit(1);                                                             //
    }                                                             
    return (L->cursor->data);                                                
} 
//---------------------------------------------------------------------------

// Returns true (1) iff Lists A and B are in same state, and return false (0) otherwise
data1 equals(List A, List B)                                     //
{                                                              //
    data1 equals = 0;                                            //
    Node a = NULL;                                             //declaration of variables we will be using                    
    Node b = NULL;                                             //                                                                                     
    if (A == NULL || B == NULL)                                //checks if the lists are valid to be compared          
    {                                                          //
        printf("error in equals, one of the lists is null\n"); //
        exit(1);                                               //
    }                                                          //
    equals = (length(A) == length(B));                         //sets equals to be either 0 or 1               
    a = A->front;                                              //set Node a and Node b to be the front of the list that is being parsed
    b = B->front;                                              //p.i.h think about how you are calling front and length and all that 
    while (equals && a != NULL)                                //
    {                                                          //
        equals = (a->data == b->data);                         //
        a = a->next;                                           //
        b = b->next;                                           //
    }                                                          //
    return equals;                                             //
} //
//-------END OF ACCESS FUNCTIONS-------------************---------------------------------
//MANIPULATION FUNCTIONS START HERE-------------------------------------------------------

void clear(List L) // Resets L to its original empty state.
{
    if (L==NULL)
    {
        printf("it IS empty, in clear. going to return");
        exit(1);
        
    }
    while (L->back != NULL && !isEmpty(L))
    {
        deleteBack(L); //p.i.h
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL; //p.i.h
    L->indexx = -1;
    L->length = 0;
    return;
}

void moveFront(List L) // If L is non-empty, sets cursor under the front element,otherwise does nothing.
{                                                                           
    if(L->length > 0){
		L->cursor = L->front;
		L->indexx = 0;
	}
} 
//---------------------------------------------------------------------------
void moveBack(List L)                                                      // If L is non-empty, sets cursor under the back element,otherwise does nothing.   //
{                                                                          //
    if (L == NULL)                                                         //first check if it is empty                                                          //
    {                                                                      //
        printf("exiting with error from moveback, list parsed is null\n"); //
        exit(1);                                                           //
    }                                                                      //
    if (length(L) > 0)                                                     //
    {                                                                      //
        L->cursor = L->back;                                               //
        L->indexx = length(L) - 1;                                          //
    }                                                                      //
    return;                                                                //
} 
//--------------------------------------------------------------------------
void movePrev(List L) //
{                     // 3 situations here,cursor is defined,cursor not defined
    // cursor is at front and moves back, making it undefined
    if (L->cursor != NULL)               //cursor is defined
    {                                    //
        L->cursor = L->cursor->previous; //p.i.h possible 'previous' issue
        L->indexx--;                      //this will move cursor back
    }                                    //
    if (L->cursor == NULL)               //checks again for all undefined cursors
    {                                    //
        L->indexx = -1;                   //
    }                                    //
    return;                              //
} //
//---------------------------------------------------------------------------
void moveNext(List L)
{
    if(L->cursor == L->back || L->cursor == NULL){
        L->cursor = NULL;
        L->indexx = -1;
    } else {
        L->cursor = L->cursor->next;
        L->indexx++;
    }

    return;
}
//-----------------------------------------------------------------------------
void prepend(List L, data1 data)
{ // Insert new element into L. If L is non-empty,
    // insertion takes place before front element.
    Node t = newNode(data);
    if (L->front == NULL)
    {
        printf("prepending with front being null\n");
        L->front = L->back = t;
    }
    else
    {
        L->front->previous = t;
        t->next = L->front;
        L->front = t;
        //p.i.h do we need indexx++ here?
    }

    if (L->cursor != NULL){
        L->indexx++;
    }
    L->length++;
    return;

// Node temp = newNode(data);

// 	if(L->front == NULL){
// 		L->front = L->back = temp;
// 	}
// 	else{
// 		L->front->previous = temp;
// 		temp->next = L->front;
// 		L->front = temp;
// 		L->indexx++;
// 	}
// 	L->length++;



}
//---------------------------------------------------------------

void append(List L, data1 data)
{
    // // Insert new element into L. If L is non-empty,
    // // insertion takes place after back element.
    // printf("could be here\n");
    Node t = newNode(data);
    //printf("data is: %d\n", data);
    //printList(stdout, L);
    if (L->back == NULL)
    {
      //  printf("L back must be NULL\n");
        L->back = L->front = t;
        //printf("did it\n");
    }
    else
    {
        L->back->next = t;
        t->previous = L->back;
        L->back = t;
    }
    L->length++;
    return;
// Node temp = newNode(data);
// 	if(L->front == NULL){
// 		L->front = L->back = temp;
// 	}
// 	else {
// 		L->back->next = temp;
// 		temp->previous = L->back;
// 		L->back = temp;
// 	}
// 	L->length++;

}
//---------------------------------------------------------------
void insertBefore(List L, data1 data)
{ //insert element before cursor
    Node t = newNode(data);

    if (length(L) <= 0 || indexx(L) < 0)
    {
        printf("insertBefore error, length or indexx is 0>");
        exit(1);
    }

    if (L->cursor == L->front)
    {

        prepend(L, data);

    } else {
    t->previous = L->cursor->previous; //p.i.h make sure you covered all instances
    L->cursor->previous->next = t;
    t->next = L->cursor;
    L->cursor->previous = t;
    L->length++;
    L->indexx++;
    return;

    }


}
//---------------------------------------------------------------
void insertAfter(List L, data1 data) // Insert new element after cursor.
                                   // Pre: length()>0, indexx()>=0
{                                  //insert element before cursor
    Node t = newNode(data);
    if (length(L) <= 0 || indexx(L) < 0)
    {
        printf("insertAfter error, length or indexx is 0>");
        exit(1);
    }
    if (L->cursor == L->back)
    {
        append(L, data);

        return;
    }
    t->next = L->cursor->next; //p.i.h make sure you covered all instances
    L->cursor->next->previous = t;
    t->previous = L->cursor;
    L->cursor->next = t;
    L->length++;
    return;
}
//---------------------------------------------------------------
// void deleteFront(List L)
// { // delete the front element. Pre: length()>0
// printf("yeah yeah in here deletefront\n");
//     Node t = NULL;
//     if(L->cursor == L -> front){
//         L->indexx = -1;
//         L->cursor = NULL;
//     }

//     if(L->cursor != NULL ){
//         L->indexx--;
//     }

//     t = L->front;
//     L->front = L->front->next;
//     L->front->previous = NULL;
//     L->length--;
//     freeNode(&t);
//     return;
// }

void deleteFront(List L){
    //printf("yeah yeah in here deletefront\n");
   Node t = NULL;

   if( L == NULL ){
      printf("deletefront exiting bc L is null\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("deletefront exiting bc isEmpty is true\n");
      exit(1);
   }
   //--------------
    t = L->front;
	L->front = L->front->next;
    //------------
	if(L->front == NULL){
		L->back = NULL;
	}
	else{
		L->front->previous = NULL;
	}
	L->length--;
	freeNode(&t);
}
//---------------------------------------------------------------
void deleteBack(List L)
{ // delete the back element. Pre: length()>0
    Node t = NULL;
    if (L == NULL)
    {
        printf("exiting bc deleteFront has null list");
        exit(1);
    }
    if (isEmpty(L))
    {
        printf("exiting bc deletefront has returned isEmpty");
        exit(1);
    }

    t = L->back; //to be deleted
    if(L->cursor == L->back) {
        L->cursor = NULL;
        L->indexx = -1;
    }
    if (length(L) > 1)
    {
        L->back = L->back->previous;
    }
    L->length--;
    freeNode(&t);
    return;
}
//---------------------------------------------------------------
void deLete(List L)
{
    //delete cursor element, leaving cursor undefined
    //Preconditions: length()>0, indexx()=>0
    //Node t = NULL;
    if (L == NULL)
    {
        printf("exiting with an error from delete function, list parsed is null");
        exit(1);
    }
    if (length(L) <= 0 || indexx(L) < 0)
    {
        printf("exiting with an error bc either length is 0 or indexx is -1");
        exit(1);
    }
    if (indexx(L) >= 0)
    {
        // printf("ive made it into delete\n");
        if (L->cursor == L->front){
            deleteFront(L);
            L->cursor = NULL;
            L->indexx = -1;
            return;
        }
        if (L->cursor == L->back) {
            deleteBack(L);
            L->cursor = NULL;
            L->indexx = -1;
            return;
        }     
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        L->cursor = NULL;
        L->indexx = -1;
        L->length--;
        freeNode(&L->cursor);
        return;
    
    }
}
//---------------------------------------------------------------
//END OF MANIPULATION FUNCTIONS*********************************
//Other functions begin here////////////////////////////////////
void printList(FILE *out, List L)
{
    	Node temp = L->front;
	while(temp != NULL) {
		fprintf(out, "%d ", temp->data);
		temp = temp->next;
	}

}
//---------------------------------------------------------------
List copyList(List L)
{    
    List copy = newList();
    for (Node N = L->front; N != NULL; N = N->next)
    {
        append(copy, N->data);
    }
    return(copy);
}



