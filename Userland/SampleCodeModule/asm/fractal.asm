GLOBAL draw_fractal

SECTION .text

draw_fractal:
  push rbp
  mov rbp,rsp
  push rax
  push rbx
  push rcx
  push rdx
  mov rax, 2
  mov rbx, rdi
  mov rcx, rsi
  int 80h
  pop rdx
  pop rcx
  pop rbx
  pop rax
  mov rsp,rbp
  pop rbp
  ret
