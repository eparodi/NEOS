#include "include/types.h"
#include "include/idt.h"
#include "include/descriptors.h"
#include "include/irq.h"

#include "include/naiveConsole.h"
#include "include/keyboard.h"



boolean
setup_idt_entry(int index, byte selector, qword offset, byte type_attr){
  if ( sizeof(INT_DESCRIPTOR) * index > (qword) idt_end ){
    return false;
  }else{
    idt[index].offset_l = offset & 0xFFFF;
    idt[index].selector = selector;
    idt[index].zero_byte = 0;
    idt[index].descriptor = type_attr;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFF;
    idt[index].zero_dword = 0;
    return true;
  }
}

void
irq_handler(int irq_number){
  switch( irq_number ){
    case 0x00:
      // Set Timer Tick Interrupt.
      break;
    case 0x01:
      update_screen();

      break;
  }
}

void
set_idt(){
  // loads the timer tick.
  setup_idt_entry( IRQ_INDEX , 0x08 , (qword) &_irq00Handler, ACS_INT);
  // loads the keyboard.
  setup_idt_entry( IRQ_INDEX + 1 , 0x08 , (qword) &_irq01Handler, ACS_INT);
  _picMasterMask(0xFC);
  _sti();
}