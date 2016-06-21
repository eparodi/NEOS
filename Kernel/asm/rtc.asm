GLOBAL _get_rtc_data
GLOBAL _write_rtc_data

SECTION .text
; -----------------------------------------------------------------------------
;	Gets the RAW data from the RTC.
;	Parameters:
;		-rdi: the number associated with the data wanted to be read.
;	Return:
;		rax:The RAW data.
; -----------------------------------------------------------------------------
_get_rtc_data:

	mov rax, rdi
	out 70h, al
	in al, 71h

	ret

; -----------------------------------------------------------------------------
;	Writes data in the RTC.
;	Parameters:
;		-rdi: the number associated with the data wanted to be read.
;		-rsi: the data going to be written.
; -----------------------------------------------------------------------------
_write_rtc_data:

	mov rax, rdi
	out 70h, al

	mov rax, rsi
	out 71h, al

	ret
