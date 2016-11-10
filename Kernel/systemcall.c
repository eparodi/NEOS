#include "include/types.h"
#include "include/systemcall.h"
#include "include/keyboard.h"
#include "include/naiveConsole.h"
#include "include/vsa_driver.h"
#include "include/rtc.h"
#include "include/timerTick.h"
#include "include/rtl_driver.h"
#include "./include/lib.h"

/* The amount of system call in Linux API. */
#define SYS_CALL_SIZE 190

/* The three standard I/O */
#define STD_IN 		0
#define STD_OUT		1
#define STD_ERR 	2

/* The vector of pointers to system call functions. RAX register holds the index of the function. */
static qword (* syscall_vector[SYS_CALL_SIZE])(qword,qword,qword,qword,qword) ;

/* Typedef function systemcall */
typedef qword (*systemcall)(qword,qword,qword,qword,qword);

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
int
read_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi );

/*
 *	The write system call, only works on Standard Input and Error. No file descriptor
 *  implementation.
 *	Parameters:
 *		-_rbx: file descriptor.
 *		-_rcx: buffer.
 *		-_rdx: number of bytes copied.
 *	Return:
 *		-1 if there was an error writing, otherwise the size of the written data.
 */
qword
write_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi );

/*
 *	A time system call. Reads the time, and returns it.
 *	Parameters:
 *		-_rbx: option to read. (See rtc.h)
 *	Return:
 *		The time required. -1 if there was an error.
 */
 int
 time_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi );

/*
 * The sleep system call.
  *	Parameters:
 *		-_rbx: ms.
 */
void sleep_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi );

/*
 * Returns the Mac Address.
 */
 void
 get_mac_address(uint8_t * buf);

int
send_message_sc(uint8_t * mac, uint8_t * message, int size );

void
start_system_call(){
	int i = 0;
	for (; i < SYS_CALL_SIZE ; i++){
		syscall_vector[i] = &null_function;
	}
	syscall_vector[3] = (systemcall)&read_sc;
	syscall_vector[4] = (systemcall)&write_sc;
	syscall_vector[13] = (systemcall)&time_sc;
	syscall_vector[14] = (systemcall)&clear_screen;
  syscall_vector[15] = (systemcall)&get_mac_address;
  syscall_vector[16] = (systemcall)&send_message_sc;
	syscall_vector[100] = (systemcall)&sleep_sc;
}

qword
system_call_interrupt(qword _rdi, qword _rsi, qword _rdx, qword _rcx, qword _rax, qword _rbx){
	return (*(syscall_vector[_rax]))(_rbx,_rcx,_rdx,_rdi,_rsi);
}

qword
null_function(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi){
	return 0;
}

int
read_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi ){

	if ( _rbx == STD_IN ){
		int j;

			 j =read_from_buffer(_rdx,(char*) _rcx);
			return j;
	}
	return 0 ;
}

qword
write_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi ){
	if ( _rbx == STD_OUT ){
		print_string_by_length( (char *)_rcx, _rdx ,0xffffff);
		return _rdx;
	}else if ( _rbx == STD_ERR ) {
		print_string_by_length( (char *)_rcx, _rdx ,0xffffff);
		return _rdx;
	}
	return -1 ;
}

int
time_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi ){
	return get_time_data(_rbx);
}

void
sleep_sc(qword _rbx, qword _rcx, qword _rdx, qword _rdi, qword _rsi ){
	sleep(_rbx);
}

void
get_mac_address(uint8_t * buf){
  copy_mac(buf);
}

int
send_message_sc(uint8_t * mac, uint8_t * message, int size ){
  Package pkg;
  pkg.data = message;
  pkg.length = size;
  pkg.mac_dest = mac;
  send_message(&pkg);
  return size;
}
