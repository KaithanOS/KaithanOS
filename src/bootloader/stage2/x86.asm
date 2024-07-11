bits 16

section _TEXT class=CODE

global _x86_Video_WriteCharTeletype

_x86_Video_WriteCharTeletype:

    push bp
    mov bp, sp

    ;      BP (old val)  SP  ...
    ;      ^ new BP

    ; save bx
    push bx

    ; [bp + 0] - old call frame
    ; [bp + 2] - return address (small memory model, so 2 byte addresses)
    ; [bp + 4] - first argument (character)
    ; [bp + 6] - second argument (page)
    ; note: bytes converted to words (cannot push one byte onto stack, must push in multiples of 2)
    mov ah, 0Eh // ah contains value 0E
    mov al, [bp + 2] // al contains the character
    mov bh, [bp + 4] // bh contains the page

    int 10h

    ; restore bx (callee saved)
    pop bx

    mov sp, bp
    pop bp
    ret
