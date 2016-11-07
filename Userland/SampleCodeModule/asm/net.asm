GLOBAL _get_mac

_get_mac:
  push rbp
  mov rbp,rsp
  mov rax, 15
  mov rbx, rdi
  int 80h
  mov rsp,rbp
  pop rbp
  ret
