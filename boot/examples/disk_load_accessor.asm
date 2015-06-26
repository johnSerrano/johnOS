[org 0x7c00]
	mov [BOOT_DRIVE], dl
	mov bp, 0x8000
	mov sp, bp
	mov bx, 0x0000
	mov es, bx
	mov bx, 0x9000			; es:bx loc in mem to write to
	mov dh, 2			; dh number of sectors to write to
	mov dl, [BOOT_DRIVE]
	
	push bx
	pop bx
	call disk_load

	mov dx, [0x9000]
	call print_hex

	mov dx, [0x9200]
	call print_hex

	jmp $


BOOT_DRIVE:
	db 0


%include "disk_load.asm"
%include "print_string.asm"	
%include "print_hex.asm"

	times 510-($-$$) db 0

	dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
