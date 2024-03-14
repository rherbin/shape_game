CC = gcc
ARGS = -Wall -g
INCLUDES = -I./SDL2/include
SRC_DIR = ./SDL2_gfx
MODULES = ./modules

ifeq ($(OS),Windows_NT)
    LIBS = -L./SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
    TARGET = main.exe
else
    LIBS = -L./SDL2/bin/ -lSDL2 -lSDL2_ttf -lSDL2_image -lm
    TARGET = main
endif

ifeq ($(OS),Linux)
    RPATH = -Wl,-rpath=./SDL2/lib
endif

SRCS = $(SRC_DIR)/SDL2_rotozoom.c \
       $(SRC_DIR)/SDL2_gfxPrimitives.c \
       $(MODULES)/ansi_escape.c \
       $(MODULES)/utils.c \
       main.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(ARGS) $(INCLUDES) $(OBJS) $(LIBS) $(RPATH) -o $(TARGET)

%.o: %.c
	$(CC) $(ARGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)