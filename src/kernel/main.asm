org 0x0 ; calculate all memory offsets from here -> this is a directive
bits 16 ; Emit 16 bit code

%define ENDL 0x0D, 0x0A
start:
    mov si, msg_hello
    call puts

; Prints string to screen
; Params - ds:si points to string
puts:
    ; save registers we will modify
    push si
    push ax
    push bx

.loop:
    lodsb           ; loads next character in al
    or al, al
    jz .done ; jump if zero flag set

    mov ah, 0x0e
    mov bh, 0
    int 0x10

    jmp .loop

.done:
    pop bx
    pop ax
    pop si
    ret

msg_hello: db 'Hello world from KaithanOS Kernel!', ENDL, 0