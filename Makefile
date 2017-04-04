CC=gcc -std=c99
CFLAGS=-c -Wall -pedantic
LDFLAGS=-Ilib/
SOURCES=lib/stack.c antvm.c main.c
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o