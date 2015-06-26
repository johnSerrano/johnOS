[org 0x7c00]

	KERNEL_OFFSET equ 0x1000

	mov [BOOT_DRIVE], dl
	
	mov bp, 0x9000
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print_string_16 	; so we get this far
	
	call load_kernel_label	; then this should run
	
	call switch_to_pm

	jmp $



	
load_kernel_label:
	mov bx, MSG_LOAD_KERN	
	call print_string_16	; but this never does

	mov bx, 0x0000
	mov es, bx
	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load
	
	ret

MSG_PROT_MODE:
	db "Booted into protected mode", 0
	
MSG_REAL_MODE:
	db "Booted into real mode", 0

MSG_LOAD_KERN:
	db "Loading kernel", 0

BOOT_DRIVE:
	db 0

%include "print_string_16.asm"
%include "gdt_start.asm"	
	
%include "switch_to_pm.asm"
%include "disk_load.asm"



	
[bits 32]
	
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string

	call KERNEL_OFFSET
	
	
	jmp $



%include "print_string.asm"	

	
	times 510-($-$$) db 0

	dw 0xaa55
