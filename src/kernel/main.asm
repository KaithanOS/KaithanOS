org 0x0 ; Always calculate addresses with this offset
bits 16 ; Must be backwards compatible with 8086 CPU. Tells assembler to emit 16-bit code

%define ENDL 0x0D, 0x0A

start:
  mov si, msg_hello
  call puts

.halt:
  cli
  hlt ; Halts processor

puts:
  push si
  push ax

.loop:
  lodsb
  or al, al
  jz .done

  mov ah, 0x0e
  mov bh, 0
  int 0x10

  jmp .loop

.done:
  pop ax
  pop si
  ret

msg_hello: db 'Hello world from Kernel!', ENDL, 0

