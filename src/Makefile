SOURCES=main.c bullet.c game.c list.c network.c player.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=shmup

CC=gcc
LIBS=-lm -lGL -lglfw
CFLAGS=-c -std=c99
LDFLAGS=-g

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 
