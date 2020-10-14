#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "blast.h"
#include "constants.h"
#include "spaceship.h"

// инициализация выстрелов
void blasts_init(Blast *blast)
{
	// blast - первая структура массива выстрелов
	
    for(int i = 0; i < Blasts_N; i++)
	{
        blast->gone = 1;						// все выстрелы в ауте (скрыты)
		blast->color = al_map_rgb_f(1, 0, 0);	// цвет выстрела красный
		
		blast++;								// следующая структура с выстрелом
	}
}

// создание выстрела
bool blasts_add(Spaceship *ss, Blast *blast)
{
	// ss - звездолет
	// blast - первая структура массива выстрелов
	
    for(int i = 0; i < Blasts_N; i++)
    {
		// если выстрел отображается на экране - пропустить
        if (blast->gone == 0)
		{
			blast++;	// следующая структура
            continue;
		}

        blast->sx = ss->sx;
		blast->sy = ss->sy;
		blast->heading = ss->heading;
		blast->speed = 1 + (3 * ss->speed);
		blast->gone = 0;	// выстрел не в ауте

        return true;
    }
	
	return false;
}

// прорисовка выстрелов
void draw_blasts(Blast *blast)
{
	// blast - первая структура массива выстрелов
	
	for(int i=0; i<Blasts_N; i++)
	{
		// если выстрел не отображается на экране - пропускаем
		if (blast->gone > 0)
		{
			blast++;	// следующая структура с выстрелом
			continue;	// переход на следующую итерацию
		}

		ALLEGRO_TRANSFORM transform;
		al_identity_transform(&transform);
		al_rotate_transform(&transform, blast->heading);
		al_translate_transform(&transform, blast->sx, blast->sy);
		al_use_transform(&transform);
		
		// новые координаты выстрела
		blast->sx += (blast->speed) * (sinf(blast->heading));
		blast->sy -= (blast->speed) * (cosf(blast->heading));
		
		// проверка выхода за границы экрана
		if (
				(blast->sx < 0) ||
				(blast->sx > DISP_W) ||
				(blast->sy < 0) ||
				(blast->sy > DISP_H)
			)
			blast->gone = 1;
		
		// отрисовка
		al_draw_line(0, 0,  0, 10, blast->color, 2.0f);
		
		blast++;		// следующая структура с выстрелом
	}
}
