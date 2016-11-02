#ifndef IRQ_H
#define IRQ_H

#include "types.h"

/*
 *	8254 Timer (Timer Tick) interrupt.
 */
void
_irq00Handler();

/*
 *	Keyboard interrupt.
 */
void
_irq01Handler();

/*
 *	Cascade pic interrupt. (It is never used)
 */
void
_irq02Handler();

/*
 *	Serial Port 2 and 4 interrupt.
 */
void
_irq03Handler();

/*
 *	Serial Port 1 and 3 interrupt.
 */
void
_irq04Handler();

/*
 *	USB interrupt.
 */
void
_irq05Handler();

/*
 *	RTL8139 interrupt.
 */
void
_irq0BHandler();

/*
 *	Clear Interrupts. The processor will not handle maskable interrupts.
 */
void
_cli();

/*
 *	Set Interrupts. The processor will handle maskable interrupts.
 */
void
_sti();

/*
 *	Set a Mask for the Master PIC. A device is enabled if the value of its bit
 *	is 1.
 *	Parameters:
 *		-mask: the mask applied.
 */
void
_picMasterMask(byte mask);

/*
 *	Set a Mask for the Slave PIC. A device is enabled if the value of its bit
 *	is 1.
 *	Parameters:
 *		-mask: the mask applied.
 */
void
_picSlaveMask(byte mask);

#endif
