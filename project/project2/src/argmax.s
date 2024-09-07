.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    # Prologue
    li t0,1
    bge a1,t0,no_exception
    li a1,77
    j exit2
no_exception:
    mv t0,zero
    mv t1,zero
loop_start:
    mv t2,t1
    slli t2,t2,2
    add t2,t2,a0
    lw t3,0(t2)
    mv t4,t0
    slli t4,t4,2
    add t4,t4,a0
    lw t5,0(t4)
    bge t3,t5,loop_continue
    mv t1,t0
loop_continue:
    addi t0,t0,1
    beq t0,a1,loop_end
    j loop_start
loop_end:
    mv a0,t1

    # Epilogue


    ret
