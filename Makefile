PROJECT = verilogTestBench
CC = g++
CFLAGS = -g
LIBS =   #place your path to boost here
FILES = $(wildcard *.cpp)

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(CFLAGS)

debug: $(PROJECT)
	gdb $(PROJECT)

clean:
	rm -rf $(PROJECT)

sample: $(PROJECT)
	./$(PROJECT) ANDOR.v 2 2 0 0001 0111
