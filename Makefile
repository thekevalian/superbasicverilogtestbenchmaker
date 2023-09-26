PROJECT = verilogTestBench
CC = g++
CFLAGS = -g
LIBS =   #place your path to boost here
FILES = $(wildcard *.cpp)
EXTRADELETE = tb_ANDOR.v

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(CFLAGS)

debug: $(PROJECT)
	gdb $(PROJECT)

clean:
	rm -rf $(PROJECT) $(EXTRADELETE)


sample: $(PROJECT)
	./$(PROJECT) ANDOR 2 2 0 0001 0111
