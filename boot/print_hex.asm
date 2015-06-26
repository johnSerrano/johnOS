; params: dx = value to print

; dependency note: calling file must include print_string.asm
print_hex:
	pusha
	
	mov bx, HEXOUT
	add bx, 0x2
	mov ax, 12

char_check:

	mov cx, dx

	push ax
shift:

	cmp ax, 0
	je below_0
	shr cx, 1
	sub ax, 1
	jmp shift
	
	
below_0:

	and cx, 0xf
	cmp cx, 0x0
	jne below_1
	mov al, '0'
	mov [bx], al	
	jmp end
below_1:
	cmp cx, 0x1
	jne below_2
	mov al, '1'
	mov [bx], al
	jmp end
below_2:
	cmp cx, 0x2
	jne below_3
	mov al, '2'
	mov [bx], al	
	jmp end
below_3:
	cmp cx, 0x3
	jne below_4
	mov al, '3'
	mov [bx], al
	jmp end
below_4:
	cmp cx, 0x4
	jne below_5
	mov bl, '4'
	mov [bx], al
	jmp end
below_5:
	cmp cx, 0x5
	jne below_6
	mov al, '5'
	mov [bx], al
	jmp end
below_6:
	cmp cx, 0x6
	jne below_7
	mov al, '6'
	mov [bx], al
	jmp end
below_7:
	cmp cx, 0x7
	jne below_8
	mov al, '7'	
	mov [bx], al
	jmp end
below_8:
	cmp cx, 0x8
	jne below_9
	mov al, '8'
	mov [bx], al
	jmp end
below_9:
	cmp cx, 0x9
	jne below_10
	mov al, '9'
	mov [bx], al
	jmp end
below_10:
	cmp cx, 0xa
	jne below_11
	mov al, 'a'
	mov [bx], al
	jmp end
below_11:
	cmp cx, 0xb
	jne below_12
	mov al, 'b'
	mov [bx], al
	jmp end
below_12:
	cmp cx, 0xc
	jne below_13
	mov al, 'c'
	mov [bx], al
	jmp end
below_13:
	cmp cx, 0xd
	jne below_14
	mov al, 'd'
	mov [bx], al
	jmp end
below_14:
	cmp cx, 0xe
	jne below_15
	mov al, 'e'
	mov [bx], al
	jmp end
below_15:
	cmp cx, 0xf
	jne def_end
	mov al, 'f'
	mov [bx], al
	jmp end
def_end:
	mov al, '.'
	mov [bx], al

end:	
	pop ax
	cmp ax, 0
	je fin

	add bx, 1
	sub ax, 4
	jmp char_check
		
fin:
	mov bx, HEXOUT
	call print_string

	popa

	ret




HEXOUT:
	db "0x0000", 0

