BUILD_DIR?=build/
INCLUDE_DIR=./Include
ASM?=nasm

.PHONY: all clean

all:stage2

stage2 : $(BUILD_DIR)/KRNLDR.SYS

$(BUILD_DIR)/KRNLDR.SYS :	stage2.asm
	@$(ASM) -I$(INCLUDE_DIR) $< -f bin -o $@
	@echo "--->Created KRNLDR.SYS"

clean:
	@rm -f $(BUILD_DIR)/KRNLDR.SYS
