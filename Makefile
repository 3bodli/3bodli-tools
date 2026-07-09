# Makefile لـ 3bodli Tools
TARGET		:= 3bodli_tools
TITLE_ID	:= BD3B00001
CONTENT_ID	:= IV0000-BD3B00001_00-3BODLITOOLS0001

SRC_DIR		:= src
BUILD_DIR	:= build
ASSETS_DIR	:= assets

SRCS		:= $(wildcard $(SRC_DIR)/*.c)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LIBS		:= -lSceSysmodule_stub -lSceSystemService_stub \
			   -lScePigletv2Vsh_stub -lSceSaveData_stub \
			   -lSceNet_stub -lkernel_stub

PREFIX		:= arm64-scei-ps4-elf
CC			:= $(PREFIX)-gcc
CFLAGS		:= -Wall -O2 -I$(SRC_DIR)
LDFLAGS		:= -L$(OO_PS4_TOOLCHAIN)/lib $(LIBS) \
			   -Wl,-T,$(OO_PS4_TOOLCHAIN)/lib/linker.x

all: dirs $(TARGET).elf

dirs:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BUILD_DIR)/$@
	@echo "Build complete: $(BUILD_DIR)/$(TARGET).elf"

pkg: $(TARGET).elf
	@echo "Creating PKG..."
	bash pkg_build.sh

clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build files"

install:
	@echo "Copy to USB and run on PS4"

.PHONY: all dirs pkg clean install
