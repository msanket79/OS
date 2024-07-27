BUILD_DIR?=build/
CODEDIRS=. ../Lib
INCDIRS=. ../Include

TARGET_CC=i686-elf-gcc
TARGET_CXX=i686-elf-g++
OPT=-O0
TARGET_CFLAGS= -std=c99 -g -ffreestanding -nostdlib $(foreach D, $(INCDIRS) , -I$(D)) $(OPT)
TARGET_LIBS=-lgcc

TARGET_LD=i686-elf-gcc
TARGET_LINKFLAGS=-T linker.ld -nostdlib

CFILES := $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o, $(CFILES))

all: $(BUILD_DIR)/KRNL.SYS

$(BUILD_DIR)/KRNL.SYS : $(OBJECTS)
	@$(TARGET_LD) $(TARGET_LINKFLAGS) -Wl,-Map=$(BUILD_DIR)/kernel.map $^ -o $@ $(TARGET_LIBS)
	@echo "-->created KRNL.SYS"

%.o : %.c
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<
	@echo "--->compiled: " $<

clean:
	@rm -rf $(OBJECTS)


