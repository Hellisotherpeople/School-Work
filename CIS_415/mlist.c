#include "mlist.h"
#include "mentry.h"
#include <stdlib.h>
#include <stdio.h>

//Allen Roush, 951441052, CIS 415 Project 0 
//This is my own work

typedef struct mlistnode {
	struct mlistnode *next;
	MEntry *entry;
} Mlistnode;

typedef struct mlist {
        size_t size;  // current size of the hash table 
        Mlistnode **list; // pointer to the linked list 
} Mlist;


/* ml_create - created a new mailing list */
Mlist *ml_create(void) {
	Mlist *p;

	if ((p = (Mlist *)malloc(sizeof(Mlist))) != NULL) {
		p->size = 20;
                p->list = (Mlistnode **) malloc(sizeof(Mlistnode *) * p->size);

                if((p->list != NULL)){
                    for(unsigned int i = 0; i < p->size; i++){
                        p->list[i] = NULL;  // Initialize each pointer to null
                    }
                }
                else{
                    free(p); 
                }
	}
	//printf("The size is: %d\n", p->size);
	return p;
}

/* ml_lookup - looks for MEntry in the hash table, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me) {
        unsigned long hashvalue = me_hash(me, ml->size);
        //printf("The hash hasehd to: %d\n", hashvalue);

	Mlistnode *q = ml->list[hashvalue];
        
        for (; q != NULL; q = q->next){
            if(me_compare(q->entry, me) == 0){
                return q->entry; 
            }
        }
        return NULL; 
}


/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me) {
	Mlist *list;
	Mlistnode *node;

	list = *ml;
        unsigned long hashvalue = me_hash(me, list->size); // get the passed in nodes hash value 
            if (ml_lookup(list, me) != NULL){
                    return 1; // it was a duplicate 
            }
            node = (Mlistnode *)malloc(sizeof(Mlistnode));
            if (node == NULL){
                    return 0; // malloced failed 
            }
                    
            node->entry = me; // set the entry to the passed in value 
            node->next = NULL;// the next will be null 
            Mlistnode *tmp = list->list[hashvalue]; //get the head node from the list 
            size_t new_size = list->size * 2;
            int counter = 1; 
            
            if (tmp == NULL){ // If the head of the bucket is null  
                //printf("Shit was null yo");
                list->list[hashvalue] = node; // set the head to be a new node 
            }

            else{
                for (; tmp->next != NULL; tmp = tmp->next){
                counter++; // counts how many nodes are in the bucket 
                }
                tmp->next = node; // add the node 
            }

            if (counter >= 20){ // check if we need to resize ;
                Mlistnode **newlist = (Mlistnode **)malloc(sizeof(Mlistnode*) * (new_size)); // create the new list  
                
                for(unsigned int j = 0; j < (new_size); j++){
                    newlist[j] = NULL;
                }
                
                unsigned int i = 0; 
                Mlistnode *nextnode = NULL; 
                Mlistnode *newhead = NULL; 
                
                for(; i < list->size; i++){ // go through the old list 
                    tmp = list->list[i]; // head node of the bucket at value i
    
                    for(; tmp != NULL; tmp = nextnode){ // loop over the items in that bucket 
                        nextnode = tmp->next;
                        //printf("The value I has is: %d\n", me_hash(tmp->entry, new_size));
                        newhead = newlist[me_hash(tmp->entry, (new_size))];
                        if (newhead == NULL) // If the bucket is empty 
                        {
                            newlist[me_hash(tmp->entry, (new_size))] = tmp; // add the new node to the front of the bucket 
                            newlist[me_hash(tmp->entry, (new_size))]->next = NULL;
                            
                        }
                        else
                        {
                            for (; newhead->next != NULL; newhead = newhead->next){  // else, go through the bucket until you hit the last non-null node 
                            }
                            newhead->next = tmp; // add the node to the new head of the bucket
                            tmp->next = NULL; // set end of the linked list to be null
                        }
                        
                    }
                }
            
            free(list->list); // free's the array of pointers 
            list->list = newlist;  //make the list point to the newlist 
            list->size = new_size; 
            fprintf(stderr, "The table has been resized\n");
        }
        return 1; // success 
    }

void ml_destroy(MList *ml){
    Mlistnode *curnode = NULL;
    Mlistnode *nextnode = NULL;
    
    
    for(unsigned int i = 0; i < ml->size; i++){
        curnode = ml->list[i];
        while (curnode != NULL){
            nextnode = curnode->next; 
            me_destroy(curnode->entry);
            free(curnode);
            curnode = nextnode; 
        }
    }
    free(ml->list);
    free(ml);
}

