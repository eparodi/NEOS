#include "include/types.h"
#include "include/systemcall.h"

/* The amount of system call in Linux API. */
#define SYS_CALL_SIZE 190

/* The vector of pointers to system call functions. RAX register holds the index of the function. */
static qword (* syscall_vector[SYS_CALL_SIZE])(qword,qword,qword,qword,qword) ;

/*
 *	This function replaces not yet implemented System Calls.
 *	Return:
 *		Always returns 0.
 */
qword
null_function(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi);

/*
 *	This funcion executes the function associated with the number (RAX) of System Call.
 *	Return:
 *		The return value of the System Call.
 */
qword
systemcall_interrupt(qword _rdi, qword _rsi, qword _rdx, qword _rcx, qword _rax, qword _rbx);

void
start_system_call(){
	int i = 0;
	for (; i < SYS_CALL_SIZE ; i++){
		syscall_vector[i] = &null_function;
	}
	//syscall_vector[index] = &dummy_function;
	//TODO: add system calls to the vector.
}

qword
system_call_interrupt(qword _rdi, qword _rsi, qword _rdx, qword _rcx, qword _rax, qword _rbx){
	return (*(syscall_vector[_rax]))(_rbx,_rcx,_rdx,_rdi,_rsi);
}

qword
null_function(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi){
	return 0;
}
