PROJECT = verilogTestBench
CC = g++
CFLAGS = -ggdb
LIBS = 
FILES = $(wildcard *.cpp)
EXTRADELETE = tb_ANDOR.v tb_ANDOR1.v

$(PROJECT): $(FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

debug: $(PROJECT)
	gdb $(PROJECT)

clean:
	rm -rf $(PROJECT) $(EXTRADELETE)


test: $(PROJECT)
	./$(PROJECT) ANDOR 2 2 0 0001 0111
	mv tb_ANDOR.v tb_ANDOR1.v
	./$(PROJECT) ANDOR 2 2 1 -o 3 -o 1 2 3
	diff tb_ANDOR.v tb_ANDOR1.v
