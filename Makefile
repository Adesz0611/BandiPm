# Makefile for BandiPm
PROGNAME = bandipm
CC = gcc
CFLAGS = -Wall -Wextra -lncursesw -ggdb

OBJ+=src/main.o
OBJ+=src/draw.o
OBJ+=src/input.o
OBJ+=src/curses.o
OBJ+=src/logo.o
OBJ+=src/version.o
OBJ+=src/config.o

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) -o $(PROGNAME) $(OBJ) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(PROGNAME) $(OBJ)
