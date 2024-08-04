bits	64
global	main


ERROR_ARGS equ 1
ERROR_OPEN_FILE equ 2
ERROR_INPUT_ARGS equ 3
ERROR equ 4


INF equ 0x7fffffffffffffff

extern	fabs
extern	printf
extern  fopen
extern	scanf
extern sqrt
extern  fclose
extern  fprintf


section .data
output db "%d) %f", 10, 0

offsetX_ equ 16
offsetPrecision_ equ offsetX_ + 16
offsetPart equ offsetPrecision_ + 16
offsetAccum equ offsetPart + 16
offsetTmp equ offsetAccum + 16
offsetRes_ equ offsetTmp + 16

offset6 equ offsetRes_ + 16
offset7 equ offset6 + 16
offset8 equ offset7 + 16
offset9 equ offset8 + 16


section .text
; NOTE rdi File
; NOTE rsi pointer res
; NOTE xmm0 first args, x
; NOTE xmm1 second args, precision
myF:
  enter offset9, 0

  movsd [rbp - offsetX_], xmm0
  movsd [rbp - offsetPrecision_], xmm1

  push rbx
  push r12

  ; NOTE rbx FILE*
  mov rbx, rdi

  cmp rsi, 0
  je .badPoint

  mov [rbp - offsetRes_], rsi

  ; x < -1?
  mov rcx, -1
  movsd xmm2, xmm0

  cvtsi2sd xmm3, rcx
  cmplesd xmm2, xmm3
  cvtsd2si rcx, xmm2
  test rcx, rcx
  jnz .badArgs

  ; x > 1?
  mov rcx, 1
  movsd xmm2, xmm0

  cvtsi2sd xmm3, rcx
  cmplesd xmm3, xmm2
  cvtsd2si rcx, xmm3
  test rcx, rcx
  jnz .badArgs

  ; precision < 0?
  mov rcx, 0
  movsd xmm2, xmm1

  cvtsi2sd xmm3, rcx
  cmplesd xmm2, xmm3
  cvtsd2si rcx, xmm2
  test rcx, rcx
  jnz .badArgs




    mov rdi, rbx
    mov rsi, output
    mov edx, 0
    ; NOTE ecx tmp
    mov ecx, 1
    ; NOTE xmm2 accum
    cvtsi2sd xmm0, ecx
    call fprintf
    movsd xmm0, [rbp - offsetX_]
    movsd xmm1, [rbp - offsetPrecision_]

      mov ecx, -1
      cvtsi2sd xmm6, ecx
      mov ecx, 1
      cvtsi2sd xmm7, ecx
      mov ecx, 2
      cvtsi2sd xmm8, ecx
      mov ecx, 4
      cvtsi2sd xmm9, ecx
      movsd [rbp - offset6], xmm6
      movsd [rbp - offset7], xmm7
      movsd [rbp - offset8], xmm8
      movsd [rbp - offset9], xmm9


  ; NOTE xmm2 accum
  movsd xmm2, xmm7
  ; NOTE xmm3 part
  movsd xmm3, xmm7

  ; NOTE r12d n
  mov r12d, 1
.startFor:

    ; NOTE xmm4 tmp
    movsd xmm4, xmm6
    mulsd xmm3, xmm4
    mulsd xmm3, xmm0

    movsd xmm4, xmm8
    mulsd xmm3, xmm4
    cvtsi2sd xmm4, r12d
    mulsd xmm3, xmm4

    movsd xmm4, xmm8
    ; NOTE xmm5 tmp
    cvtsi2sd xmm5, r12d
    mulsd xmm4, xmm5
    movsd xmm5, xmm7
    subsd xmm4, xmm5
    mulsd xmm3, xmm4

    movsd xmm4, xmm9
    divsd xmm3, xmm4

    cvtsi2sd xmm4, r12d
    divsd xmm3, xmm4
    divsd xmm3, xmm4

    movsd xmm4, xmm8
    cvtsi2sd xmm5, r12d
    mulsd xmm5, xmm4
    movsd xmm4, xmm7
    subsd xmm4, xmm5
    movsd [rbp - offsetTmp], xmm4
    divsd xmm3, xmm4

    addsd xmm2, xmm3



    movsd [rbp - offsetAccum], xmm2
    movsd [rbp - offsetPart], xmm3

    mov rdi, rbx
    mov rsi, output
    mov edx, r12d
    movsd xmm0, xmm3

    call fprintf

    movsd xmm0, [rbp - offsetX_]
    movsd xmm1, [rbp - offsetPrecision_]
    movsd xmm2, [rbp - offsetAccum]
    movsd xmm3, [rbp - offsetPart]
    movsd xmm6, [rbp - offset6]
    movsd xmm7, [rbp - offset7]
    movsd xmm8, [rbp - offset8]
    movsd xmm9, [rbp - offset9]


    ; NOTE xmm4 copyX
    movsd xmm4, xmm0
    movsd xmm0, xmm3

    call fabs
    cmpltsd xmm0, xmm1
    movq rcx, xmm0
    test rcx, rcx
    jnz .endFor

    movsd xmm0, xmm4

    movsd xmm4, [rbp - offsetTmp]
    mulsd xmm3, xmm4

    inc r12d
jmp .startFor

.endFor:
  mov eax, 1


.end:
  mov rsi, [rbp - offsetRes_]
  movsd [rsi], xmm2
  pop r12
  pop rbx
  leave
  ret

.badArgs:
  mov rcx, INF
  cvtsi2sd xmm2, rcx
  mov eax, 0
  jmp .end

.badPoint:
  pop r12
  pop rbx
  leave
  ret


section	.data
res dq 0

msgUsage      db "Usage ./a.out file", 10,0
msgError      db "Error", 10,0
msgOk         db "Ok)", 10,0
msgFile       db "Error file opening", 10,0
scanX         db "X         >> ",0
scanPresicion db "precision >> ",0

printMath db   "sqrt(1+x) = %lf", 10,0
printMyMath db "My        = %lf", 10,0

scanfDouble db "%lf", 0
file_flags db "w", 0

EOF equ -1

; VARIABLES
offsetX equ 16
offsetPrecision equ offsetX + 16


section .text
main:
  ; NOTE я был прав, выравнивание по 16 байт
  enter 16, 0

  cmp rdi, 2
  jne .errorArgs


  mov rdi, [rsi + 8]
  xor rax, rax
  lea rsi, [file_flags]
  call fopen
  cmp rax, 0
  jle .errorFile

  ; NOTE r12 FILE*
  mov r12, rax


  xor eax, eax
  mov rdi, scanX
  call printf

  xor eax, eax
  mov rdi, scanfDouble
  lea rsi, [rbp - offsetX]
  call scanf
  cmp eax, EOF
  je .good_end

  xor eax, eax
  mov rdi, scanPresicion
  call printf

  xor eax, eax
  mov rdi, scanfDouble
  lea rsi, [rbp - offsetPrecision]
  call scanf
  cmp eax, EOF
  je .good_end


  mov ecx, 1
  cvtsi2sd xmm1, ecx
  movsd xmm0, [rbp - offsetX]
  addsd xmm0, xmm1
  call sqrt

  mov eax, 1
  mov rdi, printMath
  call printf

  mov rdi, r12
  mov rsi, res
  movsd xmm0, [rbp - offsetX]
  movsd xmm1, [rbp - offsetPrecision]
  call myF

  test eax, eax
  jz .justError

  mov eax, 1
  mov rdi, printMyMath
  movsd xmm0, [res]
  call printf


  jmp .good_end


.errorFile:
  mov rdi, msgFile
  xor rax, rax
  call printf
  mov eax, ERROR_OPEN_FILE
jmp .end

.justError:
  mov rdi, msgError
  xor rax, rax
  call printf
  mov eax, ERROR
jmp .end

.errorArgs:
  mov rdi, msgUsage
  call printf
  mov eax, ERROR_ARGS
  jmp .end

.good_end:
  mov rdi, r12
  call fclose
  xor eax, eax
  mov rdi, msgOk
  call printf

.end:
  leave
  ret
