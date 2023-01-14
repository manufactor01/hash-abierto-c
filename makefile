CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes
EXEC = pruebas
OBJFILES = lista.o hash.o main.o pruebas_catedra.o testing.o
%.o: %.c %.h 
	$(CC) $(CFLAGS) -c $<
$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(EXEC)
all: $(EXEC)
clear:
	clear
run: all clear
	./$(EXEC)
valgrind: all clear
	valgrind $(VFLAGS) ./$(EXEC)
free: $(EXEC) $(OBJFILES) valgrind
	rm -f $(EXEC) $(OBJFILES)
gdb: all clear
	gdb -tui ./$(EXEC)