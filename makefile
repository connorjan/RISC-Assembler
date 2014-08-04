CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=Main.cpp Assembler.cpp File.cpp Exception.cpp SimpleInst.cpp AdvancedInst.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=myAssembler

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) *.o *~