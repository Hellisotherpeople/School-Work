# Descro[topn: THe program reads and prints a string 
###################### Data Segment ##############3####
.data 
str: .space 10 
################## Code segment #####################
.text 
.globl main 
main: 
 la            $a0, str 
 li            $a1, 10 
 li            $v0, 8 
 syscall 
 li            $v0, 4
 syscall 
 li            $v0, 10 
 syscall