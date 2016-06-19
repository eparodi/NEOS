GLOBAL draw_fractal

SECTION .text

draw_fractal:
  push rbp
  mov rbp,rsp
  push rax
  push rbx
  push rcx
  push rdx
  mov rax, 101
  mov rbx, rdi
  mov r9, rcx
  mov rcx, rsi
  mov rdi, r9
  int 80h
  pop rdx
  pop rcx
  pop rbx
  pop rax
  mov rsp,rbp
  pop rbp
  ret
