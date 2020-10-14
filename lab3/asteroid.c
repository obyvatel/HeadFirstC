#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"
#include "constants.h"
#include "blast.h"
#include "spaceship.h"

// инициализация астероидов
// т.к. астероиды удваиваются при попадании - 
// инициируем 1/4 всего массива астероидов
void asteroids_init(Asteroid *asteroid)
{
	// asteroid - первый элемент массива астероидов
	int Asteroids_N4 = Asteroids_N / 4;
	
	for (int i=0; i<Asteroids_N; i++)
	{
		if (i>Asteroids_N4)
		{
			asteroid->gone = 1;	// астероиды скрыть
		}
		else
		{
			asteroid->gone = 0;	// все астероиды целые, не уничтожены
			asteroid->color = al_map_rgb_f(0, 0, 1);
			asteroid->sx = (float)rand() / (float)RAND_MAX * DISP_W;
			asteroid->sy = (float)rand() / (float)RAND_MAX * DISP_H;
			asteroid->heading = (float)rand() / (float)RAND_MAX * 10;
			asteroid->speed = (float)rand() / (float)RAND_MAX * 5;
			asteroid->twist = (float)rand() / (float)RAND_MAX * 10;
			asteroid->rot_velocity = (float)rand() / (float)RAND_MAX * 0.1;
			asteroid->scale = 1;
		}
		
		asteroid++;			// следующая структура с астероиодом
	}
}

// проверка столкновения астероида и выстрела
bool collide_blast(Asteroid *as, Blast *bl)
{
	// as - одиночный астероид
	// bl - одиночный выстрел
	if (bl->gone) return false;
	if ( bl->sx > (as->sx + (20 * as->scale)) ) return false;
	if ( bl->sx < (as->sx - (25 * as->scale)) ) return false;
	if ( bl->sy > (as->sy + (20 * as->scale)) ) return false;
	if ( bl->sy < (as->sy - (20 * as->scale)) ) return false;
	
	return true;
}

// проверка столкновения астероида и звездолета
bool collide_ship(Asteroid *as, Spaceship *ss)
{
	// as - одиночный астероид
	// ss - звездолет
	if (as->gone) return false;
	if ( ss->sx - 8  > (as->sx + (20 * as->scale)) ) return false;
	if ( ss->sx + 8  < (as->sx - (25 * as->scale)) ) return false;
	if ( ss->sy - 11 > (as->sy + (20 * as->scale)) ) return false;
	if ( ss->sy + 9  < (as->sy - (20 * as->scale)) ) return false;
	
	return true;
}

// поведении астероида и выстрела после столкновения
void after_collide_blast(Asteroid *as, Asteroid *asteroid, Blast *bl)
{	
	// as - адрес заданного астероида в памяти
	// asteroid - адрес массива астероидов в памяти
	// bl - адрес выстрела в памяти

	// уничтожаем выстрел
	bl->gone = 1;
	
	// уменьшаем или уничтожаем астероид
	// уменьшить можно два раза, в третий раз уничтожается астероид
	if (as->scale > 0.3)
	{
		as->scale /= 2;	// уменьшит размер
		as->heading = bl->heading - 0.5;
		
		// создать вторую уменьшенную копию астероида
		for (int i=0; i<Asteroids_N; i++)
		{
			if (asteroid->gone)
			{
				asteroid->gone = 0;
				asteroid->color = al_map_rgb_f(0, 0, 1);
				asteroid->sx = as->sx;
				asteroid->sy = as->sy;
				asteroid->heading = bl->heading + 0.5;
				asteroid->speed = as->speed;
				asteroid->twist = as->twist;
				asteroid->rot_velocity = as->rot_velocity;
				asteroid->scale = as->scale;
				
				break;
			}
			
			asteroid++;	// следующая структура с астероидлом
		}
	}
	else
		as->gone = 1;
}

// поведение после столкновения астероида и звездолета
void after_collide_ship(Spaceship *ss)
{
	// ss - звездолет
	
	// вернуть звездолет в центр экрана
	ss->sx = DISP_W/2;
	ss->sy = DISP_H/2;
}

// проверить на столкновения астероиды и выстрелы
void check_collide_asteroid_blast(Asteroid *asteroid, Blast *blast, int *score_count)
{
	// asteroid - первая структура массива астероидов
	// blast - первая структура массива выстрелов
	// score_count - счет игрока
	
	Asteroid *keep_start_asteroid = asteroid;	// сохранить начало массива астероидов
	
	Blast* store_start = blast;
	for (int i=0; i<Asteroids_N; i++)
	{
		blast = store_start;
		
		for (int j=0; j<Blasts_N; j++)
		{
			if (collide_blast(asteroid, blast))
			{	// если произошло столкновение с выстрелом
				*score_count += 100;		// обновляем счет
				after_collide_blast(asteroid, keep_start_asteroid, blast);
			}
			blast++;	// следующая структура с выстрелом
		}
		
		asteroid++;
	}
}

// проверить на столкновения звездолет и астреоиды
void check_collide_ship_asteroid(Spaceship *ship, Asteroid *asteroid, int *life_count)
{
	// ship - звездолет
	// asteroid - первая структура массива астероидов
	// life_count - счетчик жизней
	
	for (int i=0; i<Asteroids_N; i++)
	{
		if (collide_ship(asteroid, ship))
		{
			*life_count -= 1;		// уменьшить количество жизней
			after_collide_ship(ship);
		}
		
		asteroid++;	// следующая структура с астероидом
	}
}

// прорисовка астероидов
void draw_asteroids(Asteroid *asteroid)
{
	// asteroid - первая структура массива астероидов
	
	for (int i=0; i<Asteroids_N; i++)
	{
		if (!asteroid->gone)
		{
			ALLEGRO_TRANSFORM transform;
			al_identity_transform(&transform);
			al_rotate_transform(&transform, asteroid->twist);
			al_translate_transform(&transform, asteroid->sx, asteroid->sy);
			//al_scale_transform(&transform, asteroid->scale, asteroid->scale);
			al_use_transform(&transform);

			// координаты
			asteroid->sx += (asteroid->speed) * (sinf(asteroid->heading));
			asteroid->sy -= (asteroid->speed) * (cosf(asteroid->heading));
			
			// вращение
			asteroid->twist += asteroid->rot_velocity;
			
			// выход за пределы поля
			if (asteroid->sx > DISP_W)
				asteroid->sx = 0;
			if (asteroid->sx < 0)
				asteroid->sx = DISP_W;
			if (asteroid->sy > DISP_H)
				asteroid->sy = 0;
			if (asteroid->sy < 0)
				asteroid->sy = DISP_H;
			
			float scale = asteroid->scale;
			
			al_draw_line(-20*scale,  20*scale, -25*scale,   5*scale, asteroid->color, 2.0f);
			al_draw_line(-25*scale,   5*scale, -25*scale, -10*scale, asteroid->color, 2.0f);
			al_draw_line(-25*scale, -10*scale,  -5*scale, -10*scale, asteroid->color, 2.0f);
			al_draw_line( -5*scale, -10*scale, -10*scale, -20*scale, asteroid->color, 2.0f);
			al_draw_line(-10*scale, -20*scale,   5*scale, -20*scale, asteroid->color, 2.0f);
			al_draw_line(  5*scale, -20*scale,  20*scale, -10*scale, asteroid->color, 2.0f);
			al_draw_line( 20*scale, -10*scale,  20*scale,  -5*scale, asteroid->color, 2.0f);
			al_draw_line( 20*scale,  -5*scale,   0*scale,   0*scale, asteroid->color, 2.0f);
			al_draw_line(  0*scale,   0*scale,  20*scale,  10*scale, asteroid->color, 2.0f);
			al_draw_line( 20*scale,  10*scale,  10*scale,  20*scale, asteroid->color, 2.0f);
			al_draw_line( 10*scale,  20*scale,   0*scale,  15*scale, asteroid->color, 2.0f);
			al_draw_line(  0*scale,  15*scale, -20*scale,  20*scale, asteroid->color, 2.0f);
		}
		
		asteroid++;	// слеудющая структура с асетроидом
	}
}