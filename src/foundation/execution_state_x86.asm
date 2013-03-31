section .text
global _foundation_execution_state_x86
_foundation_execution_state_x86:
  push ecx
  mov ecx, [esp + 16]
  mov dword [ecx], eax
  pop eax
  mov dword [ecx + 4], eax ; ecx
  mov dword [ecx + 8], edx
  mov dword [ecx + 12], ebx
  mov eax, esp
  add eax, 16
  mov dword [ecx + 16], eax ; esp
  mov eax, [esp + 4]
  mov dword [ecx + 20], eax ; ebp
  mov dword [ecx + 24], esi
  mov dword [ecx + 28], edi
  mov dword eax, [esp + 8]
  mov dword [ecx + 32], eax ; eip
  ret