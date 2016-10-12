/*
 * CIS 314 Fall 2015 Lab 1
 * Assigned project
 *
 * This program reads a sorted array from a file and finds a requested number
 *    using recursive or iterative binary search. The array is read from a file
 *    defined by FILE_NAME, which should be written as the number of elements
 *    followed by the elements themselses. each number can be deliniated with
 *    any whitepace character. Also, the maximum size of the array is defined 
 *    as MAX_SIZE.
 * 
 * NOTE: The array must be sorted!!
 * 
 */

//Written by Allen Roush 

//NOTE: I (along with many others in the class) was under the impression that the given array would be sorted.
// The professor let us know that this was something we were supposed to do ourselves but realized that this was unclear 
// And said that we shouldn't be penalized for not sorting the array. Before I realized this I thought the "100" at the beginning 
// of the array file was the size of the array (and is implied by both searches not finding it when prompted). 
// 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 150
#define FILE_NAME "array.dat" //must include quotes

// Implement the rest of the program

int recursive_binary_search(int numbers[], int target, int low, int high) {
   int middle;
 
   if (low > high)
      return -1; // if it's not found 
 
   middle = (low + high) / 2;
 
   if (target == numbers[middle]) {
      return (middle);
   } else if (target < numbers[middle]) {
      recursive_binary_search(numbers, target, low, middle - 1);
   } else {
      recursive_binary_search(numbers, target, middle + 1, high);
   }
}

int iterative_binary_search(int numbers[], int target) {
    //This doesn't require low or high to be passed in since it's not being called recursivly 
   int low = 0;
   int high = MAX_SIZE - 1;
   while (low <= high) {
      int middle = (low + high) / 2;
      if (numbers[middle] == target){ 
        return middle;
      }
      else if (numbers[middle] < target){
          low = middle + 1;
      }
      else
          high = middle - 1;
   }
   return -1; // if we got this far, it hasn't been found 
}


void printArray(int array[]){ 
    printf("Here's the array you're looking through! \n");
    int i = 0; 
    for (i; i<101; ++i){
        printf("%d ", array[i]);
    }
    printf("\n"); 
}


int main(void) {
   // Define variables 
   int array[MAX_SIZE];
   int i = 0; //for iteration 
   int num, target, rtime, itime; 
   clock_t t1, t2, t3, t4;
   char in_file_name[] = FILE_NAME;
   
   //open the file and populate it
   FILE *in_file = fopen(FILE_NAME, "r"); 
   while(fscanf(in_file, "%d", &num) == 1) {
       array[i] = num;
       i++;
   }
   fclose(in_file); 
   


   printf("\n\n=== CIS314 Fall 2014 - Lab 1: Part 2: Program 2 ===\n\n");
   printf("\n\n");
   
   printf("Enter the number that you are searching for between 0-150 \n"); 
   int tester = scanf("%d", &target); //Hackey way to guaratnee that the user enters a number 
   if (target > 150 || target < 0 || tester != 1){ 
       printf("Please run the program again and enter a correct number to search for \n");
       exit(1);
   }
   
   t1 = clock(); 
   int rposition = recursive_binary_search(array, target, 0, MAX_SIZE-1);
   t2 = clock();
   rtime = t2 - t1; 
   
   t3 = clock(); 
   int iposition = iterative_binary_search(array, target); 
   t4 = clock(); 
   itime = t4 - t3; 
   
   printArray(array); 
   
   if (rposition != -1){
       printf("\n The recursive search found the number %d at position %d  and it took %d amount of time to execute", (target), (rposition), (rtime)); 
   }
   else 
       printf("\n The number was not found in the array by the Recursive search!"); 
   
   if (iposition != -1){
       printf("\n The iterative search found the number %d at position %d and it took %d amount of time to execute \n", (target), (iposition), (itime)); 
   }
   else 
       printf("\n The number was not found in the array by the Iterative search!"); 
   
   return 0;
}

