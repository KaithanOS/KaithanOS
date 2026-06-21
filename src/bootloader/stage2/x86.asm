bits 16

section _TEXT class=CODE

;
; void _cdecl x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotientOut, uint32_t* remainderOut);
;
global _x86_div64_32
_x86_div64_32:


  ; make new call frame
  push bp ; save old call frame
  mov bp, sp ; init new call frame

  push bx

  ; divide upper 32 bits
  mov eax, [bp + 8] ; upper 32 bits of dividend
  mov ecx, [bp + 12] ; divisor
  xor edx, edx
  div ecx ; eax - quotient, edx - remainder

  ; store upper 32 bits of quotient
  mov bx, [bp + 16]
  mov [bx + 4], eax

  ; divide lower 32 bits
  mov eax, [bp + 4]
  div ecx

  mov [bx], eax
  mov bx, [bp + 18]
  mov [bx], edx

  pop bx

  ; restore old call frame
  mov sp, bp
  pop bp
  ret

;
; int 10h ah=0Eh
; args: character, page
global _x86_Video_WriteCharTeletype
_x86_Video_WriteCharTeletype:

  ; make new call frame
  push bp ; save old call frame
  mov bp, sp ; init new call frame

  ; [bp + 0] - old call frame
  ; [bp + 2] -  return address
  ; [bp + 4] -  first argument - the character
  ; [bp + 6] -  second argument - the page
  mov ah, 0Eh
  mov al, [bp + 4]
  mov bh, [bp + 6]

  int 10h

  pop bx

  ; restore old call frame
  mov sp, bp
  pop bp
  ret
