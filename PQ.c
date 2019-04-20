// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define FALSE 0
#define TRUE 1
#define INF 0x7FFFFFFF

// rough ideas for PQ

typedef struct PQNode {
    ItemPQ node; // maybe change this variable to item, might make more sense 
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

void addPQ(PQ pq, ItemPQ element) {

    assert (pq != NULL);

    PQNode *new = malloc (sizeof(PQNode *));
	assert(new != NULL);
	// initialise the values in the new PQ node
	new->node.key = element.key;
	new->node.value = element.value;
	new->next = NULL;
		
	if (pq->head == NULL) {
	    pq->head = new;
	    pq->tail = new;
	} else {
	    PQNode *head_hold = pq->head; // easier holder for the head value
	    PQNode *curr = pq->head;
	    PQNode *curr_next = pq->head->next;
	   // PQNode *tail_hold = pq->tail;
	    int added = FALSE;
	    while (curr != NULL && added == FALSE) {
	        // case: same key, so just need to update the value
	        if(curr->node.key == new->node.key) {
	            curr->node.value = new->node.value;
	            added = TRUE;
	        } else if(head_hold->node.key < new->node.key) { // case: higher priority than the head
	            new->next = head_hold;
	            pq->head = new;
	            added = TRUE;
	        } else if (curr_next->node.key < new->node.key) { // case: insert somewhere in the middle
	            curr->next = new;
	            new->next = curr_next; // add more ??
	            added = TRUE;
	        } else if( curr == pq->tail && curr->node.key > new->node.key) { // case: insert at tail
	            curr->next = new;
	            new->next = NULL;
	            pq->tail = new;
	            added = TRUE;
	        }      
	        curr = curr->next;
	        curr_next = curr_next->next;  // this will eventuall point to null so maybe change
	                                        // looping conditions 
	    }
	}

}

ItemPQ dequeuePQ(PQ pq) {

    assert(pq != NULL);
    assert(PQEmpty(pq) != 1);

	ItemPQ throwAway = {0};
	throwAway = pq->head->node; // maybe change node name to element (better use in struct)
	PQNode *old = pq->head;
	// going to run through the queue, to update the above value, until we
	// find the correct node to dequeue, node needs to have the smallest value, 
	// and stick to FIFO order
	if(pq->head == pq->tail) {
	    pq->head = pq->tail = NULL;
	    return throwAway;
    } else {
	
	    // storage variables to keep track of the smallest value and
	    // its key
	    int smallest_v = INF;
	    //int key_index = INF; // might node use this variable 
	    
	    PQNode *curr_prev = pq->head; 
	    PQNode *curr = pq->head->next;
	    PQNode *curr_next = pq->head->next->next;  
	    while (curr != NULL) {
	    // first check the head of the queue
	        if(curr_prev->node.value < smallest_v && curr_prev == pq->head) {
	        // the values of throwAway and old stay the same
	            throwAway = pq->head->node; 
                old = pq->head;  
                pq->head = curr;
                smallest_v = curr_prev->node.value;
            } else if(curr->node.value < smallest_v) {
	            throwAway = curr->node;
	            old = curr;
	            smallest_v = curr->node.value;
	            if(curr == pq->tail) {
	               curr_prev->next = NULL;
	               pq->tail = curr_prev;
	             } else {
	                curr_prev->next = curr_next; 
	            }
	        }
	        curr = curr->next;
	        curr_prev = curr_prev->next;
	        curr_next = curr_next->next;
	    }
	}
	free(old);   
	return throwAway;
}

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
        printf("{%d, %d}", curr->node.key, curr->node.value);
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
