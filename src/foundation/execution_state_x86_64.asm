section .text
global _foundation_execution_state_x86_64
_foundation_execution_state_x86_64:
  ; push rcx
  ; mov rcx, [rsp + 16]
  ; mov qword [rcx], rax
  ; mov rax, rcx
  ; pop rcx
  ; mov qword [rax + 8], rcx
  ; mov qword [rax + 16], rdx
  ; mov qword [rax + 24], rbx
  ; mov rcx, rsp
  ; sub rcx, 4
  ; mov qword [rax + 32], rcx
  ; mov qword [rax + 40], rbp
  ; mov qword [rax + 48], rsi
  ; mov qword [rax + 56], rdi
  ; mov qword [rax + 64], r8
  ; mov qword [rax + 72], r9
  ; mov qword [rax + 80], r10
  ; mov qword [rax + 88], r11
  ; mov qword [rax + 96], r12
  ; mov qword [rax + 104], r13
  ; mov qword [rax + 112], r14
  ; mov qword [rax + 120], r15
  ; pop rcx
  ; push rcx
  ; mov qword [rax + 128], rcx
  ret