/*	list.c | An implementation of the methods included in the Lab4 list.h to create a Doubly-Linked List

	Project name: Lab 4 Crawler
	Component name: DLL implementation 

	This file contains implementation for the methods provided in list.h
	q
	Primary Author:	Chris Livingston
	Date Created: 2/7/15	

	Special considerations:  
		n/a
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 


// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>

// ---------------- Local includes  e.g., "file.h"
#include "list.h"
		
#include "string.h"
// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

// set head and tail to NULL
void create (List *list)
{
    list->head = list->tail = NULL;
    
}

// create a new node
ListNode* newNode(){
    ListNode* node;
   // WebPage* page;
    //page = malloc(sizeof(WebPage));
    node = malloc(sizeof(ListNode));
    //node->page = page;
    return node;
}

// add to end of List
void add (List * list, WebPage * data)
{
   
    ListNode * link;
    
    link = calloc (1,sizeof(ListNode));
    link->page = calloc(1,sizeof(WebPage));


    if (! link) {
        fprintf (stderr, "calloc failed.\n");
        exit (EXIT_FAILURE);
    }

    link->page = data;
    link->page->url = data->url;


    if (list->tail == NULL) {
       
        list->head = link;
        list->tail = link;

    }
    else {

        /* Join the two final links together. */
        list->tail->next = link;
        link->prev = list->tail;
        list->tail = link;
            }
}


// deletes the head of the list
ListNode* delete (List * list)
{

    if (list->head == NULL){
        return NULL;
    }
    else{
       
        ListNode * temp = calloc(1,sizeof(ListNode)); 
        temp = list->head;
        temp->page = list->head->page;
        
        if(list->head->next == NULL){
            list->head = NULL; 
        }
        else{
            
            list->head = list->head->next;
            list->head->prev = NULL;
        }

        return temp;
    }
}


// free memory of list
void destroy (List * list)
{
    ListNode * link;
    ListNode * next;
    for (link = list->head; link; link = next) {
        /* Store the next value so that we don't access freed
           memory. */
        next = link->next;
        free (link);

    }
}


