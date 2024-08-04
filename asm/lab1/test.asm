bits 64
global _start


section .text
_start:
  mov ax, 0xFfff
  mov bx, 0x1
  add ax, bx
  adc dx, bx

  mov edi, eax
  mov eax, 60
  syscall
