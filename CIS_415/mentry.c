#include "mentry.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <ctype.h>

//Allen Roush, 951441052, CIS 415 Project 0 
//This is my own work

MEntry *me_get(FILE *fd){
    MEntry *me = (MEntry *)malloc(sizeof(MEntry)); // create the Mentry and malloc it
    int i = 0;
    size_t buffsize = 0; //setting buffersize to 0 tells getline to dynamically allocate the buffer space 
    size_t fullstringlength = 0; 
    char *buffer = NULL; 
    char entryarr[3][100]; // two dimensional array to store mail entries in sets of 3, 
    char *ztemp; // storing tokenized zipcode
    char *surtemp; // storing tokenized surname
    int entry = 0;
    
    
    if (me != NULL && fd != NULL){
        
        
        for(i = 0; i < 3; i++) {
            entry = getline(&buffer,&buffsize, fd);    
            if (entry > 0) {
              strcpy(entryarr[i], buffer); // copy it to position i of the entryarray, 
              fullstringlength += strlen(buffer);
            }
            else {
              free(buffer);
              free(me);
              return NULL;
            }
        } 
        
        free(buffer); // buffer is dynamically allocated and needs to be explicitly freed when no longer being used 
        
        //printf("FullstringLength: %d\n", fullstringlength); 
        me->full_address = (char*)malloc(sizeof(char) * (fullstringlength + 1));
        strcpy(me->full_address, entryarr[0]); 
        strcat(me->full_address, entryarr[1]); 
        strcat(me->full_address, entryarr[2]);
        //printf("Full Address: \n%s\n", me->full_address);    
            
        surtemp = strtok(entryarr[0], ",");
        me->surname = (char*)malloc(sizeof(char) * (strlen(surtemp) + 1));
        strcpy(me->surname, surtemp); // assign surname  
        //printf("Surname: %s\n", me->surname);
        
        
        if (!(me->house_number = atoi(strtok(entryarr[1], " ")))){ // if this reads a number, assign it to house number, else assign 0 
            me->house_number = 0; 
        }
        //printf("House Number: %d\n", me->house_number);
        
        ztemp = strtok(entryarr[2], ","); // remove the comma in the 2nd line 
        ztemp = strtok(NULL, " "); //and the two spaces 
        ztemp = strtok(NULL, " \n");
        
        
        me->zipcode = (char*)malloc(sizeof(char) * (strlen(ztemp) + 1));
        
        
        strcpy(me->zipcode, ztemp); 
        //printf("Zipcode : %s\n", ztemp);
        return me; 
    }
    else{
        free(me);
        return NULL;
    }
}

int me_compare(MEntry *me1, MEntry *me2){
    int seq; // surname comparison 
    int zeq; // zipcode comparison
    int heq; // house number comparison 
    
    for(int i = 0; me1->surname[i]; i++){
        me1->surname[i] = tolower(me1->surname[i]);
    }
    
    for(int i = 0; me2->surname[i]; i++){
        me2->surname[i] = tolower(me2->surname[i]);
    }
    

    //printf("zipcode1: %s", me1->zipcode);
    //printf("zipcode2: %s", me2->zipcode);
    
    seq = strcmp(me1->surname, me2->surname); //strcmp return -1, 0, or 1 based on a lexiographical comparison of the passed in strings 
    //printf("I read the surnames  as %s %s", me1->surname, me2->surname);
    //printf("and the surname compairson returns %d", seq);
    if(seq == 0){
        //printf("I read the zipcodes as %s %s", me1->zipcode, me2->zipcode); 
        zeq = strcmp(me1->zipcode, me2->zipcode);
        //printf("And the zipcode comparison returns %d", zeq);
        //printf("zeq returend: %d\n", zeq); // figure out why this returns 10 
        if(zeq == 0){
           // printf("I read the house numbers as %d %d", me1->house_number, me2->house_number);
            heq = me1->house_number - me2->house_number;
            //printf("And the house number comparison returns %d", heq);
            if(heq == 0){
                return 0;
            }
            else if (heq < 0){
                return -1; 
            }
            else if (heq > 0){
                return 1; 
            }
        }
        else if (zeq < 0){
            return -1; 
        }
        else if (zeq > 0){
            return 1; 
        }
    }
    else if (seq < 0){
        return -1; 
    }
    else {
        return 1; 
    }
    return 0;
}


void me_destroy(MEntry *me){
    free(me->zipcode); // free internal char*'s 
    free(me->surname);
    free(me->full_address);
    free(me); // then free the mentry object 
}

void me_print(MEntry *me, FILE *fd){
    fprintf(fd, "%s", me->full_address);
}

unsigned long me_hash(MEntry *me, unsigned long size){
    char a;
    unsigned long hashvalue = 0;
    for(int i = 0; me->surname[i]; i++){
        //me->surname[i] = tolower(me1->surname[i]);
        a = me->surname[i];
        a = tolower(a);
        hashvalue += a + 31 * hashvalue;
    } // make sure each character read in is lowercase 
    
    
    for(int k = 0; me->zipcode[k] != '\0'; k++){
        hashvalue += me->zipcode[k] + 31 * hashvalue; 
    }
    
    hashvalue += me->house_number; 
    return hashvalue % size; 

}
  
    
/*
  char catstring[100];
  char *hnumber = (char*)malloc(sizeof(char) * 10);
  
  
  //printf("Zipcode: %s", me->zipcode);
  strcpy(catstring, me->surname); 
  strcat(catstring, me->zipcode); 
  sprintf(hnumber, "%d", me->house_number); // convert int to string 
  strcat(catstring, hnumber);
  //printf("Catstring is: %s", catstring);
  
  unsigned long hashvalue = 0; 
 //
  for (int i = 0; catstring[i] != '\0'; i++){  
    hashvalue = catstring[i] + 31 * hashvalue;
  }
  
  free(hnumber);
  return hashvalue % size;
  */

/*
 * 
 *         fscanf(fd, "%19[^,]", sname); // reads a string of non-comma characters and stops at the first comma, maximum num of characters to read is 19
        fscanf(fd, "%*[^\n]\n", NULL); // skip the line 
        if (!fscanf(fd, "%d", &hnumber)){ // read the beginning of the 2nd line to find the house number, or if not found, set to 0 
            hnumber = 0;
        }
        
        
        //printf("the value of sname is: %d\n", hnumber); 
        
*/         
