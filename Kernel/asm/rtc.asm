GLOBAL _get_rtc_data
GLOBAL _write_rtc_data

SECTION .text
; -----------------------------------------------------------------------------
;	Gets the RAW data from the RTC.
;	Parametres:
;		-rdi: the number associated with the data wanted to be read.
;	Return:
;		rax:The RAW data.
; -----------------------------------------------------------------------------
_get_rtc_data:

	mov rax, rdi
	out 70h, al
	in ax, 71
	
	ret

; -----------------------------------------------------------------------------
;	Writes data in the RTC.
;	Parametres:
;		-rdi: the number associated with the data wanted to be read.
;		-rsi: the data going to be written.
; -----------------------------------------------------------------------------
_write_rtc_data:

	mov rax, rdi
	out 70h, al

	mov rax, rsi
	out 71h, ax

	ret