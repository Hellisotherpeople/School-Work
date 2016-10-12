//
//  program1.c 
//
//
//  Created by Allen Roush
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>



int main (int argc, char **argv)
{
    
    CheckreadFile(argc, argv);
    
    int cache_size = 32; // Cache size should be 32
    int block_size = 16; // Block size should be 16
    int num_lines  = 1;  // number of lines per cache 
    int num_sets   = cache_size/block_size; 
    

    
    direct(argv[1], cache_size, block_size);
    
    
    
    
    return 0;
    
}




void CheckreadFile(int argc, char **argv) {    //Checks validity of user input

    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "<ERROR>: File not found\n");
        exit(1);
    }
    
    
    
}



int isPower2(int x) {           //returns 1 if x is power of 2
    
    return !(x>>31) & !!x & !(x & (x+(~1+1)));
}


int getBlock(int w, int b) {        //returns right most b bits
    
    int mask = (1 << b) - 1;
    int block = w & mask;
    return block;
}


int getSetIndex(int w, int s) {         //returns right most s bits
    
    int mask = (1 << s) - 1;
    int set_index = w & mask;
    return set_index;
}


int isHit(struct Address *cache, int set_index, int tag) {          //returns 1 if hit, 0 if miss
    
    if (cache[set_index].valid_bit == 0) {
        
        cache[set_index].valid_bit = 1;
        cache[set_index].tag = tag;
        return 0;
    }
    else {
        if (cache[set_index].tag == tag)
        {
            return 1;
        }
        cache[set_index].tag = tag;
        return 0;
    }
}

void direct(char *trace_file, int cache_size, int block_size) {
    
    FILE *file;
    file = fopen(trace_file, "r");
    
    int reads = 0;
    int hits = 0;
    int misses = 0;
    int tag = 0;

    
    int sets = cache_size/block_size;
    int s = log2(sets);
    int b = log2(block_size);
    
    
    
    struct Address *cache = malloc(sizeof(struct Address)*sets);
    
    int i = 0;
    
    for (i = 0; i < sets; i++) {
        
        cache[i].tag = 0;
        cache[i].valid_bit = 0;
        cache[i].set_index = 0;
    }
    
    
    char line[100];
    
    
    
    
    while (fgets(line, sizeof(line), file)) {  //Parses each line of address file for address's and splits them into their components 
                        
            int mem_add = (int)strtol(word, NULL, 0); // converts hex memory address to integer
            int block = getBlock(mem_add, b);
            mem_add = mem_add >> b;
            int set_index = getSetIndex(mem_add, s);
            tag = mem_add >> s;
                
            if (isHit(cache, set_index, tag)) {
                    hits++;
                }
            else {
                    misses++;
                    reads++;
                }
                
            }
            
        }
    
    printf("Memory Reads: %d\n", reads);
    printf("Memory Writes: %d\n", writes);
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    
    
}