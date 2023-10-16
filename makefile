# ----------------------------------------------------------------------------------
#  CONFIG
# ----------------------------------------------------------------------------------
EXE ?= game
BUILD ?= RELEASE
ASSETS_DIR ?= assets

CC := gcc
COMPILER_FLAGS := -O2 -Wall
LINKER_FLAGS := -lGL -lm -lpthread -ldl -lrt -lX11
SRC_FILES := $(wildcard src/*.c) $(wildcard src/*/*.c)
DEFINES :=

# ----------------------------------------------------------------------------------
#  OS SETUP
# ----------------------------------------------------------------------------------
EXE_EXT :=

ifeq ($(OS), Windows_NT)
	EXE_EXT := .exe
	LINKER_FLAGS := -lopengl32 -lgdi32 -lwinmm
endif

# ----------------------------------------------------------------------------------
#  CONFIG SETUP
# ----------------------------------------------------------------------------------
ifeq ($(BUILD), DEBUG)
	LINKER_FLAGS += -g
	DEFINES += -DBUILD_DEBUG
else
	DEFINES += -DBUILD_RELEASE
endif

.PHONY: build run clean release

build:
	$(CC) $(DEFINES) $(SRC_FILES) $(COMPILER_FLAGS) -lraylib $(LINKER_FLAGS) -o $(EXE)$(EXE_EXT)

run:
	./$(EXE)$(EXE_EXT)

clean:
	rm $(EXE)$(EXE_EXT)

release:
	zip -r $(EXE)$(EXE_EXT) $(ASSETS_DIR)/
