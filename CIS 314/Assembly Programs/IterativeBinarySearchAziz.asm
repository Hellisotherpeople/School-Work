#----------------------------------------------------------#
# recursive_fib_example.asm
# a simple mips program that calculates the fibonocci 
#    sequence recursively
# CIS 314 in-lab activity
# demonstrate function calling
#----------------------------------------------------------#

####################### Text Section #######################

.text
.globl main

main:
       la $s0, list           # $s0 = [1,4,5,7,9,12,15,18,20,21,30]
       lw $s1, size           # $s1 = 11
       lw $a0, value          # $a0 = 21 ,which in index 9
       jal binary_search            # fib(0)
       add $s7, $v0, $zero    # $s7 = binary_search (element 15) 
########################
exit:   li   $v0 10
        syscall
########################
binary_search: add $s3, $zero, $zero       #int low = 0;
        add $s4, $zero, $zero       #int mid = 0;
        addi $s5, $s1, -1           #int high = size - 1;
        j loop
########################
loop: 
      slt $t7, $s5, $s3
      bgtz $t7, end
      add $s4, $s3, $s5   # mid = (low + high)
      srl $s4, $s4, 1     # mid = (low + high)/2
      sll $t0, $s4, 2     # $t0 = mid * 4
      add $t1, $t0, $s0   # $t1 = $t0 + *list
      lw $t1, 0($t1)      # $t1 = list[mid]
      beq $a0, $t1, vequal
      slt $t2, $a0, $t1
      bg $t2, vless
      addi $s3, $s4, 1
      add $v0, $zero, $s4
      j loop
########################
vless:
      addi $s5, $s4, -1      #high = mid - 1;
      add $v0, $zero, $s4
      j loop
vequal:
      add $v0, $zero, $s4
      j return
end: 
      addi $v0, $zero, -1
      j return
return:                       #epilogue
      
      jr $ra  

#-----------        end fib(n)           ------------------#


####################### Data Section #######################
  .data
        list: .word 1, 4, 5, 7, 9, 12, 15, 18, 20, 21, 30
        size: .word 11
        value: .word 15
