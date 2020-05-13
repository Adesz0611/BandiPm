PROGNAME = bandipm
CC = gcc
CFLAGS = -Wall -Wextra -lncursesw

OBJ+=src/main.o
OBJ+=src/init.o
OBJ+=src/draw.o
OBJ+=src/input.o
OBJ+=src/curses.o
OBJ+=src/logo.o

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) -o $(PROGNAME) $(OBJ) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(PROGNAME) $(OBJ)
