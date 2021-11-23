#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "chararray2D.h"
#include "tool.h"

//i = numero de collone et j numero de ligne
//x = numero de collone et y numero de ligne
//j = h et i = w 



//Fonction privé
//pour un char**
void chararray_alloc(chararray A, int w , int h)
{
	A->data = toolsMalloc(sizeof(char) * w * h);
	
	A->pixel = toolsMalloc(sizeof(char*) * h);

	int j;
	for(j = 0; j < h; j++)
		A->pixel[j] = A->data + j * A->w * sizeof(char);
}
//________________________________________________________

chararray chararray_create(int w , int h , char bg) 
{
	chararray A = toolsMalloc(sizeof(struct _chararray));
	A->w = w; A->h = h; A->bg = bg;
	chararray_alloc(A, w, h); //toolsMalloc(sizeof(char) * w * h); 
	chararray_fill(A, bg);
	return A; 
}

void chararray_destroy(chararray* AA)
{
	chararray A = *AA; 
	int j;

/*	for(j = 0; j < A->h; j++)
		toolsFree(A->data[j], sizeof(char) * A->w);
*/

	toolsFree(A->pixel, sizeof(char*) * A->h);
	toolsFree(A->data, sizeof(char)* A->w * A->h);
	toolsFree(A, sizeof(struct _chararray));

	*AA = NULL;
}



void chararray_debug(chararray A) 
{
	int j , i;
	char* ptr = A->data;

	for(j = 0; j < A->h ; j++)
	{
		for(i = 0; i < A->w; i++)
		{
			fprintf(stderr, " %c ", *ptr);
			ptr++;
		}

		fprintf(stderr, "\n");
	}
}

void chararray_fill(chararray A, char bg)
{
	int j , i ;
	char* ptr = A->data;	
	for(j = 0; j < A->h; j ++)
	{
		for(i = 0; i < A->w; i ++)
		{
			*ptr = bg; 
			ptr++; 
		}
	}

}

char chararray_get(chararray A, int x, int y)
{
	
	
	if((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h))
	{
		fprintf( stderr, "ERROR <chararray_get> : (%d;%d) is out of bounds.\n", x, y );
		return A->bg;
	}
	

	return A->pixel[y][x];
	//return A->data[y * A-> w + x];
}

void chararray_set(chararray A, int x, int y, char value)
{
	if((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h))
	{
		fprintf( stderr, "ERROR <chararray_set> : (%d;%d) is out of bounds.\n", x, y );
	}	

	//A->data[y][x] = value; 
	A->data[y * A->w +x] = value;
}


void chararray_copy_aux(chararray src, int sx1, int sy1,
		    chararray tar, int tx1, int ty1, int w, int h, int alpha)

{
	if(src == tar)
	{
		fprintf(stderr, "ERROR <charray_copy> : src and tar are the same chararray.\n");
		return;
	}

	int ex1 = sx1 + w - 1;
	int ey1 = sy1 + h - 1; 
	int_normalize_and_warn(&sx1, 0, src->w -1);
	int_normalize_and_warn(&sy1, 0, src->h -1);
	int_normalize_and_warn(&ex1, 0, src->w -1);
	int_normalize_and_warn(&ey1, 0, src->h -1);
	w = ex1 - sx1 + 1;
	h = ey1 - sy1 + 1;

	int x, y, xx, yy;
	int error = 0;
	for(y = 0; y < h; y++)
	{
		xx = tx1;
		yy = ty1 + y;

		for(x = 0; x < w ; x++)
		{
			if((xx >= 0) && (yy >= 0) && (xx < tar->w) && (yy < tar->h))
			{
				char c =  src->pixel[sy1 + y][sx1 +x];
				if((alpha == 1) && (c == src->bg))
					tar->pixel[yy][xx] = tar->bg;
				else 
					tar->pixel[yy][xx]  = c; 
			}
			else
				error = 1;
			xx++;		
		}

		if(error == 1)
			fprintf(stderr, "ERROR <chararray_copy> : out of bounds in target\n");
	}


}

void chararray_copy(chararray src, int sx1, int sy1, 
		    chararray tar, int tx1, int ty1, int w, int h)
{
	chararray_copy_aux(src, sx1,sy1, tar, tx1, ty1, w, h, 0);
}



void chararray_copy_alpha(chararray src, int sx1, int sy1,
		    chararray tar, int tx1, int ty1, int w, int h)
{
	chararray_copy_aux(src, sx1,sy1, tar, tx1, ty1, w, h, 1);
}

chararray chararray_crop(chararray A, int x1, int y1, int w, int h)
{
	chararray B = chararray_create(w, h, A->bg);
	chararray_copy(A, x1, y1, B, 0, 0, w, h);
	return B; 
}

chararray chararray_clone(chararray A)
{
	return chararray_crop(A, 0, 0,A->w, A->h);
}


void chararray_draw_hor_line(chararray A, int x1, int x2, int y, char bg)
{
	char* ptr = A->data + x1 + y * A->w;
	int x; 

	for (x = x1; x <= x2; x++)
	{
		*ptr = bg;
		ptr ++;
	}
}


void chararray_draw_ver_line(chararray A, int y1, int y2, int x, char bg)
{
	char* ptr = A->data + x + y1 * A->w;
      	int y; 
	for(y = y1; y <= y2; y++)
	{
		*ptr = bg; 
		ptr += A->w;
	}
}


void chararray_draw_empty_box(chararray A, int x1, int y1,
				int x2, int y2, char bg)
{
	chararray_draw_hor_line(A,x1,x2,y1, bg);
	chararray_draw_hor_line(A,x1,x2,y2, bg);

	chararray_draw_ver_line(A, y1, y2, x1, bg);
	chararray_draw_ver_line(A, y1, y2, x2, bg);
}


void chararray_draw_filled_box(chararray A, int x1, int y1,
				int x2, int y2, char bg)
{
	int x , y;

	for(y  = y1; y <= y2; y++)
	{
		char* ptr = A->data + x1 + y * A->w;
		for(x = x1; x <= x2; x++)
		{
			*ptr = bg;
			ptr ++; 
		}
	}	
}


void chararray_draw_disk(chararray A, int cx, int cy, float radius, char bg)
{
/*
	Pour calculer la distance entre A et B :
	racine carrée de (Xb -Xa) ^ 2 + (Ya - Yb) ^2.

	Pour savoir si un point (x, y) appartient au disque
	de centre (cx, cy) et de rayon r, il suffit de tester
	si la distance entre (x, y) et (cx, cy) est <= r. 	
       
*/

	int x1 = cx - radius -2;
	int x2 = cx + radius +2;
	int y1 = cy - radius -2;
	int y2 = cy + radius +2;
	int x,y;
	int r2 = radius * radius; 

	int_normalize(&x1, 0, A->w - 1);
	int_normalize(&x2, 0, A->w - 1);
	int_normalize(&y1, 0, A->h - 1);
	int_normalize(&y2, 0, A->h - 1);

	for(y = y1; y <= y2; y++)
	{
		char* ptr = A->data + x1 + y * A->w;
		for(x = x1; x <= x2; x++)
		{
			if((x - cx) * (x -cx) + (y - cy) * (y - cy) <= r2)
				*ptr = bg;
			ptr ++; 
		}	
	}

	


}


