section .text
global _foundation_execution_state_x86
_foundation_execution_state_x86:
  push ecx
  mov ecx, [esp + 8]
  mov dword [ecx], eax
  mov eax, ecx
  pop ecx
  mov dword [eax + 4], ecx
  mov dword [eax + 8], edx
  mov dword [eax + 12], ebx
  mov ecx, esp
  sub ecx, 4
  mov dword [eax + 16], ecx
  mov dword [eax + 20], ebp
  mov dword [eax + 24], esi
  mov dword [eax + 28], edi
  pop ecx
  push ecx
  mov dword [eax + 32], ecx
  ret 4