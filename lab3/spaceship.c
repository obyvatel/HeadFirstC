#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "constants.h"

// инициализация звездолета
void ship_init(Spaceship *ss)
{
	// ss - звездолет
	ss->sx = DISP_W/2;
	ss->sy = DISP_H/2; 
	ss->heading = 0;
	ss->speed = 0;
	ss->gone = 0;
	ss->color = al_map_rgb_f(0, 1, 0);
}

// инициализация звездолетов чтобы показать жизни
void ship_life_init(Spaceship *ss_l, int lifes)
{
	// ss_l - звездолет в шапке в виде жизней
	// lifes - количество жизней
	
	for (int i=0; i<lifes; i++)
	{
		ss_l->sx = i * 20 + 10;
		ss_l->sy = 35;
		ss_l->heading = 0;
		ss_l->speed = 0;
		ss_l->gone = 0;
		ss_l->color = al_map_rgb_f(0, 1, 0);
		
		ss_l++;	// следующий звездолет
	}
}
	
// прорисовка звездолета
void draw_ship(Spaceship* s)
{
	// s - звездолет
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, s->heading);
	al_translate_transform(&transform, s->sx, s->sy);
	al_use_transform(&transform);
	
	// координаты
	s->sx += (s->speed) * (sinf(s->heading));
	s->sy -= (s->speed) * (cosf(s->heading));
	
	// выход за пределы поля
	if (s->sx > DISP_W) s->sx = 0;
	if (s->sx < 0) s->sx = DISP_W;
	if (s->sy > DISP_H) s->sy = 0;
	if (s->sy < 0) s->sy = DISP_H;
	
	al_draw_line(-8,   9,  0, -11, s->color, 3.0f);
	al_draw_line( 0, -11,  8,   9, s->color, 3.0f);
	al_draw_line(-6,   4, -1,   4, s->color, 3.0f);
	al_draw_line( 6,   4,  1,   4, s->color, 3.0f);
}

// прорисовать жизни в шапке в виде звездолетов
void draw_ship_life(Spaceship *ss_life, int life)
{
	// ss_l - указатель на звездолет
	// life - количество жизней
	
	for (int i=0; i<life; i++)
	{
		draw_ship(ss_life);	// прорисовать жизни
		ss_life++;				// следующая структура
	}
}
