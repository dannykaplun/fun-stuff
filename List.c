//---------------------
//Daniel Kaplun, 1606945, PA1
//List.c contains the ADT for PA1, Lex will call on List to implement functions such as append
//---------------------
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
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
    data1 index;         //
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
} //
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
    list->index = -1;                     //
    return (list);                        //
} //
//---------------------------------//

// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S

void freeList(List *pointerList)                     //
{                                                    //
    if (pointerList != NULL && *pointerList != NULL) //
    {       
        Node t = (*pointerList) ->front;            //
        while (t != NULL)                            //
        {                                            //
            Node tbd = t;
            t = t->next;
            free(tbd);                               //
        }                                            //
        free(*pointerList);                          //
        *pointerList = NULL;                         // p.i.h
    }
    return;                                                //
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
data1 length(List L)    //
{                     //
    return L->length; //
} //
//---------------------------
// Returns index of cursor element if defined, -1 otherwise.
data1 index(List L)    //
{                    //
    return L->index; //
} //
//-----------------------
// Returns front element of L. Pre: length()>0
data1 front(List L)                                                 //
{                                                                 //
    if (L->length <= 0)                                           //
    {                                                             //
        printf("exit bro, front function returns length of 0\n"); //
        exit(1);                                                  //
    }                                                             //
    return (L->front->data);                                      //
} //
//-----------------------------------------------------------------
// Returns back element of L. Pre: length()>0
data1 back(List L)                                                 //
{                                                                //
    if (L->length <= 0)                                          //
    {                                                            //
        printf("exit bro, back function returns length of 0\n"); //
        exit(1);                                                 //
    }                                                            //
    return (L->back->data);                                      //
} //
//-------------------------------------------------------------------
// Returns cursor element of L. Pre: length()>0, index()>=0
data1 get(List L)                                                              //
{                                                                            //
    if (L->length <= 0)                                                      //
    {                                                                        //
        printf("get function exiting bc length is equal to 0\n");            //
        exit(1);                                                             //
    }                                                                        //
    if (L->index <= -1)                                                      //
    {                                                                        //
        printf("get function exiting bc index is equal to or less than -1"); //
        exit(1);                                                             //
    }                                                                        //
    return (L->cursor->data);                                                //
} //
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
    L->index = -1;
    L->length = 0;
    return;
}

void moveFront(List L)                                                      // If L is non-empty, sets cursor under the front element,otherwise does nothing.
{                                                                           //
    if (L == NULL)                                                          //first check if it is empty                                                         //
    {                                                                       //
        printf("exiting with error from movefront, list parsed is null\n"); //
        exit(1);                                                            //
    }                                                                       //
    if (length(L) > 0)                                                      //
    {                                                                       //
        L->cursor = L->front;                                               //
        L->index = 0;                                                       //p.i.h ordering?                                                                 //
    }                                                                       //
    return;                                                                 //
} //
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
        L->index = length(L) - 1;                                          //
    }                                                                      //
    return;                                                                //
} //
//--------------------------------------------------------------------------
void movePrev(List L) //
{                     // 3 situations here,cursor is defined,cursor not defined
    // cursor is at front and moves back, making it undefined
    if (L->cursor != NULL)               //cursor is defined
    {                                    //
        L->cursor = L->cursor->previous; //p.i.h possible 'previous' issue
        L->index--;                      //this will move cursor back
    }                                    //
    if (L->cursor == NULL)               //checks again for all undefined cursors
    {                                    //
        L->index = -1;                   //
    }                                    //
    return;                              //
} //
//---------------------------------------------------------------------------
void moveNext(List L)
{
    if(L->cursor == L->back || L->cursor == NULL){
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->cursor = L->cursor->next;
        L->index++;
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
        L->front = L->back = t;
    }
    else
    {
        L->front->previous = t;
        t->next = L->front;
        L->front = t;
        //p.i.h do we need index++ here?
    }

    if (L->cursor != NULL){
        L->index++;
    }
    L->length++;
    return;
}
//---------------------------------------------------------------

void append(List L, data1 data)
{
    // Insert new element into L. If L is non-empty,
    // insertion takes place after back element.
    Node t = newNode(data);
    if (L->back == NULL)
    {
        L->back = L->front = t;
    }
    else
    {
        L->back->next = t;
        t->previous = L->back;
        L->back = t;
    }
    L->length++;
    return;
}
//---------------------------------------------------------------
void insertBefore(List L, data1 data)
{ //insert element before cursor
    Node t = newNode(data);

    if (length(L) <= 0 || index(L) < 0)
    {
        printf("insertBefore error, length or index is 0>");
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
    L->index++;
    return;
    }
}
//---------------------------------------------------------------
void insertAfter(List L, data1 data) // Insert new element after cursor.
                                   // Pre: length()>0, index()>=0
{                                  //insert element before cursor
    Node t = newNode(data);
    if (length(L) <= 0 || index(L) < 0)
    {
        printf("insertAfter error, length or index is 0>");
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
void deleteFront(List L)
{ // delete the front element. Pre: length()>0
    Node t = NULL;
    if(L->cursor == L -> front){
        L->index = -1;
        L->cursor = NULL;
    }

    if(L->cursor != NULL ){
        L->index--;
    }

    t = L->front;
    L->front = L->front->next;
    L->front->previous = NULL;
    L->length--;
    freeNode(&t);
    return;
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
        L->index = -1;
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
void delete(List L)
{
    //delete cursor element, leaving cursor undefined
    //Preconditions: length()>0, index()=>0
    //Node t = NULL;
    if (L == NULL)
    {
        printf("exiting with an error from delete function, list parsed is null");
        exit(1);
    }
    if (length(L) <= 0 || index(L) < 0)
    {
        printf("exiting with an error bc either length is 0 or index is -1");
        exit(1);
    }
    if (index(L) >= 0)
    {
        // printf("ive made it into delete\n");
        if (L->cursor == L->front){
            deleteFront(L);
            L->cursor = NULL;
            L->index = -1;
            return;
        }
        if (L->cursor == L->back) {
            deleteBack(L);
            L->cursor = NULL;
            L->index = -1;
            return;
        }     
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        L->cursor = NULL;
        L->index = -1;
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
    Node T = NULL;
    data1 checker = 1;

    if (L == NULL)
    {
        printf("exiting bc list in printlist is null");
        exit(1);
    }
    T = L->front;
    while (checker == 1)
    {
        printf("%d", T->data);
        T = T->next;
        if (T == NULL)
        {
            checker = 0;
        }
    }
            printf("\n");

    return;
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



//from quiz 1 (below)

//  data1  searchList(List L, data1 x) {
//      moveFront(L);

//      for (data1 i = 0; i < L->length; i++)
//      {
//          if(x == get(L)) {
//              return index(L);
//          }
//          moveNext(L);
//      }

//      L->cursor = NULL;
//      L->index = -1;
//      return L->index;
//  }

    // data1  isPalindrome(List L) {
    //     List temp = newList();
    //     moveFront(L);


    //     for(data1 i = 0; i < length(L)/2; i++) {        
    //         append(temp, get(L));
    //         moveNext(L);
    //     }
    //     moveFront(temp);
    //     moveBack(L);

    //     for(data1 i = 0; i < length(temp); i++) {
    //         if(get(L) != get(temp)){
    //             return 0;
    //         }
    //         moveNext(temp);
    //         movePrevious(L);
    //     }

    //    return 1;
    // }


/*
Your function will perform a linear search in L for the target x.  
Your function will return the lowest index (i.e. nearest the front) at which the target is found, 
if it is found, and will return -1 if the target is not found.  
Upon return, the input list will have its cursor under the found element, if found, 
and will have it's cursor in the undefined state if the target is not found.



*/
