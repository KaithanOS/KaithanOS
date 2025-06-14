org 0x7C00 ; calculate all memory offsets from here -> this is a directive
bits 16 ; Emit 16 bit code

%define ENDL 0x0D, 0x0A
start:
    jmp main

; Prints string to screen
; Params - ds:si points to string
puts:
    ; save registers we will modify
    push si
    push ax

.loop:
    lodsb           ; loads next character in al
    or al, al
    jz .done ; jump if zero flag set

    mov ah, 0x0e
    int 0x10

    jmp .loop

.done:
    pop ax
    pop si
    ret

main:

    mov ax, 0
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7C00 ; stack grows downwards

    mov si, msg_hello
    call puts

    hlt ; this is an instruction

.halt:
    jmp .halt

msg_hello: db 'Hello world!', ENDL, 0

times 510-($-$$) db 0 ; $ is memory position of current line, $$ is the current section. $ - $$ = length of program so far.
; Fill 510 bytes, set the last two bytes as AA55 (this is a convention).
dw 0AA55h