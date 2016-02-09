par-shell: commandlinereader.o list.o par-shellCommands.o par-shell.o
	gcc -pthread -o par-shell commandlinereader.o list.o par-shellCommands.o par-shell.o

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc -Wall -g -c commandlinereader.c

list.o: list.c list.h
	gcc -Wall -g -c list.c

par-shellCommands.o: par-shellCommands.c par-shellCommands.h
	gcc -pthread -Wall -g -c par-shellCommands.c

par-shell.o: par-shell.c commandlinereader.h
	gcc -pthread -Wall -g -c par-shell.c
