CC=gcc
CFLAGS=-Wall
LDFLAGS=
SOURCES=minimat.c parser.c vector_array.c vector_math.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=minimat
all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) -MM $< > $*.d
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d