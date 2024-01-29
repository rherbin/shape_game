# Makefile for compiling the SDL program

CC = gcc
CFLAGS = -Wall
INCLUDES = -I./SDL2/include
LIBS = -L./SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
SRC_DIR = ./SDL2_gfx
MODULES_DIR = ./modules

SRCS = $(SRC_DIR)/SDL2_rotozoom.c \
       $(SRC_DIR)/SDL2_gfxPrimitives.c \
       $(MODULES_DIR)/ansi_escape.c \
       $(MODULES_DIR)/utils.c \
       main.c

OBJS = $(SRCS:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)