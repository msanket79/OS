BUILD_DIR?=build/
ASM?=nasm

.PHONY: all clean

all:stage1


stage1: $(BUILD_DIR)/BOOT.BIN

$(BUILD_DIR)/BOOT.BIN:boot.asm
	@$(ASM) $< -f bin -o $@
	@echo "--->Created BOOT.BIN"

clean:
	@rm -f $(BUILD_DIR)/BOOT.BIN
