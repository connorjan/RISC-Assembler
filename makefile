CC=g++
CFLAGS=-c -I/usr/local/Cellar/boost/1.55.0/include/boost -std=c++11
LDFLAGS=
SOURCES=Main.cpp Assembler.cpp File.cpp Exception.cpp SimpleInst.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=myAssembler

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) *.o *~