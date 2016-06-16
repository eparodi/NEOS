#include "include/types.h"
#include "include/idt.h"
#include "include/descriptors.h"
#include "include/irq.h"
#include "include/vsa_driver.h"

#include "include/keyboard.h"
#include "include/systemcall.h"

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
  static char a='0';
  //TODO change to array of pointer to function.
  switch( irq_number ){
    case 0x00:
      // Set Timer Tick Interrupt.
        print_char('A',0xFF00FF);
        break;
    case 0x01:
      add_to_buffer();
      //update_screen();
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

  // load system calls.
  start_system_call();
  // sets system call function in vector.
  setup_idt_entry( SYS_CALL_INDEX , 0x08 , (qword) &_sys_call , ACS_INT);
}
