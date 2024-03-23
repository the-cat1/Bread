# Makefile

# Version Release
VERSION			= 0.0.1
COMPILE_NUM		= 1

# Make
MAKE_ARGS		= --no-print-directory

# Compile
CC				= gcc
BUILD_DIR		= build
RELEASE_DIR		= release

INCLUDE 		= include
CARGS			= -I $(INCLUDE) -mwindows
ifeq ($(debug), true)
	CARGS += -g
endif

TARGETS 		= bread window/window window/windowproc graphics/render util/list

objs = $(foreach F,$(TARGETS),$(BUILD_DIR)/$(F).o )

all:
	$(MAKE) $(MAKE_ARGS) main

main:
	@echo """"""""""""""""""""""""""""""""""""""""""""""
	@echo "         ____                     _         "
	@echo "        | __ ) _ __ ___  __ _  __| |        "
	@echo "        |  _ \| '__/ _ \/ _` |/ _` |        "
	@echo "        | |_) | | |  __/ (_| | (_| |        "
	@echo "        |____/|_|  \___|\__,_|\__,_|        "
	@echo "                                            "
	@echo """"""""""""""""""""""""""""""""""""""""""""""
	@echo Bread Version $(VERSION)($(COMPILE_NUM))
ifneq ($(OS), Windows_NT)
	@echo Bread just can compile or run on Windows!
else
	$(MAKE) folder
	$(MAKE) $(RELEASE_DIR)/libbread.a
endif

test:
	$(MAKE) main
	$(CC) test.c -o test.exe -L$(RELEASE_DIR) -lbread $(CARGS)

$(RELEASE_DIR)/libbread.a: $(objs) $(HEAD_FILES)
	ar -rc $(RELEASE_DIR)/libbread.a $(objs)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CARGS) -c $*.c -o $(BUILD_DIR)/$*.o

folder:
	if not exist $(BUILD_DIR) md $(BUILD_DIR)
	if not exist $(BUILD_DIR)\window md $(BUILD_DIR)\window
	if not exist $(BUILD_DIR)\graphics md $(BUILD_DIR)\graphics
	if not exist $(BUILD_DIR)\util md $(BUILD_DIR)\util

	if not exist $(RELEASE_DIR) md $(RELEASE_DIR)

clean:
	if exist $(BUILD_DIR) rd /S /Q $(BUILD_DIR)
	if exist $(RELEASE_DIR) rd /S /Q $(RELEASE_DIR)
	if exist test.exe del test.exe
