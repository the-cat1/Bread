# Makefile

# Version
VERSION			= 0.0.1
COMPILE_NUM		= 1

#Make
MAKE_ARGS		= -s

# Compile
CC				= gcc
OBJECTS 		= bread window/window window/windowproc util/list

INCLUDE 		= include
CARGS			= -I $(INCLUDE) -mwindows
ifeq ($(debug), true)
	CARGS += -g
endif

objs = $(foreach F,$(OBJECTS),build/$(F).o )

all:
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
	$(MAKE) $(MAKE_ARGS) folder
	$(MAKE) $(MAKE_ARGS) libbread.a
endif

test:
	$(MAKE) $(MAKE_ARGS) folder
	$(MAKE) $(MAKE_ARGS) libbread.a
	$(CC) test.c -o test.exe -L./ -lbread $(CARGS)

libbread.a: $(objs)
	ar -rc libbread.a $(objs)

build/%.o: %.c
	$(CC) $(CARGS) -c $*.c -o build/$*.o

folder:
	if not exist build md build
	if not exist build\window md build\window
	if not exist build\util md build\util

clean:
	del /S /Q build
	del /Q libbread.a
	del /Q test.exe
