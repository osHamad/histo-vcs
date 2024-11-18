OBJ = main.o commands.o

histo: $(OBJ) defs.h
	gcc -o histo $(OBJ) defs.h

main.o: main.c defs.h
	gcc -c main.c

commands.o: commands.c defs.h
	gcc -c commands.c

clean:
	rm -f histo *.o

run:
	./histo
