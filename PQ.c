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

void addPQ(PQ pq, ItemPQ element) {

    assert (pq != NULL);

    PQNode *new = malloc (sizeof(PQNode *));
	assert(new != NULL);
	// initialise the values in the new PQ node
	new->node.key = element.key;
	new->node.value = element.value;
	new->next = NULL;
	int added = FALSE;
	
	//adding to empty PQ	
	if (pq->head == NULL) {
	    pq->head = new;
	    pq->tail = new;
	    added = TRUE;
	    return;
	} else {
	    PQNode *head_hold = pq->head; 
	    PQNode *curr = pq->head;
	    PQNode *curr_next = pq->head->next;
	    added = FALSE;
	    while (curr != NULL && added == FALSE) {
	        // case: same key, so just need to update the value
	        if(curr->node.key == new->node.key) {
	            curr->node.value = new->node.value;
	            added = TRUE;
	        } 
	        
	        else if(head_hold->node.key < new->node.key) { // case: higher priority than the head
	            new->next = head_hold;
	            pq->head = new;
	            added = TRUE;
	        } else if (curr_next->node.key < new->node.key) { // case: insert somewhere in the middle
	            curr->next = new;
	            new->next = curr_next;
	            added = TRUE;
	        } else if( curr == pq->tail && curr->node.key > new->node.key) { // case: insert at tail
	            curr->next = new;
	            new->next = NULL;
	            pq->tail = new;
	            added = TRUE;
	        }   
	        curr = curr->next;
	                                        // looping conditions 
	    }
	    if(curr == pq->tail && added == FALSE){
	        pq->tail->next = new;
	        pq->tail = new;
	   }
	}
	

}

ItemPQ dequeuePQ(PQ pq) {

    assert (pq != NULL);
    assert (PQEmpty(pq) != 1);

    //if only one node in queue
    
    //if more than one node in queue
        //while loop to find smallest value and key
        
    //outside while loop store node to remove in a temp
    //removal when head
    //removal when tail
    //removal when middle
    PQNode *itemFound = malloc(sizeof(PQNode));
    itemFound->node.value = 0;
    itemFound->node.key = 0;
    
    ItemPQ itemFoundNode;
    itemFoundNode.value = 8;                        // used these values to test in output
    itemFoundNode.key = 8;                          // 
    
    if(pq->head != NULL && pq->head == pq->tail) {
        itemFoundNode.value = pq->head->node.value;    
        itemFoundNode.key = pq->head->node.key;         
	    free(pq->head);
	    pq->head = pq->tail = NULL;
	    return itemFoundNode;
    } else {
        int smallest_v = INF;
	    PQNode *curr = pq->head;
	    PQNode *prev = pq->head;
	    PQNode *itemFound_prev = NULL;
        while (curr != NULL) {
            if (curr->node.value < smallest_v) {
                itemFound = curr;
                itemFound_prev = prev;
                smallest_v = curr->node.value;          
                
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
            pq->tail = itemFound_prev;
            pq->tail->next = NULL;
            free(itemFound); 
        //item in middle
        } else {
            PQNode *temp = itemFound;
            itemFound_prev->next = itemFound->next;
            free(temp);
       }          
    }      
    return itemFoundNode;

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

