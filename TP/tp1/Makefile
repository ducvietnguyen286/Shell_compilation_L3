all: main.o fonc.o
	cc main.o fonc.o -o main
main.o: main.c
	cc -c main.c
fonc.o: fonc.c
	cc -c fonc.c
clean:
	rm -rf *o main
