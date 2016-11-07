GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq0BHandler

GLOBAL _sti
GLOBAL _cli

GLOBAL _picMasterMask
GLOBAL _picSlaveMask

EXTERN irq_handler

; -----------------------------------------------------------------------------
;	This macro calls the irq_handler function in idt.h
; -----------------------------------------------------------------------------
%macro irqHandlerMaster 1
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push r8
	push r9
	mov rdi, %1
	call irq_handler

	;signal pic
	mov al, 20h
	out 20h, al
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	iretq

%endmacro

SECTION .text

; -----------------------------------------------------------------------------
; 	8254 Timer (Timer Tick) interrupt.
; -----------------------------------------------------------------------------
_irq00Handler:
	irqHandlerMaster 0

; -----------------------------------------------------------------------------
; 	Keyboard interrupt.
; -----------------------------------------------------------------------------
_irq01Handler:
	irqHandlerMaster 1

; -----------------------------------------------------------------------------
; 	Cascade pic interrupt. (It is never used)
; -----------------------------------------------------------------------------
_irq02Handler:
	irqHandlerMaster 2

; -----------------------------------------------------------------------------
;	Serial Port 2 and 4 interrupt.
; -----------------------------------------------------------------------------
_irq03Handler:
	irqHandlerMaster 3

; -----------------------------------------------------------------------------
; 	Serial Port 1 and 3 interrupt.
; -----------------------------------------------------------------------------
_irq04Handler:
	irqHandlerMaster 4

; -----------------------------------------------------------------------------
;	USB interrupt.
; -----------------------------------------------------------------------------
_irq05Handler:
	irqHandlerMaster 5

; -----------------------------------------------------------------------------
;	RTL8139 interrupt.
; -----------------------------------------------------------------------------
_irq0BHandler:
	irqHandlerMaster 11

; -----------------------------------------------------------------------------
;	Clear Interrupts. The processor will not handle maskable interrupts.
; -----------------------------------------------------------------------------
_cli:
	cli
	ret

; -----------------------------------------------------------------------------
;	Set Interrupts. The processor will handle maskable interrupts.
; -----------------------------------------------------------------------------
_sti:
	sti
	ret

; -----------------------------------------------------------------------------
;	Set a Mask for the Master PIC. A device is disabled if the value of its bit
;	is 1.
;	Parameters:
;		-rdi: the mask applied.
; -----------------------------------------------------------------------------
_picMasterMask:
    mov rax, rdi
    out	21h, al
    ret

; -----------------------------------------------------------------------------
;	Set a Mask for the Slave PIC. A device is disabled if the value of its bit
;	is 1.
;	Parameters:
;		-rdi: the mask applied.
; -----------------------------------------------------------------------------
_picSlaveMask:
    mov     rax, rdi
    out		0A1h,al
    ret
