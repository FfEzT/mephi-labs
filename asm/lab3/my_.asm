; TODO разница equ and define
; TODO сделать флаг типа, если первый раз пишем, то юзаем trunc, иначе без него
; TODO all constants rewrite with using equ/define
; TODO все метки сделать локальными
bits 64

global _start

section .data
msg1 db "Enter string: "
msg1Len equ $ - msg1

SIZE equ 1024

inputStr  times SIZE db 0
outputStr times SIZE db 0

delTab   equ 9
delENTER equ 10
delSpace equ ' '


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
%define FILE_flags 1101o
%define FLAG_chmod 666o ;права доступа


section .text
_start:
  ; считывание аргументов
  ; cmp dword [rsp], 2
  ; jne .errorCountArgs
  ;
  ; ; NOTE ptr To name of file from arg
  ; mov r15, [rsp+16]

  ; вывод msg1
  ; mov eax, 1
  ; mov edi, 1
  ; mov esi, msg1
  ; mov edx, msg1Len
  ; syscall

  ; NOTE r13d кол-во символов, которые могут быть началом слова на стыке буферов
  ; mov r13d, 0

  .getString:
    ; scanf
    xor eax, eax
    xor edi, edi
    mov esi, inputStr
    mov edx, SIZE
    syscall

  .getPalindrome:
    ; NOTE ebx currentIndex
    xor ebx, ebx
    ; NOTE eax index
    mov eax, 0

    .checkWhile:
      cmp byte[inputStr + rax], 0
      je .writeFile

      ; NOTE dl inputStr[index]
      mov dl, [inputStr + rax]
      cmp dl, delTab
      je .m2
      cmp dl, delENTER
      je .m2
      cmp dl, delSpace
      jne .m1

      .m2:
      inc eax
      jmp .checkWhile


      .m1:
      ; NOTE edi start
      mov edi, eax
      ; NOTE esi end
      mov esi, eax

      .check1:
        ; NOTE dl inputStr[end]
        mov dl, [inputStr + esi]
        cmp dl, delENTER
        je .m3
        cmp dl, delSpace
        je .m3
        cmp dl, delTab
        je .m3
        cmp dl, 0
        je .m3

        inc esi
        jmp .check1

      .m3:
      ; NOTE r8d afterWord
      mov r8d, esi
      dec esi

      ; NOTE ch, isPalindrom
      mov ch, 1

      .check2:
        cmp edi, esi
        jnl .endWhile2

        ; NOTE dl inputStr[start]
        mov dl, [inputStr + edi]
        ; NOTE dh inputStr[end]
        mov dh, [inputStr + esi]
        cmp dl, dh
        je .m4
        mov ch, 0
        jmp .endWhile2

        .m4:
        inc edi
        dec esi
        jmp .check2

      .endWhile2:
      cmp ch, 1
      jne .m5

        .startWhile:
        cmp eax, r8d
        jnl .m5

        ; NOTE dh, in[index]
        mov dh, [inputStr + eax]
        mov [outputStr + ebx], dh
        inc eax
        inc ebx
        jmp .startWhile


      .m5:
      mov eax, r8d
      jmp .checkWhile

    ; NOTE В outputStr лежит результирующая строка, ее размер = ebx
    ; ОСталось записать это все в файл (название в t15)

  .writeFile:
    ; mov eax, 2
    ; mov rdi, r15
    ; mov esi, FILE_flags
    ; mov edx, FLAG_chmod
    ; syscall
    ;
    ; cmp eax, -21
    ; je .errorDir
    ; cmp eax, -13
    ; je .errorNoPerm
    ; or eax, eax
    ; jle .hz

    ; NOTE r14 fileDescriptor
    mov r14d, eax
    mov eax, 1
    mov edi, r14d
    mov esi, outputStr
    mov edx, ebx
    syscall

    mov eax, 3
    mov edi, r14d
    syscall
    jmp good_end

  ; errorDir:
  ;   mov eax, 1
  ;   mov	edi, 2
  ;   mov	esi, err3
  ;   mov	edx, err3Len
  ;   syscall
  ;
  ;   mov edi, 2
  ;   jmp end
  ;
  ; errorNoPerm:
  ;   mov eax, 1
  ;   mov	edi, 2
  ;   mov	esi, err4
  ;   mov	edx, err4Len
  ;   syscall
  ;
  ;   mov edi, 3
  ;   jmp end
  ;
  ; hz:
  ;   mov eax, 1
  ;   mov	edi, 2
  ;   mov	esi, err5
  ;   mov	edx, err5Len
  ;   syscall
  ;
  ;   mov edi, 4
  ;   jmp end
  ;
  ; errorCountArgs:
  ;   mov eax, 1
  ;   mov	edi, 2
  ;   mov	esi, err1
  ;   mov	edx, err1Len
  ;   syscall
  ;
  ;   mov	eax, 1
  ;   mov	edi, 2
  ;   mov	rsi, [rsp+8]
  ;   xor	edx, edx
  ;   m1:
  ;     cmp	byte[rsi+rdx], 0
  ;     je m2
  ;     inc edx
  ;     jmp m1
  ;   m2:
  ;     syscall
  ;
  ;   mov	eax, 1
  ;   mov	edi, 2
  ;   mov	esi, err2
  ;   mov	edx, err2Len
  ;   syscall
  ;
  ;   mov edi, 1
  ;   jmp end
  ;
  ;
  ; good_end:
  ;   mov edi, 0
  ;   jmp end
  ;
  ; end:
  ;   mov eax, 60
  ;   syscall
