GLOBAL _get_mac
GLOBAL _send_message

_get_mac:
  push rbp
  mov rbp,rsp

  mov rax, 15
  mov rbx, rdi
  int 80h

  mov rsp,rbp
  pop rbp
  ret

_send_message:
  push rbp
  mov rbp,rsp

  mov rax, 16
  mov rbx, rdi
  mov rcx, rsi
  int 80h

  mov rsp,rbp
  pop rbp
  ret
