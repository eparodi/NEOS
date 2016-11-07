#ifndef IDT_H
#define IDT_H

// http://wiki.osdev.org/Interrupt_Descriptor_Table

#include "types.h"

// Starts packing the data. Pragma directive makes the struct occupy only 16
// bytes.
#pragma pack(push)
// Pack size.
#pragma pack(1)

/* Interrupt Descriptor */
typedef struct{
  word    offset_l,
          selector;
  byte    zero_byte,
          descriptor;
  word    offset_m;
  dword   offset_h,
          zero_dword;
}INT_DESCRIPTOR;
// Stops packing data.
#pragma pack(pop)

/* Interrupt request first index */
#define IRQ_INDEX 0x20
#define IRQ_SLAVE_INDEX 0x70

/* System Call index */
#define SYS_CALL_INDEX 0x80

/*
 *  Adds an interrupt descriptor to the Interrupt Descriptor Table.
 *  Parametres:
 *    -index:     index of the table.
 *    -selector:  code segment selector. (0x08 is an usual value)
 *    -offset:    memory address of the function associated to the interrupt.
 *    -type_attr: descriptor of the entry.
 *  Return:
 *    True if the entry is set.
 */
boolean
setup_idt_entry(int index, byte selector, qword offset, byte type_attr);

/*
 *	Executes the Interrupt Requested.
 *	Parametres:
 *	  -irq_number: number of the interrupt.
 */
void
irq_handler(int irq_number);

/*
 *	Loads the custom Interrupt Descriptors on the Interrupt Descriptor Table.
 */
void
set_idt();

#endif
