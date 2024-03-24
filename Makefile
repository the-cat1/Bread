# Bread
# Makefile

# Make Bread. Use 'make help' to get help.

# Version
VERSION			= 0.0.1

# Make
MAKE_ARGS		= --no-print-directory
ECHO_TAG		= [Bread]
ECHO			= @echo [Bread]

# Compile
CC				= gcc
AR				= ar

INCLUDE 		= include
CARGS			= -I $(INCLUDE) -mwindows

TARGETS 		= bread window/window window/windowproc graphics/render util/list
PROJECT_DIRS	= window graphics util
BUILD_DIR		= build
DEBUG_DIR		= debug
RELEASE_DIR		= release
RELEASE_DIRS	=
BINARY_FILE_NAME= libbread.a

# debug mode
debug_mode		= 0
ifeq ("$(debug)"", "true")
  debug_mode	= 1
endif
ifeq ("$(d)", "true")
  debug_mode	= 1
endif

ifeq ($(debug_mode), 1)
  CARGS			+= -g
endif

ifeq ($(debug_mode), 1)
  binary_file	= $(DEBUG_DIR)/$(BINARY_FILE_NAME)
else
  binary_file	= $(RELEASE_DIR)/$(BINARY_FILE_NAME)
endif

ifeq ($(debug_mode), 1)
  out_dir		= $(DEBUG_DIR)
else
  out_dir		= $(BUILD_DIR)
endif

out_dirs		= $(foreach F,$(PROJECT_DIRS),$(out_dir)\$(F))
release_dirs	= $(foreach F,$(RELEASE_DIRS),$(RELEASE_DIR)\$(F))
objs 			= $(foreach F,$(TARGETS),$(out_dir)/$(F).o)

all:
	@$(MAKE) $(MAKE_ARGS) main

main:
	@echo """"""""""""""""""""""""""""""""""""""""""""""
	@echo "         ____                     _         "
	@echo "        | __ ) _ __ ___  __ _  __| |        "
	@echo "        |  _ \| '__/ _ \/ _` |/ _` |        "
	@echo "        | |_) | | |  __/ (_| | (_| |        "
	@echo "        |____/|_|  \___|\__,_|\__,_|        "
	@echo "                                            "
	@echo """"""""""""""""""""""""""""""""""""""""""""""
	@echo Bread Makefile / Bread version $(VERSION)
ifeq ($(debug_mode), 1)
	@echo                                   * DEBUG MODE
endif
ifneq ($(OS), Windows_NT)
	$(error Bread just can compile or run on Windows!)
else
	@echo Output directory: $(out_dir)
  ifeq ($(debug_mode), 0)
	@echo Release directory: $(RELEASE_DIR)
  endif

	@$(MAKE) folder
	@$(MAKE) $(binary_file)
endif

$(binary_file): $(objs) $(HEAD_FILES)
	$(ECHO) Making $(binary_file)...
	@$(AR) -rc $(binary_file) $(objs)

$(out_dir)/%.o: %.c
	$(ECHO) Compiling $*.c ...
	@$(CC) $(CARGS) -c $*.c -o $(out_dir)/$*.o

folder:
	$(ECHO) Created output directories...
	@$(foreach F,$(out_dirs),if not exist $(F) (md $(F)) &&) echo nul > NUL

	$(ECHO) Creating release directories...
	@if not exist $(RELEASE_DIR) md $(RELEASE_DIR)
#	@$(foreach F,$(release_dirs),if not exist $(F) (md $(F)) &&) echo nul > NUL

clean:
	$(ECHO) Deleting files...
	@if exist $(BUILD_DIR) rd /S /Q $(BUILD_DIR)
	@if exist $(RELEASE_DIR) rd /S /Q $(RELEASE_DIR)
	@if exist $(DEBUG_DIR) rd /S /Q $(DEBUG_DIR)
	@if exist test.exe del test.exe

test:
	@$(MAKE) $(MAKE_ARGS) all
	$(CC) test.c -o test.exe -L$(dir $(binary_file)) -lbread $(CARGS)

help:
	@echo Help of Bread Makefile.
	@echo Target:
	@echo     all         Make Bread and exit.
	@echo     clean       Delete all output files.
	@echo Arguments:
	@echo     debug(or d) If it set to true then enter to DEBUG MODE.
	@echo                 DEBUG MODE: Take -g when compiling and set output to $(DEBUG_DIR).
