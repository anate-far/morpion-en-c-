#ifndef MORPION_H
#define MORPION_H

#include<stdlib.h>
#include<stdio.h>

#include"chararray2D.h"
#include"tool.h"

typedef struct _morpion* morpion;
typedef struct _morpion S_morpion;

struct _morpion{
	chararray grid;
	char player; //'X' ou 'O'
	char status; //'X' si 'x' gagne ou 'O' si 'o' gagne. '?' si nul. '. sinon'
	int nb_empty;
};


morpion morpion_init(void);
void morpion_destroy(morpion* MM);
void morpion_display(morpion M); 
void morpion_play(morpion M);

#endif
