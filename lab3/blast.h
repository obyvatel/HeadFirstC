//Защита от повторного включения файла
#ifndef BLAST_H_INCLUDED
#define BLAST_H_INCLUDED

#include <allegro5/allegro5.h>
#include "spaceship.h"

// константы для выстрелов
#define Blasts_N 128	// макс количество выстрелов 
						// одновременно присутствующих на экране

// структура для выстрелов
typedef struct
{
	float sx;
	float sy;
	float heading;	// направление
	float speed;
	int gone;		// попал/аут
	ALLEGRO_COLOR color;
} Blast;

// инициализация выстрелов
void blasts_init(Blast *blast);

// создание выстрела
bool blasts_add(Spaceship *ss, Blast *blast);

// прорисовка выстрелов
void draw_blasts(Blast *blast);

#endif