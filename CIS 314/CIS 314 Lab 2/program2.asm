#----------------------------------------------------------#
# RecursiveBinarySearch.asm 
# a simple mips program that Recursivly performs a Binary Search on an arra
# CIS 314 Lab 
# Author: Allen Roush, while working with Abdul Al-Aziz 
# 
#----------------------------------------------------------#

####################### Text Section #######################

.text
.globl main

main:
       la $s0, list            # $s0 = [1,4,5,7,9,12,15,18,20,21,30]
       lw $s1, size            # $s1 = 11

       #addi $a0, $zero, 7
       #addi $a1, $s1, -1       # $a1 = 10, high - 1
       #add $a2, $zero, $zero   # $a2 = 0, low 
       #jal binary_search              
       #add $s5, $v0, $zero     # $s0 = bin(7) = 3
       
              
       #The above run was commented out because I needed to run the binary #search with desired element 21 for the 2nd excel thing 
       

       addi $a0, $zero, 21 
       addi $a1, $s1, -1       # $a1 = 10, high - 1
       add $a2, $zero, $zero   # $a2 = 0, low 
       jal binary_search     
       add $s6, $v0, $zero     # $s0 = fib(21) = 9
       

########################
exit:   li   $v0 10
        syscall
########################
binary_search: addi $sp, $sp, -32  # move stack pointer
        sw   $s1, 0($sp)    # high
        sw   $s2, 4($sp)    # low
        sw   $s3, 8($sp)   # mid
        sw   $s4, 12($sp)   # list[mid]
        sw   $s5, 16($sp)    # value        
        sw   $t0, 20($sp)
        sw   $t1, 24($sp) 
        sw   $ra, 28($sp)  

        add  $s5, $a0, $zero # ($s5) = value
        add  $s1, $a1, $zero # ($s1) = high
        add  $s2, $a2, $zero # ($s2) = low

        slt $t0, $s1, $s2 # if high < low : $t0 = 1, else $t0 = 0
        bgtz $t0, not_found   # if $t0 > 0, jump to not_found
        add $s3, $s2, $s1   # mid = (low + high)
        srl $s3, $s3, 1     # mid = (low + high)/2
        sll $t1, $s3, 2     # $t1 = mid * 4
        add $t1, $t1, $s0   # $t1 = $t1 + *list
        lw $s4, 0($t1)      # $s4 = list[mid]
        slt $t0, $s5, $s4   # if value < list[mid] : $t0 = 1, else $t0 = 0
        bgtz $t0, value_less_mid   # if $t0 > 0, jump to not_found
        slt $t0, $s4, $s5   # if value > list[mid] : $t0 = 1, else $t0 = 0
        bgtz $t0, value_bigger_mid   # if $t0 > 0, jump to not_found
        add $v0, $zero, $s3
        j return

########################
value_less_mid:
      addi $a1, $s3, -1     # high = $a2 = mid - 1 
      jal binary_search              
      j return

value_bigger_mid:
      addi $a2, $s3, 1     # low = $a2 = mid + 1,  
      jal binary_search            
      j return
     
not_found: 
      addi $v0, $zero, -1
      j return
return:                       #epilogue
      lw   $s1, 0($sp)      # pop stack
      lw   $s2, 4($sp)
      lw   $s3, 8($sp)
      lw   $s4, 12($sp)
      lw   $s5, 16($sp)
      lw   $t0, 20($sp)
      lw   $t1, 24($sp) 
      lw   $ra, 28($sp)  
      addi $sp, $sp, 32     # move stack pointer
      jr $ra  

#-----------        end fib(n)           ------------------#


####################### Data Section #######################
  .data
        list: .word 1, 4, 5, 7, 9, 12, 15, 18, 20, 21, 30
        size: .word 11
        value: .word 9
