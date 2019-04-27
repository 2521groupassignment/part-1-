// PQ ADT interface for Ass2 (COMP2521)
// Part 2 of Assignment 2
// Jing Jing Fan and Sarah Williams

#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define FALSE 0
#define TRUE 1
#define INF 0x7FFFFFFF

typedef struct PQNode {
    ItemPQ node;  
    struct PQNode *next;
} PQNode;

typedef struct PQRep {

    PQNode *head;
    PQNode *tail;
    
}PQRep;

// make a new priority queue
PQ newPQ() {

    PQRep *new = malloc(sizeof(PQRep *));
    assert(new != NULL);
    new->head = NULL;
    new->tail = NULL;
    
	return new;
}

// check whether the queue is empty
int PQEmpty(PQ p) { 
	if (p->head == NULL){
	    return 1;
	} 
	
	return 0;
	    
}

// Adds item (ItemPQ) to the priority queue.
// If an item with 'key' exists, it's 'value' is updated.

void addPQ(PQ pq, ItemPQ element) {

    assert (pq != NULL);

    PQNode *new = malloc (sizeof(PQNode *));
	assert(new != NULL);
	
	// initialise the values in the new PQ node
	new->node.key = element.key;
	new->node.value = element.value;
	new->next = NULL;
	
	
	PQNode *curr = pq->head;
	int changed = 0;
	// case: item with the key exists, need to update its value
	while (curr != NULL) {
	
	    if (curr->node.key == element.key) {
	        curr->node.value = element.value;
	        changed = 1;  
	    }
	    curr=curr->next;
	}
	
	if (changed == 1) return;
	
	// if the key does not exist, add it to the head of the priority queue
	if (pq->head == NULL) {
        pq->head = new;
        pq->tail = new;
	} else {
        new->next = pq->head;
        pq->head = new;
    }    

}

// Removes and returns the item (ItemPQ) with smallest 'value'.
// For items with equal 'value', observes FIFO.

ItemPQ dequeuePQ(PQ pq) {

    assert (pq != NULL);
    assert (PQEmpty(pq) != 1);
    
    PQNode *itemFound = malloc(sizeof(PQNode));
    itemFound->node.value = 0;
    itemFound->node.key = 0;
    
    ItemPQ itemFoundNode;
   
   // case: only one node in the queue
    if(pq->head != NULL && pq->head == pq->tail) {
        itemFoundNode.value = pq->head->node.value;    
        itemFoundNode.key = pq->head->node.key;         
	    free(pq->head);
	    pq->head = pq->tail = NULL;
	    return itemFoundNode;
    } else {
        // case: more than one node in the queue
        // loop through to find the smallest value and key
        int smallestValue = INF;
	    PQNode *curr = pq->head;
	    PQNode *prev = pq->head;
	    PQNode *itemFoundPrev = NULL;
        while (curr != NULL) {
            if (curr->node.value < smallestValue) {
                itemFound = curr;
                itemFoundPrev = prev;
                smallestValue = curr->node.value;          
                
            }
            prev = curr;
            curr = curr->next;
        }
        itemFoundNode.value = itemFound->node.value;
        itemFoundNode.key = itemFound->node.key;
        
        //itemFound is head
        if (itemFound == pq->head) {
            pq->head = pq->head->next;
            free(itemFound);
        //item found is tail
        } else if (itemFound == pq->tail) {
            pq->tail = itemFoundPrev;
            pq->tail->next = NULL;
            free(itemFound); 
        //item in middle
        } else {
            PQNode *temp = itemFound;
            itemFoundPrev->next = itemFound->next;
            free(temp);
       }          
    }      
    return itemFoundNode;

}

// Updates item with a given 'key' value, by updating that item's value to the given 'value'.
// If item with 'key' does not exist in the queue, no action is taken

void updatePQ(PQ pq, ItemPQ element) {
    
    assert(pq != NULL);

    PQNode *curr = pq->head;
    int updated = FALSE;
    while(curr != NULL && updated == FALSE){
        if(curr->node.key == element.key) { 
            curr->node.value = element.value;
            updated = TRUE;
        }
        curr = curr->next;
   }

}

void  showPQ(PQ pq) {
    
    assert(pq != NULL);  
    
    PQNode *curr;
    for(curr = pq->head; curr != NULL; curr = curr->next){
        printf("{%d,%d}", curr->node.key, curr->node.value);
        if(curr->next != NULL) {
            printf(" - ");
        }
    }
    
}

void  freePQ(PQ pq) {

    assert(pq != NULL);
    PQNode *curr = pq->head;
    PQNode *tmp;
    while( curr!= NULL) {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    
    free(pq);

}


