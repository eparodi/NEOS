GLOBAL time

SECTION .text

; -----------------------------------------------------------------------------
;	Returns the interpreted data from the RTC.
;	Parameters:
;		-rdi: the id of the data requested. (See rtc.h)
;	Return:
;		The time data requested.
; -----------------------------------------------------------------------------
time:
	push rbp
	mov rbp,rsp

	mov rax, 13
	mov rbx, rdi
	int 80h

	mov rsp,rbp
	pop rbp
	ret
