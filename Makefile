

all: os_image

run: all
	qemu-system-i386 os_image

os_image: kernel/kernel.bin kernel/pad.bin
	cat boot/boot_sector.bin kernel/kernel.bin kernel/pad.bin > os_image

kernel/kernel.bin: kernel/cm.bin kernel/kernel.o drivers/screen.o kernel/utils.o drivers/keyboard.o kernel/commands/command.o
	ld -o kernel/kernel.bin kernel/cm.bin kernel/kernel.o kernel/utils.o drivers/screen.o drivers/keyboard.o kernel/commands/command.o kernel/commands/helloWorld.o --oformat binary -melf_i386 -e main

kernel/kernel.o: 
	gcc -ffreestanding -m32 -c kernel/kernel.c -o kernel/kernel.o

kernel/cm.bin:
	nasm -f elf kernel/call_main.asm -o kernel/cm.bin

kernel/utils.o:
	gcc -ffreestanding -m32 -c kernel/utils.c -o kernel/utils.o

drivers/screen.o:
	gcc -ffreestanding -m32 -c drivers/screen.c -o drivers/screen.o

drivers/keyboard.o:
	gcc -ffreestanding -m32 -c drivers/keyboard.c -o drivers/keyboard.o

kernel/commands/command.o: kernel/commands/helloWorld.o
	gcc -ffreestanding -m32 -c kernel/commands/command.c -o kernel/commands/command.o

kernel/commands/helloWorld.o:
	gcc -ffreestanding -m32 -c kernel/commands/helloWorld.c -o kernel/commands/helloWorld.o

kernel/pad.bin:
	nasm -f bin kernel/padding20sectors.asm -o kernel/pad.bin

clean:
	rm kernel/*.bin kernel/*.o drivers/*.o kernel/commands/*.o
