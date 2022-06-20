i686-elf-gcc -std=gnu99 -ffreestanding -g -c boot.s -o boot.o
i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o
i686-elf-gcc -T linker.ld -o leaf.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

if grub-file --is-x86-multiboot leaf.bin; then
	echo multiboot confirmed
else
	echo the file is not multiboot
fi
