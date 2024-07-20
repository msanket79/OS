ASM=nasm

SRC_DIR=src
BUILD_DIR=build


#Floppy Image
floppy_image: $(BUILD_DIR)/main.img
$(BUILD_DIR)/main.img: bootloader KRNLDR
	dd if=/dev/zero of=$(BUILD_DIR)/main.img bs=512 count=2880 
	mkfs.fat -F 12 -n "FALCONOS" $(BUILD_DIR)/main.img

	dd if=$(BUILD_DIR)/BOOT.BIN of=$(BUILD_DIR)/main.img conv=notrunc
	dd if=$(BUILD_DIR)/BOOT.BIN of=$(BUILD_DIR)/main.img conv=notrunc
	mcopy -i $(BUILD_DIR)/main.img $(BUILD_DIR)/KRNLDR.SYS "::KRNLDR.SYS"

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
	$(ASM) $(SRC_DIR)/bootloader/stage2.asm -f bin -o $(BUILD_DIR)/KRNLDR.SYS


clean:
	rm -f build/main.img build/BOOT.BIN build/KRNLDR.SYS


