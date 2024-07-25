ASM=nasm
CC=i686-elf-gcc
CXX=i686-elf-g++
CFLAGS= -std=c99 -g -ffreestanding -nostdlib
LINKFLAGS=-T linker.ld -nostdlib
LIBS=-lgcc
LD=i686-elf-gcc
SRC_DIR=src
BUILD_DIR=build

.PHONY: floppy_image load debug bootloader KRNLDR KRNL clean

#Floppy Image
floppy_image: $(BUILD_DIR)/main.img
$(BUILD_DIR)/main.img: bootloader KRNLDR KRNL
	dd if=/dev/zero of=$(BUILD_DIR)/main.img bs=512 count=2880 
	mkfs.fat -F 12 -n "FALCONOS" $(BUILD_DIR)/main.img

	dd if=$(BUILD_DIR)/BOOT.BIN of=$(BUILD_DIR)/main.img conv=notrunc
	dd if=$(BUILD_DIR)/BOOT.BIN of=$(BUILD_DIR)/main.img conv=notrunc
	mcopy -i $(BUILD_DIR)/main.img $(BUILD_DIR)/KRNLDR.SYS "::KRNLDR.SYS"
	mcopy -i $(BUILD_DIR)/main.img $(BUILD_DIR)/KRNL.SYS "::KRNL.SYS"

#dd command -- copies data from if to of bs--> is block size and count is how many blocks (/dev/zero will contain 0)

load: floppy_image
	qemu-system-i386 -fda build/main.img

debug: floppy_image
	qemu-system-i386 -fda build/main.img -s -S

# bootloader
bootloader:	$(BUILD_DIR)/BOOT.BIN
$(BUILD_DIR)/BOOT.BIN:
	$(ASM) $(SRC_DIR)/bootloader/boot.asm -f bin -o $(BUILD_DIR)/BOOT.BIN

# kernel
KRNLDR: $(BUILD_DIR)/KRNLDR.SYS
$(BUILD_DIR)/KRNLDR.SYS:
	$(ASM) $(SRC_DIR)/stage2/stage2.asm -f bin -o $(BUILD_DIR)/KRNLDR.SYS

KRNL: $(BUILD_DIR)/KRNL.SYS
$(BUILD_DIR)/KRNL.SYS:$(BUILD_DIR)/KRNL.obj
	$(LD) $(LINKFLAGS) -Wl,-Map=$(BUILD_DIR)/kernel.map $(BUILD_DIR)/KRNL.obj -o $(BUILD_DIR)/KRNL.SYS $(LIBS)

$(BUILD_DIR)/KRNL.obj: $(SRC_DIR)/kernel/kernel.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/KRNL.obj $(SRC_DIR)/kernel/kernel.c


	

clean:
	rm -f $(BUILD_DIR)/* 


