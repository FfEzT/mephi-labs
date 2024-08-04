; TODO разница equ and define
;    hall y nnnn ii vova avov voov
bits 64

global _start

section .data
SIZE equ 7

charCarry db 10
charSpace db ' '
charLen equ $ - charSpace

inputStr  times SIZE db 0
outputStr times SIZE db 0


delTab   equ 9
delEnter equ 10
delSpace equ ' '


msg1 db "Enter string: "
msg1Len equ $ - msg1

msgOk db "Ok)", 10
msgOkLen equ $ - msgOk


err1 db "Usage: "
err1Len equ $ - err1

err2 db " filename", 10
err2Len equ $ - err2

err3 db "errorDir", 10
err3Len equ $ - err3

err4 db "errorNoPerm", 10
err4Len equ $ - err4

err5 db "Just error :)", 10
err5Len equ $ - err4

;CREAT 100o
;TRUNC 1000o
; 00 RD
; 01 WR
; 02 WR
%define FILE_FLAGS 1101o
%define FLAG_CHMOD 666o ;права доступа

%define SYSCALL_READ  0
%define SYSCALL_WRITE 1
%define SYSCALL_OPEN  2

section .text
_start:
  cmp dword [rsp], 2
  jne errorCountArgs

; openfile:
  mov eax, SYSCALL_OPEN
  mov rdi, [rsp+16]
  mov esi, FILE_FLAGS
  mov edx, FLAG_CHMOD
  syscall

; check isOk open
  cmp eax, -21
  je errorDir
  cmp eax, -13
  je errorNoPerm
  or eax, eax
  jle hz

  ; NOTE r14d fileDesk
  mov r14d, eax

; init
  writeMsg1:
  ; NOTE r10b isPrintedBetweenBuf
  xor r10b, r10b
  ; NOTE r15d betweenBuffers
  mov r15d, 0
  ; NOTE 113b isLast
  mov r13b, 0


  mov eax, SYSCALL_WRITE
  mov edi, 1
  mov esi, msg1
  mov edx, msg1Len
  syscall

  scanf:
  ; NOTE r9b isPrinted
  xor r9b, r9b

    mov eax, SYSCALL_READ
    xor edi, edi
    mov esi, inputStr
    add esi, r15d

    mov edx, SIZE
    sub edx, r15d
    syscall

    cmp eax, -1
    je hz

    ; TODO здесь прикол
    ; если начнет считывать следующий буфер, то 
    cmp eax, 0
    je good_end

    ; cmp eax, SIZE - r15d
    add eax, r15d
    cmp eax, SIZE
    jge notLastBuf

    ; NOTE for 107 row
    sub eax, r15d

    mov r13b, 1
    ; NOTE r12d workingLen
    mov r12d, eax
    add r12d, r15d
    jmp palindrom


  notLastBuf:
    xor r15d, r15d
    ; NOTE for 107 row
    sub eax, r15d

  notLastBuf_:
    mov r11d, SIZE
    sub r11d, 1
    sub r11d, r15d

    cmp r11d, 0
    jl overBuffer

    ; NOTE dl str[size - 1 - betweenBuffers]
    mov dl, [inputStr + r11]

    cmp dl, delTab
    je afterNotLastBuf
    cmp dl, delEnter
    je afterNotLastBuf
    cmp dl, delSpace
    je afterNotLastBuf
    inc r15d
  jmp notLastBuf_

  afterNotLastBuf:
    ; NOTE r12d workingLen
    mov r12d, SIZE
    sub r12d, r15d
    jmp palindrom

  palindrom:
    ; NOTE ebx currentIndex
    xor ebx, ebx
    ; NOTE eax index
    xor eax, eax

    checkWhile:
      ; cmp byte[inputStr + rax], 0
      cmp eax, r12d
      jnl checkForWrite

      ; NOTE dl inputStr[index]
      mov dl, [inputStr + rax]
      cmp dl, delTab
      je m2
      cmp dl, delEnter
      je writeFile_
      ; je m2
      cmp dl, delSpace
      jne m1

      m2:
      inc eax
    jmp checkWhile


      m1:
      ; NOTE edi start
      mov edi, eax
      ; NOTE esi end
      mov esi, eax

      check1:
        ; NOTE dl inputStr[end]
        mov dl, [inputStr + esi]
        cmp dl, delEnter
        je m3
        cmp dl, delSpace
        je m3
        cmp dl, delTab
        je m3
        cmp esi, r12d
        jnl m3

        inc esi
        jmp check1

      m3:
      ; NOTE r8d afterWord
      mov r8d, esi
      dec esi

      ; NOTE ch, isPalindrom
      mov ch, 1

      check2:
        cmp edi, esi
        jnl endWhile2

        ; NOTE dl inputStr[start]
        mov dl, [inputStr + edi]
        ; NOTE dh inputStr[end]
        mov dh, [inputStr + esi]
        cmp dl, dh
        je m4
        mov ch, 0
        jmp endWhile2

        m4:
        inc edi
        dec esi
        jmp check2

      endWhile2:
        cmp ch, 1
        jne m5

        cmp r9b, 1
        jne startWhile
        mov byte[outputStr + ebx], delSpace
        inc ebx

        startWhile:
          mov r9b, 1
          cmp eax, r8d
          jnl m5

          ; NOTE dh, in[index]
          mov dh, [inputStr + eax]
          mov [outputStr + ebx], dh
          inc eax
          inc ebx
        jmp startWhile


      m5:
      mov eax, r8d
    jmp checkWhile

  ; NOTE В outputStr лежит результирующая строка, ее размер = ebx
  ; Осталось записать это все в файл

  checkForWrite:
  ; TODO rewrite with or
  cmp ebx, 0
  je checkIsLast
  cmp r10b, 1
  je writeSpace

  mov r10b, 1
  jmp writeFile

  writeSpace:
    mov eax, SYSCALL_WRITE
    mov edi, r14d
    mov esi, charSpace
    mov edx, charLen
    syscall

  writeFile:
    mov eax, SYSCALL_WRITE
    mov edi, r14d
    mov esi, outputStr
    mov edx, ebx
    syscall


  checkIsLast:
    cmp r13b, 1
    je nextLine

    ; NOTE ebx j
    mov ebx, SIZE
    sub ebx, r15d
    ; NOTE edi i
    xor edi, edi

    checkFor:
      cmp edi, r15d
      jnl scanf

      ; NOTE dh, inputStr[j]
      mov dh, [inputStr + ebx]
      mov [inputStr + rdi], dh

      inc edi
      inc ebx
    jmp checkFor

  nextLine:
    mov eax, SYSCALL_WRITE
    mov edi, r14d
    mov esi, charCarry
    mov edx, charLen
    syscall

    jmp writeMsg1

  writeFile_:

    ; TODO rewrite with or
    cmp ebx, 0
    je nextLine
    cmp r10b, 1
    jne kek

    mov eax, SYSCALL_WRITE
    mov edi, r14d
    mov esi, charSpace
    mov edx, charLen
    syscall

kek:
    mov eax, SYSCALL_WRITE
    mov edi, r14d
    mov esi, outputStr
    mov edx, ebx
    syscall

    jmp nextLine


  errorDir:
    mov eax, 1
    mov	edi, 2
    mov	esi, err3
    mov	edx, err3Len
    syscall

    mov edi, 2
    jmp end

  errorNoPerm:
    mov eax, 1
    mov	edi, 2
    mov	esi, err4
    mov	edx, err4Len
    syscall

    mov edi, 3
    jmp end

  hz:
    mov eax, 1
    mov	edi, 2
    mov	esi, err5
    mov	edx, err5Len
    syscall

    mov edi, 4
    jmp end

  errorCountArgs:
    mov eax, 1
    mov	edi, 2
    mov	esi, err1
    mov	edx, err1Len
    syscall

    mov	eax, 1
    mov	edi, 2
    mov	rsi, [rsp+8]
    xor	edx, edx
    m6:
      cmp	byte[rsi+rdx], 0
      je m7
      inc edx
      jmp m6
    m7:
      syscall

    mov	eax, 1
    mov	edi, 2
    mov	esi, err2
    mov	edx, err2Len
    syscall

    mov edi, 1
    jmp end

  overBuffer:
    ;close file
    mov eax, 3
    mov edi, r14d
    syscall

    jmp hz


  good_end:
    ;close file
    mov eax, 3
    mov edi, r14d
    syscall

    mov eax, SYSCALL_WRITE
    mov edi, 1
    mov esi, msgOk
    mov edx, msgOkLen
    syscall

    mov edi, 0
    jmp end

  end:
    mov eax, 60
    syscall
