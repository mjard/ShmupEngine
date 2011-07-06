SOURCES=$(shell find . -type f -name "*.c")
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=shmup

CC=gcc
LIBS=-lm -lglfw -lenet
LDFLAGS=-g
CFLAGS=-c -std=c99

UNAME_S=$(shell uname)

ifeq ($(UNAME_S), Linux)
LIBS += -lGL
endif

ifeq ($(UNAME_S), Darwin)
CC=clang
LDFLAGS += -framework OpenGL -framework Cocoa
endif

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 
