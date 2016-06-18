GLOBAL sleep

SECTION .text

sleep:
  push rbp
  mov rbp,rsp
  push rax
  push rbx
  push rcx
  push rdx
  mov rax, 100
  mov rbx, rdi
  ;mov rcx, rsi
  int 80h
  pop rdx
  pop rcx
  pop rbx
  pop rax
  mov rsp,rbp
  pop rbp
  ret
