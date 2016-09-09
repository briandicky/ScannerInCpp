CC = g++
CFLAGS = -c -Wall -O2
CXXFLAGS = $(CFLAGS)
RM = rm
FORCE = -f
LDFLAGS =
SOURCES = main.cpp lexer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = lexer

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) $< -o $@

dep:
	$(CC) -M *.cpp > .depend

clean:
	$(RM) $(FORCE) $(OBJECTS) $(EXECUTABLE) 
