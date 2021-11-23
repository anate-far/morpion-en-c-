prog : morpion.o tool.o chararray2D.o
	gcc -o morpion morpion.o tool.o chararray2D.o

morpion.o : morpion.c morpion.h tool.h chararray2D.h
	gcc -c morpion.c

tool.o : tool.c tool.h
	gcc -c tool.c

chararray2D.o : chararray2D.c chararray2D.h tool.h
	gcc -c chararray2D.c
