GLOBAL _sys_call

EXTERN system_call_interrupt

SECTION .text

; -----------------------------------------------------------------------------
;	Wrapper for the System Call function in C.
;	Parametres:
;		-rax: the number of system call.
;		-rbx, rcx, rdx, rsi and rdi: system call parameters.
;	Return;
;		-rax: the return of the system call.
; -----------------------------------------------------------------------------
_sys_call:
	mov r8, rax
	mov r9, rbx
	call system_call_interrupt

	iretq
