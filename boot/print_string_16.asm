print_string_16:   		; declare function name so it can be called
	pusha			; push registers to the stack to preserve state
	
	mov ah, 0x0e		; signals to bios al contains char

get_char:			; label for looping
	mov al, [bx]		; but the character referenced to by bx in al
	add bx, 0x01		; increment bx so it points to next char
	
	cmp al, 0		; is al null terminator?
	je terminated		; if yes, jump to terminated

	int 0x10		; else, print the char to the screen

	jmp get_char		; continue loop
	

terminated:			; if al is null terminator:
	popa			; pop registers from stack back into place

	ret			; return to the place that called this function
