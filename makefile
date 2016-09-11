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
	$(RM) $(FORCE) $(OBJECTS) $(EXECUTABLE) .depend

help:
	@echo "This is makefile command information:"
	@echo "==============================================="
	@echo "all = compile all the file."
	@echo "DEBUG = enable the debugger mode."
	@echo "clean = remove executable and object file."
	@echo "dep = output the compiling detail to .depend file."
	@echo "==============================================="
	@echo 'Just use "make (FLAG)" then pass argument to make command.'
	@echo ""
