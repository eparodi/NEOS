GLOBAL _read_keyboard

section .text

; -----------------------------------------------------------------------------
;	Get the RAW data from the Keyboard.
;	Return:
;		-rax: the RAW data.
; -----------------------------------------------------------------------------
_read_keyboard:
	in al, 60h
	mov rdi, rax
	ret