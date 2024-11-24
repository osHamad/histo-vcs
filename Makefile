OBJ = init.o help.o commit.o main.o structures.o

histo: $(OBJ)
	gcc -o histo $(OBJ)

main.o: main.c commands/cmds.h
	gcc -c main.c

structures.o: structures.c structures.h 
	gcc -c structures.c

commit.o: commands/commit.c defscmd.h structures.h
	gcc -c commands/commit.c

init.o: commands/init.c defscmd.h structures.h
	gcc -c commands/init.c

help.o: commands/help.c defscmd.h 
	gcc -c commands/help.c

clean:
	rm -f histo *.o

run:
	./histo
