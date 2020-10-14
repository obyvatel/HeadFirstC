//Защита от повторного включения файла
#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <allegro5/allegro5.h>
#include "blast.h"
#include "spaceship.h"

// структура и константы для астероидов
typedef struct
{
	float sx;		// координата Х
	float sy;		// координата У
	float heading;	// направление перемещения
	float speed;	// скорость перемещения
	float twist;	// положения вращения
	float rot_velocity;	// вращенние за один кадр
	float scale;	// коэффициент масштабирования
	int gone;		// уничтожен
	ALLEGRO_COLOR color;
} Asteroid;

// максимальное количество астероидов одновременно присутствующих на экране
#define Asteroids_N 50

// инициализация астероидов
// т.к. астероиды удваиваются при попадании - 
// инициируем 1/4 всего массива астероидов
void asteroids_init(Asteroid *asteroid);

// проверка столкновения астероида и выстрела
bool collide_blast(Asteroid *as, Blast *bl);

// проверка столкновения астероида и звездолета
bool collide_ship(Asteroid *as, Spaceship *ss);

// поведении астероида и выстрела после столкновения
void after_collide_blast(Asteroid *as, Asteroid *asteroid, Blast *bl);

// поведение после столкновения астероида и звездолета
void after_collide_ship(Spaceship *ss);

// проверить на столкновения астероиды и выстрелы
void check_collide_asteroid_blast(Asteroid *asteroid, Blast *blast, int *score_count);

// проверить на столкновения звездолет и астреоиды
void check_collide_ship_asteroid(Spaceship *ship, Asteroid *asteroid, int *life_count);

// прорисовка астероидов
void draw_asteroids(Asteroid *asteroid);

#endif