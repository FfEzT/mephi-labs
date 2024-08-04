global _start
; TODO параметр сортировки

; TODO
; можно n,m превратить в EQU
section .data
  n db 2 ; row
  m db 7 ; column

  SIZE_EL equ 2 ; 2byte

  matrix:
    dw 18,-9,-18,1,14,0,-1
    dw 758,9999,0xffff,32,5,6,7

  res:
    times 14 dw 0

  index:
    db  0, 1, 2, 3, 4,5,6

; TODO use uninit section
  max:
    times 7 dw 0

section .text
_start:
  mov r9, matrix

  movsx di, byte[n]
  movsx bx, byte[m]
  cmp bx, 1
  jle good_end
  mov dx, 0 ; j

  getMax:
    cmp dx, bx
    jge sort


    mov si, 0x8000 ; min num in word

    test di, di
    jz endGetMax_
    mov cx, di ; i

    metka:
      ; r9 + cx*bx*SIZE_EL + dx * SIZE_EL
      mov r8, rcx
      dec r8
      imul r8, rbx

      add r8, rdx
      imul r8, SIZE_EL

      add r8, r9

      cmp si, [r8]
      jge endGetMax_secondCycle
      mov si, [r8]

    endGetMax_secondCycle:
      loop metka

    ; for i
    endGetMax_:
      mov [max + rdx*SIZE_EL], si
      inc dx
      jmp getMax

  ; for j
  sort:
    xor r8, r8
    xor si, si ; left
    xor cx, cx ; k
    mov r11w, bx ; right
    mov rax, max ; max

    start_loop:
      inc si
      cmp si, r11w
      jge end_sort

      mov dx, [rax + rcx * SIZE_EL] ;a1
      mov r8w, [rax + rsi*SIZE_EL] ; a2
      mov r14b, [index + rcx] ;i1
      mov r15b, [index + rsi] ;i2

      cmp dx, r8w

%ifidni SORT_ORDER,ASK
      jge while1
%else
      jle while1
%endif
      xchg dx, r8w
      xchg r14b, r15b


    while1:
      dec cx
      cmp cx, 0
      jl passWhile1
      mov r10w, [rax + rcx * SIZE_EL] ; a[k]
      cmp dx, r10w

%ifidni SORT_ORDER,ASK
      jge passWhile1
%else
      jle passWhile1
%endif

      mov r13b, [index + rcx] ; index[k]
      add cx, 2
      mov [rax + rcx*SIZE_EL], r10w
      mov [index + rcx], r13b
      sub cx, 2
      jmp while1

    passWhile1:
      ;xor r10w
      add cx, 2
      mov [rax + rcx * SIZE_EL], dx
      mov [index + rcx], r14b
      dec cx

    while2:
      dec cx
      cmp cx, 0
      jl passWhile2
      mov r10w, [rax + rcx * SIZE_EL] ; a[k]
      cmp r8w, r10w

%ifidni SORT_ORDER,ASK
      jge passWhile2
%else
      jle passWhile2
%endif

      mov r13b, [index + rcx] ; index[k]
      inc cx
      mov [index + rcx], r13b
      mov [rax + rcx*SIZE_EL], r10w
      dec cx
      jmp while2

    passWhile2:
      inc cx
      mov [rax + rcx * SIZE_EL], r8w
      mov [index + rcx], r15b
      dec cx

    end_loop:
      inc si
      mov cx, si
      jmp start_loop

  end_sort:
  general_insertion_sort:
    ; si left
    ; rax maxPtr

    ; r11w right
    dec r11w
    mov dx, [rax + r11 * SIZE_EL] ; last
    mov r13b, [index + r11] ; lastI

    start_general_loop:
      dec r11w
      cmp r11w, 0
      jl passLoop
      mov r8w, [rax + r11 * SIZE_EL] ; a[right]
      cmp dx, r8w

%ifidni SORT_ORDER,ASK
      jnl passLoop
%else
      jng passLoop
%endif

      mov r14b, [index + r11]; index[right]
      inc r11w
      mov [rax + r11 * SIZE_EL], r8w
      mov [index + r11], r14b
      dec r11w
      jmp start_general_loop

    passLoop:
      inc r11w
      mov [rax + r11 * SIZE_EL], dx
      mov [index + r11], r13b
      dec r11w

; xor r10w, r10w
; xor r13b, r13b
; xor r14b, r14b
; xor r15b, r15b

  xor dx,dx ;j
  ; r9 = matrix
  mov rax, res; res ptr

  startMV:
    cmp dx, bx ;j, m
    jnl endForJ

    mov r13b, [index + rdx] ; column

    xor si,si ;i
    startI:
      cmp si, di; i,n
      jnl endForI

      mov cx, si
      imul ecx, ebx
      add rcx, r13


      ; mov [rax + rsi*rbx*SIZE_EL + rdx * SIZE_EL], [matrix + rsi*rbx*SIZE_EL + r13 * SIZE_EL]
      mov r11w, [matrix + rcx*SIZE_EL]

      sub rcx, r13
      add rcx, rdx
      mov [rax + rcx*SIZE_EL], r11w

      inc si
      jmp startI

    endForI:
      inc dx
      jmp startMV

  endForJ:

  ; xor r11w,r11w
  ; xor rcx,rcx
  ; xor r8w,r8w
  ; xor rax,rax
  ; xor dx,dx
  ; xor si,si
  good_end:
    mov edi,0
    jmp end

  end:
    mov eax, 60
    syscall
