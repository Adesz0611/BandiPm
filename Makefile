CC = gcc
CFLAGS = -Wall -lncursesw -I.
PROGNAME = bandipm
all: $(PROGNAME)

OBJ+=src/main.o
OBJ+=src/init.o
OBJ+=src/draw.o
OBJ+=src/input.o

$(PROGNAME): $(OBJ)
	$(CC) -o $(PROGNAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(PROGNAME) src/*.o
