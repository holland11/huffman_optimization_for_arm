CC=gcc
CFLAGS=-c -O3

huffman_start: huffman_start.o huffman_debug.o huffman_coding.o huffman_tree.o huffman_utils.o
	$(CC) huffman_debug.o huffman_start.o huffman_coding.o huffman_tree.o huffman_utils.o -o huffman_start

huffman_start.o: huffman_start.c huffman_debug.h huffman_tree.h huffman_coding.h huffman_utils.h
	$(CC) $(CFLAGS) huffman_start.c
	
huffman_debug.o: huffman_debug.c huffman_debug.h huffman_tree.h
	$(CC) $(CFLAGS) huffman_debug.c
	
huffman_coding.o: huffman_coding.c huffman_coding.h huffman_tree.h
	$(CC) $(CFLAGS) huffman_coding.c
	
huffman_tree.o: huffman_tree.c huffman_tree.h
	$(CC) $(CFLAGS) huffman_tree.c

huffman_utils.o: huffman_utils.c huffman_utils.h
	$(CC) $(CFLAGS) huffman_utils.c
	
clean:
	rm *.o
	rm huffman_start