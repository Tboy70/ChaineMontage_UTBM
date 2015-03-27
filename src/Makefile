projet: anneau.o file_entree.o file_sortie.o robot1.o robot2.o robot3.o robot4.o robot5.o robot6.o main.o
	gcc -o projet anneau.o file_entree.o file_sortie.o robot1.o robot2.o robot3.o robot4.o robot5.o robot6.o main.o -lpthread

anneau.o: anneau.c
	gcc -o anneau.o -c anneau.c 

file_entree.o: file_entree.c
	gcc -o file_entree.o -c file_entree.c

file_sortie.o: file_sortie.c
	gcc -o file_sortie.o -c file_sortie.c

robot1.o: robot1.c
	gcc -o robot1.o -c robot1.c

robot2.o: robot2.c
	gcc -o robot2.o -c robot2.c

robot3.o: robot3.c
	gcc -o robot3.o -c robot3.c

robot4.o: robot4.c
	gcc -o robot4.o -c robot4.c

robot5.o: robot5.c
	gcc -o robot5.o -c robot5.c

robot6.o: robot6.c
	gcc -o robot6.o -c robot6.c

main.o: main.c main.h
	gcc -o main.o -c main.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf hello