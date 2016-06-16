#ifndef SYSTEMCALL_H
#define SYSTEMCALL_H

// http://docs.cs.up.ac.za/programming/asm/derick_tut/syscalls.html

/*
 *	This library was implemented in order to facilitate the development of System Call.
 *	Each parameter received by the System Call function is moved to the respective
 *	register to pass the parametres in C by _sys_call function. Each register is associated
 *  to a parameter with the same name. 
 */

/*
 *	Configurates the system calls for future using. If the 80th interrupt is called before
 *	calling this function will not perform the system call.
 */
void
start_system_call();

/*
 *	Calls the System Call. This is an Assembly function, and the parameters depend on the 
 *	state of the registers.
 */
void
_sys_call();

#endif