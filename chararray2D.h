#ifndef CHARARRAY_H
#define CHARARRAY_H

#include <stdlib.h>
#include <stdio.h>

#include "tool.h"

//i = numero de collone et j numero de ligne
//x = numero de collone et y numero de ligne 

typedef struct _chararray* chararray;
typedef struct _chararray S_chararray;

struct _chararray
{
	int w;//width 
	int h;//height
	char* data;
	char** pixel; 
	char bg; 

};

chararray chararray_create(int w , int h , char bg); //bg = background
void chararray_destroy(chararray* A);

void chararray_debug(chararray A);
void chararray_fill(chararray A, char bg);
char chararray_get(chararray A, int x, int y);
void chararray_set(chararray a, int x, int y, char value);


//src et tar doivent etre deux chararray différendte 
void chararray_copy(chararray src, int sx1, int sy1,
		    chararray tar, int tx1, int ty1, int w, int h);

void chararray_copy_alpha(chararray src, int sx1, int sy1,
		    chararray tar, int tx1, int ty1, int w, int h);
chararray chararray_crop(chararray A, int x1, int y1, int w, int h);
chararray chararray_clone(chararray A);


//Primitive

void chararray_draw_hor_line(chararray A, int x1, int x2, int y, char bg);
void chararray_draw_ver_line(chararray A, int y1, int y2, int x, char bg);

void chararray_draw_empty_box(chararray A, int x1, int y1,
				int x2, int y2, char bg);
void chararray_draw_filled_box(chararray A, int x1, int y1,
				int x2, int y2, char bg);

void chararray_draw_disk(chararray A, int cx, int cy, float radius, char bg);

#endif
