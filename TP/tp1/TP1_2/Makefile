all: main.o trie.o
	cc main.o trie.o -o main
main.o: main.c
	cc -c main.c
fonc.o: trie.c
	cc -c trie.c
clean:
	rm -rf *o main
