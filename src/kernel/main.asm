org 0x7C00 ; Always calculate addresses with this offset
bits 16 ; Must be backwards compatible with 8086 CPU. Tells assembler to emit 16-bit code

%define ENDL 0x0D, 0x0A

start:
  jmp main

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

main:

  mov ax, 0 ; can't write to ds/es directly
  mov ds, ax
  mov es, ax

  ; setup stack
  mov ss, ax
  mov sp, 0x7C00 ; stack grows downwards from where we are loaded in memory

  mov si, msg_hello
  call puts

  hlt ; Halts processor

.halt: ; Sometimes it falls through after the hlt instruction
  jmp .halt

msg_hello: db 'Hello world!', ENDL, 0

; db is an instruction that writes given byte(s) to the assembled binary file
; this line essentially calculates 510 minus (current line's address minus beginning of current section, or in other words, the length of the program)
times 510-($-$$) db 0
dw 0AA55h
