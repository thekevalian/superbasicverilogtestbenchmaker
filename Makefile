PROJECT = verilogTestBench
CC = g++
CFLAGS = -g
FILES = $(wildcard *.cpp)

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(CFLAGS)

debug: $(PROJECT)
	gdb $(PROJECT)

clean:
	rm -rf $(PROJECT)

