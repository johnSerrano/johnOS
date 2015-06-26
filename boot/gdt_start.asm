gdt_start:

gdt_null:			; null descriptor

	dd 0x0
	dd 0x0


gdt_code:			; gdt code segment descriptor

	dw 0xffff		; Limit set to maximum
	dw 0x0			; first 16 bits of BASE
	db 0x0			; next 8 bits of BASE
	db 10011010b		; flags:
	                        ; present = 1
	                        ; privilege = 00
	                        ; descriptor type: 1
 				; Type Flags:
				; code = 1
				; conforming = 1
				; readable = 1
				; accessed = 0
	db 11001111b		; more flags:
				; granularity = 1
				; 32-bit = 1
				; 64 bit = 0
				; avl = 0
				; limit = f
	db 0x0			; next 8 bits of base

gdt_data:
	
		dw 0xffff		; Limit set to maximum
	dw 0x0			; first 16 bits of BASE
	db 0x0			; next 8 bits of BASE
	db 10010010b		; flags:
	                        ; present = 1
	                        ; privilege = 00
	                        ; descriptor type: 1
 				; Type Flags:
				; code = 0
				; conforming = 1
				; readable = 1
				; accessed = 0
	db 11001111b		; more flags:
				; granularity = 1
				; 32-bit = 1
				; 64 bit = 0
				; avl = 0
				; limit = f
	db 0x0			; next 8 bits of base

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1 ; size of gdt less one
	dd gdt_start		   ; addr of start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start	
