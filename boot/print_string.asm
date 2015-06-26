	; params: ebx = string to write


	[bits 32]

	VIDEO_MEM equ 0xb8000
	WH_ON_BL equ 0x0f

print_string:
	pusha
	mov edx, VIDEO_MEM

print_string_loop:
	mov al, [ebx]
	mov ah, WH_ON_BL

	cmp al, 0
	je print_string_done

	mov [edx], ax

	add ebx, 1
	add edx, 2

	jmp print_string_loop

print_string_done:
	popa
	ret
