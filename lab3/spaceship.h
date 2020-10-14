//Защита от повторного включения файла
#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include <allegro5/allegro5.h>

// структура звездолета
typedef struct
{
	float sx;
	float sy;
	float heading;	// направление
	float speed;
	int gone;		// разбился
	ALLEGRO_COLOR color;
} Spaceship;

// инициализация звездолета
void ship_init(Spaceship *ss);

// инициализация звездолетов чтобы показать жизни
void ship_life_init(Spaceship *ss_l, int lifes);
	
// прорисовка звездолета
void draw_ship(Spaceship* s);

// прорисовать жизни в шапке в виде звездолетов
void draw_ship_life(Spaceship *ss_life, int life);

#endif