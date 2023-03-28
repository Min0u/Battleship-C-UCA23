all : bataille_navale_blv2

bataille_navale_blv2 : main.c stdprof.o afficher.o grille.o action.o type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi stdprof.o afficher.o grille.o action.o main.c -o bataille_navale_blv2

stdprof.o : stdprof.c stdprof.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c stdprof.c

afficher.o : afficher.c afficher.h type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c afficher.c

grille.o : grille.c grille.h type.h
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c grille.c

action.o : action.c action.h grille.h type.h 
	gcc -Wall -pedantic -fsanitize=address -fsanitize=undefined -ansi -c action.c


