.section .text
.global _start
_start:

li t1, 150
li t2, 300
li t3, -250
ADD t4, t1, t2
ADD t5, t2, t3
ecall