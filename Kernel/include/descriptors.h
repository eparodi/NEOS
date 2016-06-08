#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

// http://wiki.osdev.org/Descriptors#type_attr
// http://wiki.osdev.org/Expand_Down#Expand_Down

/* Bits:
 *    -Bit 7:        Present Flag.
 *    -Bits 5 and 6: Descriptor Privilege Level.
 *    -Bit 4:        Whether the segment is a data/code segment or system
 *                   segment.
 *    -Bits 0 to 3:  Type (depends on the segment type).
 *
 * Type bits for Data Segment:
 *    -Bit 3:        Its value is 0. It means it is a data segment.
 *    -Bit 2:        Its value is 0 if the segment contains normal data.
 *                   Otherwise, it is a expand-down data segment (Stack).
 *    -Bit 1:        Its value is 1 if it is writable.
 *    -Bit 0:        Its value is 1 if it has been accessed.
 *
 * Type bits for Code Segment:
 *    -Bit 3:        Its value is 1. It means it is a code segment.
 *    -Bit 2:        Its value is 0 if the segment is conforming.
 *    -Bit 1:        Its value is 1 if it is readable and executable. Otherwise
 *                   it is only executable.
 *    -Bit 0:        Its value is 1 if it has been accessed.
 */

#define INT_PRESENT 0x80 //1000 0000
/* I386 TRAP GATE */
#define ACS_INT_368 0x0E //0000 1110
/* Interruptions modifier */
#define ACS_INT (INT_PRESENT | ACS_INT_368)
 
#endif