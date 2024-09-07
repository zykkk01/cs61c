.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:

    # Error checks
    li t0,1
    blt a1,t0,exception1
    blt a2,t0,exception1
    blt a4,t0,exception2
    blt a5,t0,exception2
    bne a2,a4,exception3
    # Prologue
    li t0,0
    mv t2,a0
    addi sp,sp,-32
    sw ra,0(sp)
    sw s0,4(sp)
    sw s1,8(sp)
    sw s2,12(sp)
    sw s3,16(sp)
    sw s4,20(sp)
    sw s5,24(sp)
    sw s6,28(sp)
    mv s0,a0
    mv s1,a1
    mv s2,a2
    mv s3,a3
    mv s4,a4
    mv s5,a5
    mv s6,a6

outer_loop_start:
    li t1,0
    
inner_loop_start:
    
    mv a0,s0
    mv t2,t1
    slli t2,t2,2
    add a1,s3,t2
    mv a2,s2
    li a3,1
    mv a4,s5

    addi sp,sp,-8
    sw t0,0(sp)
    sw t1,4(sp)

    call dot
    sw a0,0(s6)

    lw t0,0(sp)
    lw t1,4(sp)
    addi sp,sp,8
    
    addi t1,t1,1
    addi s6,s6,4
    bne t1,s5,inner_loop_start
inner_loop_end:
    addi t0,t0,1
    mv t2,s2
    slli t2,t2,2
    add s0,s0,t2
    bne t0,s1,outer_loop_start
outer_loop_end:

    # Epilogue
    
    lw ra,0(sp)
    lw s0,4(sp)
    lw s1,8(sp)
    lw s2,12(sp)
    lw s3,16(sp)
    lw s4,20(sp)
    lw s5,24(sp)
    lw s6,28(sp)
    addi sp,sp,32
    ret

exception1:
    li a1,72
    j exit2
exception2:
    li a1,73
    j exit2
exception3:
    li a1,74
    j exit2
