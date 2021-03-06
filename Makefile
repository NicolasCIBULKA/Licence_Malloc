all : test batch commandline interactive

test : test.o structures.o memory.o ipcTools.o
	gcc test.o structures.o memory.o ipcTools.o -o test 

batch : batch.o structures.o memory.o ipcTools.o
	gcc batch.o structures.o memory.o ipcTools.o -o batch

commandline : commandline.o structures.o memory.o ipcTools.o
	gcc commandline.o structures.o memory.o ipcTools.o -o commandline

interactive : interactive.o structures.o memory.o ipcTools.o
	gcc interactive.o structures.o memory.o ipcTools.o -o interactive

interactive.o : interactive.c ./utils/memory.h
	gcc -c interactive.c

commandline.o: commandline.c ./utils/memory.h
	gcc -c commandline.c

batch.o : batch.c ./utils/memory.h
	gcc -c batch.c

test.o: test.c ./utils/memory.h
	gcc -c test.c

memory.o: ./utils/memory.c ./utils/memory.h ./utils/structures.h ./utils/ipcTools.h
	gcc -c ./utils/memory.c 

ipcTools.o: ./utils/ipcTools.c ./utils/ipcTools.h
	gcc -c ./utils/ipcTools.c

structures.o: ./utils/structures.c ./utils/structures.h
	gcc -c ./utils/structures.c

clear :
	rm -f *.o test batch commandline interactive