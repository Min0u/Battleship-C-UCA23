all : bataille_navale_b1

bataille_navale_b1 : main.c stdprof.o afficher.o grille.o action.o jeu.o type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi stdprof.o jeu.o afficher.o grille.o action.o main.c -o bataille_navale_b1

stdprof.o : stdprof.c stdprof.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c stdprof.c

afficher.o : afficher.c afficher.h type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c afficher.c

grille.o : grille.c grille.h type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c grille.c

action.o : action.c action.h grille.h type.h 
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c action.c

jeu.o : jeu.c jeu.h grille.h afficher.h action.h type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c jeu.c
