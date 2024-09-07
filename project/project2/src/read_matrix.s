.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
read_matrix:

    # Prologue
    addi sp,sp,-36
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s2,12(sp)
    sw s3,16(sp)
    sw s4,20(sp)
    sw s5,24(sp)
    sw s6,28(sp)
    sw s7,32(sp)

    mv s0,a0
    mv s1,a1
    mv s2,a2
    
    mv a1,s0
    li a2,0
	call fopen
    li t0,-1
    beq a0,t0,exit_90
    mv s3,a0

    mv a1,s3
    mv a2,s1
    li a3,4
    call fread
    li t0,4
    blt a0,t0,exit_91
    mv a1,s3
    mv a2,s2
    li a3,4
    call fread
    li t0,4
    blt a0,t0,exit_91

    lw s4,0(s1)
    lw s5,0(s2)
    mul s6,s4,s5
    slli s6,s6,2
    mv a0,s6
    call malloc
    beq x0,a0,exit_88
    mv s7,a0

    mv a1,s3
    mv a2,s7
    mv a3,s6
    call fread
    bne a0,s6,exit_91


    mv a1,s3
    call fclose
    bne a0,zero,exit_92
    # Epilogue

    mv a0,s7

    lw ra,0(sp)
    lw s0,4(sp)
    lw s1,8(sp)
    lw s2,12(sp)
    lw s3,16(sp)
    lw s4,20(sp)
    lw s5,24(sp)
    lw s6,28(sp)
    lw s7,32(sp)
    addi sp,sp,36
    ret

exit_88:
    li a1,88
    j exit2
exit_90:
    li a1,90
    j exit2
exit_91:
    li a1,91
    j exit2
exit_92:
    li a1,92
    j exit2
