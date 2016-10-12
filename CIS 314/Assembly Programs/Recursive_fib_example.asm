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
       addi $a0, $zero, 1     #
       jal  do_fib            # fib(1)
       add  $s0, $v0, $zero   # $s0 = fib(1) = 1
       
       addi $a0, $zero, 4     #
       jal  do_fib            # fib(4)
       add  $s1, $v0, $zero   # $s1 = fib(4) = 5
       
       addi $a0, $zero, 8    # 
       jal  do_fib            # fib(8)
       add  $s2, $v0, $zero   # $s2 = fib(8) = 34
       
exit:   li   $v0 10
        syscall

#----------- fib(n) = 1 or fib(n-1) + fib(n-2) ------------#
#----------- expects n in $a0                  ------------#
#----------- returns ans in $v0                ------------#

                            # prologue
do_fib: addi $sp, $sp, -20  # move stack pointer
        sw   $s0, 0($sp)
        sw   $s1, 4($sp)
        sw   $s2, 8($sp)
        sw   $s3, 12($sp)
        sw   $ra, 16($sp)
        
                              # body of the function
        add  $s0, $a0, $zero  # $s0 = n
        slti $t0, $s0, 2      # check base
        bne  $t0, $zero, base # if n < 2 do base
                             
                              # recursive
        addi $a0, $s0, -1     # $a0 = n - 1
        jal  do_fib           # fib(n-1)
        add  $s2, $v0, $zero  # $s2 = fib(n-1)
        addi $a0, $s0, -2     # $a0 = n - 2
        jal  do_fib           # fib(n-2)
        add  $s3, $v0, $zero  # $s3 = fib(n-2)
        add  $v0, $s2, $s3    # $v0 = fib(n-1) + fib(n-2)
        j    return           # all done

base:   addi $v0, $zero, 1    # base

return:                       #epilogue
        lw   $s0, 0($sp)      # pop stack
        lw   $s1, 4($sp)
        lw   $s2, 8($sp)
        lw   $s3, 12($sp)
        lw   $ra, 16($sp)
        addi $sp, $sp, 20     # move stack pointer
        jr   $ra              # return

#-----------        end fib(n)           ------------------#


####################### Data Section (unused) #######################
# .data
