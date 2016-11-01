GLOBAL _out_port_8
GLOBAL _out_port_16
GLOBAL _out_port_32
GLOBAL _in_port_8
GLOBAL _in_port_16
GLOBAL _in_port_32

section .text

_out_port_8:
  mov rax, rdi
  mov rdx, rsi
  out dx, al
  ret

_out_port_16:
  mov rax, rdi
  mov rdx, rsi
  out dx, ax
  ret

_out_port_32:
  mov rax, rdi
  mov rdx, rsi
  out dx, eax
  ret

_in_port_8:
  mov rdx, rdi
  in  eax, dx
  ret

_in_port_16:
  mov rdx, rdi
  in  eax, dx
  ret

_in_port_32:
  mov rdx, rdi
  in  eax, dx
  ret
