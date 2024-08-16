BUILD_DIR = build

.PHONY : all  floppy_image load debug bootloader stage1 stage2 kernel clean debug-gdb

all:floppy_image


#Floppy Image
floppy_image: $(BUILD_DIR)/main.img

$(BUILD_DIR)/main.img: bootloader kernel
	@dd if=/dev/zero of=$(BUILD_DIR)/main.img bs=512 count=2880 
	@mkfs.fat -F 12 -n "FALCONOS" $@
	@dd if=$(BUILD_DIR)/BOOT.BIN of=$@ conv=notrunc
	@mcopy -i $@ $(BUILD_DIR)/KRNLDR.SYS "::KRNLDR.SYS"
	@mcopy -i $@ $(BUILD_DIR)/KRNL.SYS "::KRNL.SYS"

#dd command -- copies data from if to of bs--> is block size and count is how many blocks (/dev/zero will contain 0)

load: floppy_image
	@qemu-system-i386 -fda  build/main.img 

debug: floppy_image
	@qemu-system-i386 -m 512m -object memory-backend-file,id=mem,size=512M,mem-path=./qemu-ram,share=on -machine memory-backend=mem -fda  build/main.img 


debug-gdb: floppy_image
	@qemu-system-i386 -fda build/main.img -s -S

# bootloader
bootloader:	stage1 stage2

stage1 : $(BUILD_DIR)/BOOT.BIN

$(BUILD_DIR)/BOOT.BIN:
	@$(MAKE) --no-print-directory -C SysBoot/stage1 BUILD_DIR=$(abspath $(BUILD_DIR)) 

stage2 : $(BUILD_DIR)/KRNLDR.SYS

$(BUILD_DIR)/KRNLDR.SYS:
	@$(MAKE) --no-print-directory -C SysBoot/stage2 BUILD_DIR=$(abspath $(BUILD_DIR))

kernel : $(BUILD_DIR)/KRNL.SYS

$(BUILD_DIR)/KRNL.SYS:
	@$(MAKE) --no-print-directory -C SysCore/Kernel BUILD_DIR=$(abspath $(BUILD_DIR))

clean:
	@$(MAKE) --no-print-directory -C SysBoot/stage1 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	@$(MAKE) --no-print-directory -C SysBoot/stage2 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	@$(MAKE) --no-print-directory -C SysCore/Kernel BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	@rm -rf $(BUILD_DIR)/*
	@echo "--->Deleted all build files"


