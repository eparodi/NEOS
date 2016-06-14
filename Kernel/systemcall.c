#include "include/types.h"
#include "include/systemcall.h"
#include "include/videoDriver.h"
#include "include/keyboard.h"
#include "naiveConsole.h"

/* The amount of system call in Linux API. */
#define SYS_CALL_SIZE 190

/* The three standard I/O */
#define STD_IN 		0
#define STD_OUT		1
#define STD_ERR 	2

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

/*
 *	The read system call, only works on Standard Input. No file descriptor implementation.
 *	Parameters:
 *		-_rbx: file descriptor.
 *		-_rcx: buffer.
 *		-_rdx: number of bytes copied.
 *	Return:
 *		The size of the data copied in bytes, if the read was succesful. Otherwise, it returns 0.
 */
qword
read_sc(qword _rbx, char * _rcx, qword _rdx, qword _rdi, qword _rsi );

/*
 *	The write system call, only works on Standard Input and Error. No file descriptor 
 *  implementation.
 *	Parameters:
 *		-_rbx: file descriptor.
 *		-_rcx: buffer.
 *		-_rdx: number of bytes copied.
 */
qword
write_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi );

void
start_system_call(){
	int i = 0;
	for (; i < SYS_CALL_SIZE ; i++){
		syscall_vector[i] = &null_function;
	}
	syscall_vector[3] = &read_sc;
	syscall_vector[4] = &write_sc;
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

qword
read_sc(qword _rbx, char * _rcx, qword _rdx, qword _rdi, qword _rsi ){
	
	
	char a;
	int i = 0;
	if ( _rbx == STD_IN ){
		while(_rdx >0){
		 _rdx--;
		((char*)_rcx)[i++] =read_from_buffer();		
		}
			
	}
	return 0 ;
}

qword
write_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi ){
	if ( _rbx == STD_OUT ){
		printWithLength( _rcx, _rdx ,0x0F);
		return _rdx;
	}else if ( _rbx == STD_ERR ) {
		printWithLength( _rcx, _rdx ,0x7C);
		return _rdx;
	}
	return -1 ;
}
