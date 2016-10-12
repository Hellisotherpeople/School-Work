#----------------------------------------------------------#
# program1.asm
# a MIPS program to iteratively do a Binary Search on an array 
# CIS 314 Labratory 2 
# Author: Allen Roush 
#
#----------------------------------------------------------#

#---------------------- Text Section ----------------------#

.text
.globl main

main:
       la   $s0, my_array      # Load base address of my_array in $s0
       lw   $s1, array_size    # put array_size (not pointer) in $s1
       
       
       addi $a0, $zero, 15      # put the desired_element  in $a0
       jal  binary_search       # call the binary_search function 
       add  $s3, $v0, $zero     # s3 = Binary_Search(15) = 6
       
       addi $a0, $zero, 4      # put the desired_element  in $a0
       jal  binary_search       # call the binary_search function 
       add  $s4, $v0, $zero     # s4 = Binary_Search(4) = 1
       
       addi $a0, $zero, 30      # put the desired_element  in $a0
       jal  binary_search       # call the binary_search function 
       add  $s5, $v0, $zero     # s5 = Binary_Search(30) = 11
       
       addi $a0, $zero, 0      # put the desired_element  in $a0
       jal  binary_search       # call the binary_search function 
       add  $s6, $v0, $zero     # s6 = Binary_Search(0) = -1 
       
       
       
    
                               
exit:   li   $v0 10
        syscall
       
       
binary_search:  
       add  $t0, $zero, $zero   # Initialize low ($t0) to 0
       addi $t5, $s1, 0      #Initialize the hgh value ($t5) to array_size
       add  $t2, $zero, $zero #initialize mid ($t2) to be 0;  
WHILE: 
       slt $t7, $t5, $t0       #The while loop 
       bgtz $t7, END           #While loop 
       add  $t2, $t0, $t5      # middle = low + high 
       srl  $t2, $t2, 1        # Initialie middle ($t2) to low + high / 2 
       sll  $t3, $t2, 2        # $t3 = mid * 4 
       add  $t4, $t3, $s0      # $t4 = $t3 + *list 
       lw   $t4, 0($t4)        # $t4 = list[mid]
       beq  $t4, $a0, FOUND    # If number[middle] == target, return middle 
       slt  $t6, $a0, $t4      # used for Else-if 
       bgtz $t6, LOW           # Else if numbers[middle] < target
       addi $t0, $t2, 1        # low = middle + 1 
       j    WHILE              # Go back through the while loop 


FOUND: 
       add $v0, $zero, $t2          # Return middle 
       jr   $ra                # Jump back outside of the function

LOW: 
       addi $t5, $t2, -1        # high = middle - 1 
       add $v0, $zero, $t2     
       j     WHILE             # Go back into the while loop 

END:        
       li $v0, -1              # If we got this far, return -1  
       jr  $ra 
       


#---------------------- Data Section ----------------------#
my_array:   .word 1, 4, 5, 7, 9, 12, 15, 17, 18, 20, 21, 30
array_size: .word 11
