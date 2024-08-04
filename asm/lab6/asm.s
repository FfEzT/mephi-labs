bits 64
global fromColour2bwAsm


%define NUMBER_OF_SHADES 5


section .data
num255     dd 255.0
half       dd 0.5
vHalf      dd 0.5, 0.5, 0.5, 0.5
vThree     dd 3.0,3.0,3.0,3.0
three      dd 3.0
state dd 0

section .text
; NOTE rdi res
; NOTE rsi src
; NOTE edx width
; NOTE ecx height
fromColour2bwAsm:
  enter 0, 0
    stmxcsr [state]
    or dword [state], 0b110000000000000
    ldmxcsr [state]

  ; NOTE xmm2 CONVERSION_FACTOR
  movss xmm2, [num255]
  mov eax, NUMBER_OF_SHADES
  dec eax
  cvtsi2ss xmm1, eax
  divss xmm2, xmm1

  ; NOTE xmm3 CONVERSION_FACTOR
  movss xmm3, xmm2

  ; NOTE xmm2 CONVERSION_FACTOR vector float
  pxor xmm1, xmm1
  movss xmm1, xmm2
  pslldq xmm1, 4
  por xmm2, xmm1
  pslldq xmm1, 4
  por xmm2, xmm1
  pslldq xmm1, 4
  por xmm2, xmm1

  ; NOTE xmm8 CONVERSION_FACTOR vector int
  cvtps2dq xmm8, xmm2

  ; NOTE xmm1 vHalf
  movaps xmm1, [vHalf]

  ; NOTE xmm9 vThree float
  movaps xmm9, [vThree]

  mov rax, 0ff000000ffh
  push rax
  push rax
  ; NOTE xmm4 mask Last byte
  movaps xmm4, [rbp - 16]

  mov edx, edx
  mov eax, ecx
  mul rdx

  mov ecx, 4
  ; NOTE edx width*height%4
  div ecx

  ; NOTE ecx width*height/4
  mov ecx, eax

.looping:
  movaps xmm5, [rsi]
  movaps xmm6, xmm5
  movaps xmm7, xmm5

  psrldq xmm6, 1
  psrldq xmm7, 2

  pand xmm5, xmm4
  pand xmm6, xmm4
  pand xmm7, xmm4

  ; NOTE xmm5 r+g+b vector word
  paddw xmm5, xmm6
  paddw xmm5, xmm7

  ; NOTE xmm6 float vector / CONVERSION_FACTOR + 0.5
  cvtdq2ps xmm6, xmm5
  divps xmm6, xmm9
  divps xmm6, xmm2
  addps xmm6, xmm1

  ; NOTE xmm5 int HZ res for 1 channel
  cvtps2dq xmm5, xmm6
  pmulld xmm5, xmm8

  movaps xmm6, xmm5
  movaps xmm7, xmm5
  pslldq xmm6, 1
  pslldq xmm7, 2
  pslldq xmm4, 3
  por xmm5, xmm6
  por xmm5, xmm7
  por xmm5, xmm4

  movaps [rdi], xmm5
  add rdi, 16
  add rsi, 16

  psrldq xmm4, 3
loop .looping

  xor eax, eax

  ; NOTE r8d (int)CONVERSION_FACTOR
  cvtss2si r8d, xmm3

  ; NOTE xmm1 half
  movss xmm1, [half]

  ; NOTE xmm9 Three float
  movss xmm9, [three]

.looping2:
  cmp edx, 0
  jle .end

  ; NOTE ecx sum
  xor ecx, ecx
  mov al, [rsi]
  add ecx, eax
  mov al, [rsi+1]
  add ecx, eax
  mov al, [rsi+2]
  add ecx, eax
  add rsi, 4

  ; NOTE xmm5 сумма / 3 / CONVERSION_FACTOR + 0.5
  cvtsi2ss xmm5, ecx
  divss xmm5, xmm9
  divss xmm5, xmm3
  addss xmm5, xmm1

  cvtss2si ecx, xmm5
  imul ecx, r8d

  mov [rdi], ecx
  mov [rdi + 1], ecx
  mov [rdi + 2], ecx
  mov byte[rdi + 3], 255

  add rdi, 4

dec edx
jmp .looping2






.end:
  leave
  ret

