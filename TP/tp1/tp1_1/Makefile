all: main.o tris.o
	cc main.o tris.o -o main
main.o: main.c
	cc -c main.c
fonc.o: tris.c
	cc -c tris.c
clean:
	rm -rf *o main
