org 0x7C00 ; Always calculate addresses with this offset
bits 16 ; Must be backwards compatible with 8086 CPU. Tells assembler to emit 16-bit code

%define ENDL 0x0D, 0x0A

; FAT12 Header
jmp short start
nop

bdb_oem: db 'MSWIN4.1'
bdb_bytes_per_sector: dw 512
bdb_sectors_per_cluster: db 1
bdb_reserved_sectors: dw 1
bdb_fat_count: db 2
bdb_dir_entries_count: dw 0E0h
bdb_total_sectors: dw 2880
bdb_media_descriptor_type: db 0F0h
bdb_sectors_per_fat: dw 9
bdb_sectors_per_track: dw 18
bdb_heads: dw 2
bdb_hidden_sectors: dd 0
bdb_large_sector_count: dd 0

; Extended boot record
ebr_drive_number: db 0
                  db 0
ebr_signature: db 29h
ebr_volume_id: db 12h, 34h, 56h, 78h
ebr_volume_label: db 'KAITHAN  OS' ; 11 bytes
ebr_system_id: db 'FAT12   ' ; 8 bytes

start:
  ; setup data segments
  mov ax, 0 ; can't write to ds/es directly
  mov ds, ax
  mov es, ax

  ; setup stack
  mov ss, ax
  mov sp, 0x7C00 ; stack grows downwards from where we are loaded in memory

  ; Some BIOSes start at 07C0:0000
  push es
  push word .after
  retf

.after:

  ; Read from floppy disk
  mov [ebr_drive_number], dl


  mov si, msg_loading
  call puts

  ; read drive params
  push es
  mov ah, 08h
  int 13h
  jc floppy_error
  pop es

  and cl, 0x3F
  xor ch, ch
  mov [bdb_sectors_per_track], cx

  inc dh
  mov [bdb_heads], dh

  ; read FAT root directory
  mov ax, [bdb_sectors_per_fat] ; compute LBA of root directory
  mov bl, [bdb_fat_count]
  xor bh, bh
  mul bx
  add ax, [bdb_reserved_sectors]
  push ax

  mov ax, [bdb_sectors_per_fat] ; compute size of root directory
  shl ax, 5
  xor dx, dx
  div word [bdb_bytes_per_sector]

  test dx, dx
  jz .root_dir_after
  inc ax

.root_dir_after:

  ; read root directory
  mov cl, al
  pop ax
  mov dl, [ebr_drive_number]
  mov bx, buffer
  call disk_read

  ; search for kernel
  xor bx, bx
  mov di, buffer

.search_kernel:
  mov si, file_kernel_bin
  mov cx, 11
  push di
  repe cmpsb
  pop di
  je .found_kernel

  add di, 32
  inc bx
  cmp bx, [bdb_dir_entries_count]
  jl .search_kernel

  ; kernel not found
  jmp kernel_not_found_error

.found_kernel:

  ; di should have the address to the entry
  mov ax, [di + 26]
  mov [kernel_cluster], ax

  mov ax, [bdb_reserved_sectors]
  mov bx, buffer
  mov cl, [bdb_sectors_per_fat]
  mov dl, [ebr_drive_number]
  call disk_read

  ; read kernel and process FAT chain
  mov bx, KERNEL_LOAD_SEGMENT
  mov es, bx
  mov bx, KERNEL_LOAD_OFFSET

.load_kernel_loop:
  ; read next cluster
  mov ax, [kernel_cluster]
  add ax, 31
  mov cl, 1
  mov dl, [ebr_drive_number]
  call disk_read

  add bx, [bdb_bytes_per_sector]

  ; compute location of next cluster
  mov ax, [kernel_cluster]
  mov cx, 3
  mul cx
  mov cx, 2
  div cx

  mov si, buffer
  add si, ax
  mov ax, [ds:si]

  or dx, dx
  jz .even

.odd:
  shr ax, 4
  jmp .next_cluster_after

.even:
  and ax, 0x0FFF

.next_cluster_after:
  cmp ax, 0x0FF8
  jae .read_finish
  mov [kernel_cluster], ax
  jmp .load_kernel_loop

.read_finish:

  ; jump to kernel
  mov dl, [ebr_drive_number]

  mov ax, KERNEL_LOAD_SEGMENT
  mov ds, ax
  mov es, ax

  jmp KERNEL_LOAD_SEGMENT:KERNEL_LOAD_OFFSET

  jmp wait_key_and_reboot

  cli
  hlt ; Halts processor

; Error handlers
floppy_error:
  mov si, msg_read_failed
  call puts
  jmp wait_key_and_reboot

kernel_not_found_error:
  mov si, msg_kernel_not_found
  call puts
  jmp wait_key_and_reboot

wait_key_and_reboot:
  mov ah, 0
  int 16h
  jmp 0FFFFh:0

.halt:
  cli
  hlt

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

; Disk routines

;
; Converts LBA to CHS
; Parameters:
;   - ax: LBA address
; Returns:
;   - cx [bits 0-5]: sector number
;   - cx [bits 6-15]: cylinder
;   - dh: head
;

lba_to_chs:

  push ax
  push dx

  xor dx, dx
  div word [bdb_sectors_per_track]

  inc dx
  mov cx, dx

  xor dx, dx
  div word [bdb_heads]

  mov dh, dl
  mov ch, al
  shl ah, 6
  or cl, ah

  pop ax
  mov dl, al
  pop ax
  ret

;
; Reads sectors from a disk
; Parameters:
;   - ax: LBA address
;   - cl: number of sectors to read (up to 128)
;   - dl: drive number
;   - es:bx: memory address where to store read data
;
disk_read:

  push ax
  push bx
  push cx
  push dx
  push di

  push cx
  call lba_to_chs
  pop ax

  mov ah, 02h
  mov di, 3 ; retry count

.retry:
  pusha
  stc
  int 13h
  jnc .done

  popa
  call disk_reset

  dec di
  test di, di
  jnz .retry

.fail:
  jmp floppy_error

.done:
  popa

  pop di
  pop dx
  pop cx
  pop bx
  pop ax
  ret

;
; Resets disk controller
; Parameters:
;   - dl: drive number
;
disk_reset:
  pusha
  mov ah, 0
  stc
  int 13h
  jc floppy_error
  popa
  ret

msg_loading: db 'Loading...', ENDL, 0
msg_read_failed: db 'Read from disk failed!', ENDL, 0
msg_kernel_not_found: db 'KERNEL.BIN file not found!', ENDL, 0
file_kernel_bin: db 'KERNEL  BIN', ENDL, 0
kernel_cluster: dw 0

KERNEL_LOAD_SEGMENT equ 0x2000
KERNEL_LOAD_OFFSET equ 0

; db is an instruction that writes given byte(s) to the assembled binary file
; this line essentially calculates 510 minus (current line's address minus beginning of current section, or in other words, the length of the program)
times 510-($-$$) db 0
dw 0AA55h

buffer:

