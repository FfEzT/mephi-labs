bits 64
global fromColour2bwAsm


%define NUMBER_OF_SHADES 5


section .data
num255     dq 255.0
half       dq 0.5
state dd 0

section .text
; NOTE rdi res
; NOTE rsi src
; NOTE edx width
; NOTE ecx height
; NOTE r8d channels
fromColour2bwAsm:
  enter 0, 0
    stmxcsr [state]
    or dword [state], 0b110000000000000
    ldmxcsr [state]

  push rbx

  ; NOTE ebx, channels
  mov ebx, r8d

  ; NOTE r8d i
  xor r8d, r8d
  ; NOTE r9d channels * height * width
  mov r9d, ebx
  imul r9d, ecx
  imul r9d, edx


  ; NOTE xmm2 CONVERSION_FACTOR
  movsd xmm2, [num255]
  mov ecx, NUMBER_OF_SHADES
  dec ecx
  cvtsi2sd xmm1, ecx
  divsd xmm2, xmm1


  ; NOTE xmm1 = channels
  cvtsi2sd xmm1, ebx
  ; NOTE xmm3 = 0.5
  movsd xmm3, [half]

  xor ecx, ecx

  ; NOTE r11d (int) CONVERSION_FACTOR
  cvtsd2si r11d, xmm2

.startFor:
  cmp r8d, r9d
  jge .end

  ; NOTE r10d sum
  mov r10d, 0

  ; NOTE edx j
  mov edx, 0

  .startJ:
    cmp edx, ebx
    jnl .endJ
    add r8d, edx
    mov cl, [rsi + r8]
    sub r8d, edx
    add r10d, ecx

    inc edx
  jmp .startJ


  .endJ:

  ; NOTE xmm0, averageValue
  cvtsi2sd xmm0, r10d
  divsd xmm0, xmm1

  ; NOTE xmm0 averageValue / CONVERSION_FACTOR + 0.5
  divsd xmm0, xmm2
  addsd xmm0, xmm3

  ; NOTE r10d gray
  cvtsd2si r10d, xmm0
  imul r10d, r11d

  ; NOTE eax j = i
  mov eax, r8d
  .secondFor:
    sub eax, ebx
    cmp eax, r8d
    jge .endSecondFor
    add eax, ebx

    mov [rdi + rax], r10b
    inc eax
  jmp .secondFor

  .endSecondFor:
  add r8d, ebx
jmp .startFor


.end:
  pop rbx
  leave
  ret
