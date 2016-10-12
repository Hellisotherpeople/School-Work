/*Author = Allen Roush, while working with Lindy Meyers
 *
 * CIS 314 Fall 2015
 * Lab 3 
 * Program1.C: An (almost) functional Direct Mapped Cache Simulator 
 * 
 *  will print the values in the cache after the first 10 cache references
 * and again after finishing all cache references.
 * 
 * LIMITATIONS: Cannot print correctly when the valid is 0. Unknown reason
 * Lindy and I both have this due to similar implementations and it's the best I can get
*/

#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#define FILE_NAME "address.txt"

// -------------------------------------- STRUCTURES --------------------------------------------------------------------
    struct Cache_line{ // structure to hold the cache object 
        char mem[26];
        int valid;
        char tag[10];
    };
    
    struct hmstructure{    // structure to hold the hits and misses. 
        int hit;
        int miss;
    };
// ----------------------------------------  MAIN PROGRAM -----------------------------------------------------------------
int main(void) {

    FILE *address_file;
    address_file = fopen(FILE_NAME, "r");  
    
    
    struct Cache_line Cache[8]; //create cache 
    struct hmstructure HitMiss[1];  //create structure for holding the hits/misses 
    HitMiss[0].hit = 0;         // initialize the values to 0 
    HitMiss[0].miss = 0;
    int i; 
    for(i=0; i<8; i++){
        Cache[i].valid = 0;     // initialize the valid bits on the cache to 0 
    }
    
    readText(address_file, Cache, HitMiss);
    return 0;
}

int readText(FILE *address_file, struct Cache_line *Cache, struct hmstructure *HitMiss){
    /*
    * reads addresses from address.txt
    * calls function to print cache and hit/miss status after ten addresses, and upon completion
    */
    char string[32];
    int i =0;
    while(i<501){ // 500 address's 
        if(fscanf(address_file, "%s", string)==1){
            CacheAddress(string, Cache, HitMiss);
        }
        else{
            printvalues(HitMiss, i);
            printCache(Cache);
            return 0;
        }
        if (i == 10){
            printf("\n");
            printf("Doesn't print out correctly if the valid is 0... Nastly little bug");
            printvalues(HitMiss, i);
            printCache(Cache);
        }
        i++;
    }
    fclose(address_file);       // clean up 
    return 0;
}

int CacheAddress(char *address, struct Cache_line *Cache, struct hmstructure *HitMiss){
    /*
    * Sets the value for the index, tag, and data given an address.
    * I use character array's for repersenting the tag, memory address and offset, unfortunately I think that this in tandem with some other lower level C stuff that I'm not really sure about is what I believe is causing my error 
    */
    int i;
    char tag[10]; // each tag is 8 + 2 = 10 bits long 
    int index;
    char mem[26] = {'M', 'E', 'M', '['}; 
    char offset = address[8];
    
    for (i=0; i<8; i++){
        tag[i] = address[i];
        mem[i+4] = address[i];  //gets the mem addresses into the right places 
        mem[i+15] = address[i]; 
    }
    
    // Stuff I saw on stack overflow for converting from char to int 
    if('0'<=offset && offset<='9'){
            
        offset = offset - '0';
    }
    
    if('A'<=offset && offset<='F'){
        offset = offset- 'A' + 10;
    }

        
    if (offset>7){
        index = offset - 8;
        char temp = '8';
        tag[8] = temp;
    }
    else{
        index = offset;
        char temp = '0';
        tag[8] = temp;
    }
    
    // I didn't know to handle the memory in any better way than this. It's kind of hackey 
    tag[9] = '\0';
    mem[12] = offset;
    mem[13] = '0'; 
    mem[14] = ':';
    mem[23] = offset;
    mem[24] = 'F';
    mem[25] = ']';
    mem[26] = '\0';
    
    // Do the writeCache now that you created one 
    writeCache(Cache, index, tag, mem, HitMiss);
    return 0;
}

int writeCache(struct Cache_line *Cache, int index, char *tag, char *mem, struct hmstructure *HitMiss){
    /*
    * Checks if an address is in the Cache.
    * First checks if the index is valid (if not writes address to Cache, brings in data, miss +=1, and set valid)
    * If it is valid it will check if address tag = Cache tag at index
    * If tags are equal hit += 1
    * Else, writes address to Cache, brings in data, and set miss +=1.
    */
    int i;
    for (i=0; i<8; i++){
        if (Cache[index].valid == 0){ // Invalid bit case 
        Cache[index].valid = 1;  // replace valid bit 
        HitMiss[0].miss += 1;    // indicate a miss 
            for (i = 0; i < 10; i++){   
                Cache[index].tag[i] = tag[i]; // replace the old tag with the new tag 
            }
            for (i = 0; i < 27; i++){
                Cache[index].mem[i] = mem[i]; // replace the old memory with the new memory 
            }
            return 0;
    }
    }
    
    for (i=0; i<8; i++){
        if (Cache[index].tag[i] != tag[i]){ // If the tag's aren't the same 
            HitMiss[0].miss +=1;    // indicate a miss 
            for (i = 0; i<10; i++){
                Cache[index].tag[i] = tag[i];
            }
            for (i=0; i<27; i++){
                Cache[index].mem[i] = mem[i];
            }
            return 0; 
            }
        }
    HitMiss[0].hit +=1; // outside of the two miss scenarios it's a hit 
    return 0;
}


int printCache(struct Cache_line *Cache){
    
    //prints the current state of the Cache 
    //This is the possible source of the bug with printing data when my valid is 0... but I'm not sure 
    
    printf("Index       Tag                Valid         Data");
    printf("\n______________________________________________________________________\n");
    int i;
    for (i=0; i<8; i++){
           printf("%d", i);
           printf("         ");
           printf("%s", Cache[i].tag);
           printf("              ");
           printf("%u", Cache[i].valid); // unsigned 
           printf("          ");
           printf("%s", Cache[i].mem);
           printf("\n");     
    }
    printf("______________________________________________________________________\n");
    return 0;
}

int printvalues(struct hmstructure *HitMiss, int i){
    /*
    * prints the number of hits, misses, hit rate and miss rate
    */
    
    float hitrate;
    float missrate;
    printf("\n\n");
    printf(" Hits: ");
    printf("%d", HitMiss[0].hit);
    printf("\n Misses: ");
    printf("%d", HitMiss[0].miss);
    printf("\n Hit Rate: ");
    hitrate = HitMiss[0].hit / (float)i*100;
    missrate = HitMiss[0].miss / (float)i*100;
    printf("%f", hitrate);
    printf("%\n Miss Rate: ");
    printf("%f", missrate);
    printf("%\n\n");
    return 0;
}

