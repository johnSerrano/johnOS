	;; dependency: gdt_start.asm
	
	[bits 16]

switch_to_pm:

	cli				; Clear interrupts

	lgdt [gdt_descriptor]		; load gdt as defined earlier


	mov eax, cr0			; set cr0 first bit to indicate 32-bit protected mode
	or eax, 0x1
	mov cr0, eax


	jmp CODE_SEG:init_pm		; far jump to clear ... something, idk

	
	[bits 32]

init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM




