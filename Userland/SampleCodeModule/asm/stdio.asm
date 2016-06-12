GLOBAL write
GLOBAL read

SECTION .text

; -----------------------------------------------------------------------------
;	Writes data in the correspondent file descriptor.
;	Paramaters:
;		-rdi: the file descriptor.
;		-rsi: the pointer to the buffer.
;		-rdx: the length of the message.
;	Return:
;		The write system call return value.
; -----------------------------------------------------------------------------
write:
	mov rax, 4
	mov rbx, rdi
	mov rcx, rsi
	int 80h
	ret

; -----------------------------------------------------------------------------
;	Reads data from the correspondent file descriptor.
;	Paramaters:
;		-rdi: the file descriptor.
;		-rsi: the pointer to the buffer.
;		-rdx: the length of the message going to be read.
;	Return:
;		The write system call return value.
; -----------------------------------------------------------------------------
read:
	mov rax, 3
	mov rbx, rdi
	mov rcx, rsi
	int 80h
	ret