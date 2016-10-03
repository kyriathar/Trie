OBJS	= main.o edges_nodes.o trie.o frequency.o rest_functions.o
SOURCE 	= main.c edges_nodes.c trie.c frequency.c rest_functions.c
HEADER	= errors.h edges_nodes.h trie.h frequency.h rest_functions.h
OUT	= exe
CC	= gcc
FLAG	= -c


all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAG) main.c

edges_nodes.o: edges_nodes.c
	$(CC) $(FLAG) edges_nodes.c

trie.o: trie.c
	$(CC) $(FLAG) trie.c

frequency.o: frequency.c
	$(CC) $(FLAG) frequency.c

rest_functions.o: rest_functions.c
	$(CC) $(FLAG) rest_functions.c


clean:
	rm -f $(OBJS) $(OUT)
