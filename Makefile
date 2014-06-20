###############################################################################
#	makefile
#	 original by Alex Chadwick
#	 modded for LuPI by Lukasz Magiera
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
# arm-linux-gnueabihf
ARMGNU ?= arm-none-eabi

CC = gcc
LD = ld

#  -march=armv6zk -mtune=arm1176jzf-s
# The intermediate directory for compiled object files.
BUILD = bin/
SOURCE = src/
LUA = resourcues/lua


# LDPARAMS = -L/usr/arm-linux-gnueabihf/lib -L/usr/lib/gcc-cross/arm-linux-gnueabihf/4.8 #-lc -lg -lm -lgcc
LDPARAMS = -Lbinlibs -L/usr/local/arm-none-eabi/lib -L/usr/local/lib/gcc/arm-none-eabi/4.8.4 -lnewc -lcsud -lm -lgcc
CCPARAMS = -c -std=c99 -Isrc/lib/lua -Iinclude -mcpu=arm1176jzf-s
ASPARAMS = -Iresourcues 
LUAPARAMS = $(LUA) src/gen/luares.h src/gen/luares.c lua_


# All standard liblaries
LIBS = $(wildcard lib/*.a)

# The name of the output file to generate.
TARGET = kernel.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

SRCDIRECTORIES = $(shell find $(SOURCE) -type d)
BUILDDIRECTORIES = $(patsubst $(SOURCE)%, $(BUILD)%, $(SRCDIRECTORIES))

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.

#OBJECTS := 	$(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))	\
#			$(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))

CFILES = $(shell find $(SOURCE) -type f -name '*.c')
ASMFILES = $(shell find $(SOURCE) -type f -name '*.s')

OBJECTS :=	$(patsubst $(SOURCE)%.c, $(BUILD)%.c.o, $(CFILES))	\
			$(patsubst $(SOURCE)%.s, $(BUILD)%.s.o, $(ASMFILES))

# Rule to make everything.
all: smallclean $(BUILDDIRECTORIES) luaresources $(TARGET) $(LIST)

smallclean:
	find . -name '*~' -type f -exec rm {} \;

build: clean all

# Rule to remake everything. Does not include clean.
rebuild: all

cleanresourcues:
	-rm -f src/gen/*
	mkdir -p src/gen/
	touch src/gen/luares.c
	touch src/gen/luares.h

luaresources: cleanresourcues
	./txt2c $(LUAPARAMS)

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET) 

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS) $(LINKER)
	$(ARMGNU)-$(LD) --no-undefined $(OBJECTS) $(LDPARAMS) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the object files.
$(BUILD)%.s.o: $(SOURCE)%.s $(BUILD)
	$(ARMGNU)-as $(ASPARAMS) -I $(SOURCE) $< -o $@
	
$(BUILD)%.c.o: $(SOURCE)%.c $(BUILD)
	$(ARMGNU)-$(CC) $(CCPARAMS) -I $(SOURCE) $< -o $@

$(BUILDDIRECTORIES):
	mkdir $@

# Rule to clean files.
clean : cleanresourcues
	-rm -rf $(BUILD)
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
	

