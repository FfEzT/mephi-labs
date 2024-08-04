bits 64
global _start


section .data
  a dd 0xffffffff
  b dd 0xffffffff
  c dd 0xfffe
  d dw 0xffff
  e dw 0

  res dq 0

; (abc - cde)/(a/b + c/d)
; a ebp
; b ebx
; c ecx
; d esi
section .text
_start:
; in rdi знаменатель
  mov ebx, dword[b]
  test ebx, ebx
  jz error_zero

  movzx esi, word[d]
  test esi, esi
  jz error_zero

  mov eax, dword[a]
  mov ebp, eax
  ; cdq
  div ebx
  mov edi, eax

  mov eax, dword[c]
  mov ecx, eax
  ; cdq
  xor edx, edx
  div esi


  add rax, rdi
  jc oh_OF

  test rax, rax
  jz error_zero
  mov rdi, rax
;END in rdi знаменатель

; in rbp 1-ое слагаемое числителя
  ; NOTE cache
  mov eax, ebp
  ; mov ebx, dword[b]
  ; mov ecx, dword[c]

  mul ebx
  sal rdx, 32
  or rax, rdx

  mul rcx
  mov rbx, rdx
  mov rbp, rax
;END in rbx:rbp 1-ое слагаемое числителя

; in rdx:rax 2-второе слагаемое числителя
  movzx edx, word[e]
  mov eax, esi

  mul edx
  ; shl
  sal rdx, 32
  or rax, rdx

  mul rcx

;END in rdx:rax 2-второе слагаемое числителя

  sub rbp, rax
  sbb rbx, rdx
  jc oh_OF

  mov rdx, rbx
  mov rax, rbp

  div rdi
; TODO что будет если DE флаг

  mov [res], eax

  good_end:
    mov edi, [res]
    ; mov edi, 0
    jmp end

  error_zero:
    mov edi, 1
    jmp end

  oh_OF:
    mov edi, 2
    jmp end

  end:
    mov eax, 60
    syscall
