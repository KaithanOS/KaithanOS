bits 16 // writing 16 bit code

section _ENTRY class=CODE

extern _cstart_
global entry

entry:
    cli
    mov ax, ds
    moc ss, ax
    mov sp, 0
    mov bp, sp
    sti

    ; expect boot drive in dl, send as argument to cstart
    xor dh, dh
    push dx
    call _cstart_

    cli hlt


