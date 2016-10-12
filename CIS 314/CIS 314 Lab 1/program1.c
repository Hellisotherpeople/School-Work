/*
 * CIS 314 Fall 2015 Lab 1
 * Assigned project
 *
 * This program converts a given number in_number with base in_base to any other base. All bases must be between 2 and 16. Does not support negative numbers or non-integers (with the exception of A-F for bases above 16) 
 * 
 * 
 * Author: Allen Roush, while working with Rui Tu (partners)
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NUM 16
#define MAX_DECIMAL 2147483647

// Implement the rest of the program


// global variables
char char_array[MAX_NUM+1] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','\0'};
char* char_array_ptr = char_array;




// Figure out the value of eah entered charecter 
int value_of(char character) {
    size_t csize = strlen(char_array);
    int i = 0;
    while (i < csize) {
        if (character == char_array[i]) {
            return i;
        }
        else
            i++;
    }

    return -1;
}


// find the maximum element in char array
int max_value(char* in_number_pointer) {
    int i = 1; 
    int curMax = value_of(in_number_pointer[0]);
    for (i; i < strlen(in_number_pointer); i++) {
        if (curMax < value_of(in_number_pointer[i])) {
            curMax = value_of(in_number_pointer[i]);
        }
    }
    return curMax;
}

// make sure each charecter is found 
bool is_every_char_found(char* in_number_pointer) {
    bool conditional = true;
    size_t size = strlen(in_number_pointer);
    int i = 0;
    while (i < size) {
        if ( value_of(in_number_pointer[i]) == -1) {
            conditional = false;
            break;
        }
        i++;
    }
    return conditional;
}


// validate if the input is valid
bool is_valid(char* in_number_pointer, int in_base, int out_base) {
    bool conditional =  true;
    if (!((int)strlen(in_number_pointer) <= MAX_NUM
            && max_value(in_number_pointer) < in_base && // Checks to make sure the user didn't input something like 1F if the base doesn't support that 
            16 >= in_base && in_base >= 2 &&
            16 >= out_base && out_base >= 2
            &&is_every_char_found(in_number_pointer) // Checks to make sure the user entered one of the 15 possible digits 
        )) {

        conditional = false;
    }
    return conditional;
}


// convert to decimal function
void convert_to_decimal(int in_base, char *in_number_pointer, int *decimal_result_pointer, bool* is_first_over_flow_flag_pointer) {
    int num = 0;
    int i = 0;
    int string_len = (int) strlen(in_number_pointer); // you can cast types in C! 
    while(i < string_len) {
        num += pow(in_base, string_len - 1 - i) * value_of(in_number_pointer[i]);
        if (num > MAX_DECIMAL || num < 0) {
            *is_first_over_flow_flag_pointer = true; //Triggers if the convert to decimal causes the value to be above the max set, or if it's below 0 
            break;
        }

        i++;
    }

    *decimal_result_pointer = num;
}



// Final conversion to the result
void convert_to_result(int* decimal_result_ptr, int out_base, char* out_number_pointer, char* character_array_pointer,
                       bool* second_overflow_flag_pointer){
    int decimal_convert_result = *decimal_result_ptr;
    int decimal_convert_tester   = *decimal_result_ptr; 
    int i = 0;
    int j = 0;

    while (decimal_convert_tester > 0){ 
        decimal_convert_tester = decimal_convert_tester / out_base;
        j++;
    }

    if (j <= MAX_NUM) { //prevents overflow 
        while (decimal_convert_result > 0) {
            int the_digit = decimal_convert_result % out_base;
            decimal_convert_result = decimal_convert_result / out_base;
            out_number_pointer[j - 1] = *(character_array_pointer + the_digit);
            i++;
            j--;
        }
        out_number_pointer[i] = '\0';
    } else {
        *second_overflow_flag_pointer = true;
    }
}


int main(){
    // define passed in values 
    int  in_base;
    int  out_base;
    int  decimal_result;

    char in_number[MAX_NUM+1];
    char* in_number_ptr = in_number;

    char out_number[MAX_NUM+1];
    char* out_number_ptr = out_number;

    bool first_overflow_flag = false;
    bool* first_overflow_flag_ptr = &first_overflow_flag;

    bool second_overflow_flag = false;
    bool* second_overflow_flag_ptr = &second_overflow_flag;

    printf("\n=== CIS314 Fall 2015 - Lab 1: Part 1: Program 1 ===\n\n");

    // take user input
    printf("Please enter the base of your input number: ");
    scanf("%d", &in_base);
    printf("Enter your number that you would like to convert: ");
    scanf("%s", in_number_ptr);
    printf("Please enter the base you would like in the output: ");
    scanf("%d", &out_base);
    convert_to_decimal(in_base, in_number_ptr, &decimal_result ,first_overflow_flag_ptr);
    convert_to_result(&decimal_result, out_base, out_number_ptr, char_array_ptr, second_overflow_flag_ptr);

    // print out stuff
    if (!is_valid(in_number_ptr, in_base, out_base)) {
        printf("You attempted to enter invalid input, please rerun the program again and enter valid inputs.\n");
    }
    else if (*first_overflow_flag_ptr || *second_overflow_flag_ptr) {
        printf("The input number entered is too large and has caused an overflow. \n");
    } else {
        printf("\nUser input number converted to decimal: %d\nUser Input Number converted to base %d is %s\n", decimal_result, out_base, out_number);
    }
    return 0;
}
