CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I./SDL2/include
SRC_DIR = ./SDL2_gfx
MODULES_DIR = ./modules

ifeq ($(OS),Windows_NT)
    LIBS = -L./SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
    TARGET = main.exe
else
    LIBS = -L. -lSDL2 -lSDL2_ttf -lSDL2_image -lm
    TARGET = main
endif

# Ajout de -Wl,-rpath
ifeq ($(OS),Linux)
    RPATH = -Wl,-rpath=./SDL2/lib
endif

SRCS = $(SRC_DIR)/SDL2_rotozoom.c \
       $(SRC_DIR)/SDL2_gfxPrimitives.c \
       $(MODULES_DIR)/ansi_escape.c \
       $(MODULES_DIR)/utils.c \
       main.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) $(RPATH) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
