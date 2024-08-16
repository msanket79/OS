BUILD_DIR?=build/
CODEDIRS=. ../Lib ../hal/src
INCDIRS=. ../Include ../hal/Include

TARGET_CC=i686-elf-gcc
TARGET_CXX=i686-elf-g++
OPT=-O0
TARGET_CFLAGS= -std=c99 -g -ffreestanding -nostdlib $(foreach D, $(INCDIRS), -I$(D)) $(OPT)
TARGET_LIBS=-lgcc

TARGET_LD=i686-elf-gcc
TARGET_LINKFLAGS=-T linker.ld -nostdlib

CFILES := $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
ASMFILES := $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.asm))
COBJECTS := $(patsubst %.c, $(BUILD_DIR)/c_objects/%.o, $(CFILES))
ASMOBJECTS := $(patsubst %.asm, $(BUILD_DIR)/asm_objects/%.o, $(ASMFILES))
OBJECTS := $(COBJECTS) $(ASMOBJECTS)
headers=$(patsubst %.c,%fileheadr.txt, $(CFILES)) $(patsubst %.asm,%fileheadr.txt, $(ASMFILES))
assemblys=$(patsubst %.c,%assembly.txt, $(CFILES)) $(patsubst %.asm,%assembly.txt, $(ASMFILES))

all: $(BUILD_DIR)/KRNL.SYS

$(BUILD_DIR)/KRNL.SYS : $(OBJECTS)
	@$(TARGET_LD) $(TARGET_LINKFLAGS) -Wl,-Map=$(BUILD_DIR)/kernel.map $^ -o $@ $(TARGET_LIBS)
	@echo "--> created KRNL.SYS"

# Compile C source files to object files
$(BUILD_DIR)/c_objects/%.o : %.c
	@mkdir -p $(dir $@)
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<
	# objdump -t -M intel  $@ > $(basename $<)fileheadr.txt
	# objdump -d -M intel  $@ > $(basename $<)assembly.txt
	@echo "---> compiled: " $<

# Assemble ASM files to object files
$(BUILD_DIR)/asm_objects/%.o : %.asm
	@mkdir -p $(dir $@)
	@nasm -f elf32 -o $@ $<
	# objdump -t -M intel  $@ > $(basename $<)fileheadr.txt
	# objdump -d -M intel  $@ > $(basename $<)assembly.txt
	@echo "---> assembled: " $<

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(headers)
	@rm -rf $(assemblys)
