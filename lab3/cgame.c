#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// общие переменные и константы
#define MAX_LIFE 3
int life = MAX_LIFE;	// жизней
int score = 0;			// счет игрока

// константы размеров дисплея
#define DISP_W 640
#define DISP_H 480

// структура и переменные звездолета
typedef struct
{
	float sx;
	float sy;
	float heading;	// направление
	float speed;
	int gone;		// разбился
	ALLEGRO_COLOR color;
} Spaceship;
Spaceship ss;
Spaceship ss_l[MAX_LIFE];

// структура, константы и переменные для выстрелов
typedef struct
{
	float sx;
	float sy;
	float heading;	// направление
	float speed;
	int gone;		// попал/аут
	ALLEGRO_COLOR color;
} Blast;

#define Blasts_N 128
Blast blasts[Blasts_N];

// структура, константы и переменные для астероидов
typedef struct
{
	float sx;
	float sy;
	float heading;	// направление перемещения
	float speed;	// скорость перемещения
	float twist;	// положения вращения
	float rot_velocity;	// вращенние за один кадр
	float scale;	// коэффициент масштабирования
	int gone;		// уничтожен
	ALLEGRO_COLOR color;
} Asteroid;

#define Asteroids_N 50
Asteroid asteroids[Asteroids_N];

// обработка ошибок инициализации
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

// прорисовка заголовка
void draw_header(ALLEGRO_FONT* font)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, 0);
	al_translate_transform(&transform, 0, 0);
	al_use_transform(&transform);
	
	// счет
	al_draw_textf(font, al_map_rgb(255, 255, 255), 0,  0, 0, "Score: %i", score);
	//al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 10, 0, "blasts[0].sx: %.1f", blasts[0].sx);
	
}

// ---------------------- Функции для звездолетов. Начало. -----------------------------
// инициализация звездолета
void ship_init()
{
	// звездолет
	ss.sx = DISP_W/2;
	ss.sy = DISP_H/2; 
	ss.heading = 0;
	ss.speed = 0;
	ss.gone = 0;
	ss.color = al_map_rgb_f(0, 1, 0);
	
	// жизни в звездолетах
	for (int i=0; i<MAX_LIFE; i++)
	{
		ss_l[i].sx = i * 20 + 10;
		ss_l[i].sy = 35;
		ss_l[i].heading = 0;
		ss_l[i].speed = 0;
		ss_l[i].gone = 0;
		ss_l[i].color = al_map_rgb_f(0, 1, 0);	
	}
}

// прорисовка звездолета
void draw_ship(Spaceship* s)
{
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

// жизней в звездолетах
void draw_ship_life()
{
	for (int i=0; i<life; i++)
	{
		draw_ship(&ss_l[i]);
	}
}
// ---------------------- Функции для звездолетов. Конец. ------------------------------

// ---------------------- Функции для выстрелов. Начало. -------------------------------
// инициализация выстрелов
void blasts_init()
{
    for(int i = 0; i < Blasts_N; i++)
	{
        blasts[i].gone = 1;	// все выстрелы в ауте
		blasts[i].color = al_map_rgb_f(1, 0, 0);
	}
}

// создание выстрела
bool blasts_add(Spaceship *ss)
{
    for(int i = 0; i < Blasts_N; i++)
    {
        if (blasts[i].gone == 0)
            continue;

        blasts[i].sx = ss->sx;
		blasts[i].sy = ss->sy;
		blasts[i].heading = ss->heading;
		blasts[i].speed = 1 + (3 * ss->speed);
		blasts[i].gone = 0;	// выстрел не в ауте

        return true;
    }
	
	return false;
}

// прорисовка выстрелов
void draw_blasts()
{
	for(int i=0; i<Blasts_N; i++)
	{
		if (blasts[i].gone > 0)
			continue;

		ALLEGRO_TRANSFORM transform;
		al_identity_transform(&transform);
		al_rotate_transform(&transform, blasts[i].heading);
		al_translate_transform(&transform, blasts[i].sx, blasts[i].sy);
		al_use_transform(&transform);
		
		// новые координаты выстрела
		blasts[i].sx += (blasts[i].speed) * (sinf(blasts[i].heading));
		blasts[i].sy -= (blasts[i].speed) * (cosf(blasts[i].heading));
		
		// проверка выхода за границы экрана
		if (
				(blasts[i].sx < 0) ||
				(blasts[i].sx > DISP_W) ||
				(blasts[i].sy < 0) ||
				(blasts[i].sy > DISP_H)
			)
			blasts[i].gone = 1;
		
		// отрисовка
		al_draw_line(0, 0,  0, 10, blasts[i].color, 2.0f);
	}
}
// ---------------------- Функции для выстрелов. Конец. --------------------------------

// ---------------------- Функции для астероидов. Начало. ------------------------------
void asteroids_init()
{
	for (int k=0; k<Asteroids_N; k++)
		asteroids[k].gone = 1;	// все астероиды уничтожены
	
	int Asteroids_N4 = Asteroids_N / 4;
	for (int i=0; i<Asteroids_N4; i++)
	{
		asteroids[i].gone = 0;	// все астероиды целые, не уничтожены
		asteroids[i].color = al_map_rgb_f(0, 0, 1);
		asteroids[i].sx = (float)rand() / (float)RAND_MAX * DISP_W;
		asteroids[i].sy = (float)rand() / (float)RAND_MAX * DISP_H;
		asteroids[i].heading = (float)rand() / (float)RAND_MAX * 10;
		asteroids[i].speed = (float)rand() / (float)RAND_MAX * 5;
		asteroids[i].twist = (float)rand() / (float)RAND_MAX * 10;
		asteroids[i].rot_velocity = (float)rand() / (float)RAND_MAX * 0.1;
		asteroids[i].scale = 1;
	}
}

// проверка столкновения астероида и выстрела
bool collide_blast(Asteroid *as, Blast *bl)
{
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
	if ( ss->sx - 8  > (as->sx + (20 * as->scale)) ) return false;
	if ( ss->sx + 8  < (as->sx - (25 * as->scale)) ) return false;
	if ( ss->sy - 11 > (as->sy + (20 * as->scale)) ) return false;
	if ( ss->sy + 9  < (as->sy - (20 * as->scale)) ) return false;
	
	return true;
}

// поведении астероида и выстрела после столкновения
void after_collide_blast(Asteroid *as, Blast *bl)
{
	// обновляем счет
	score += 100;
	
	// уничтожаем выстрел
	bl->gone = 1;
	
	// уменьшаем или уничтожаем астероид
	// уменьшить можно два раза, в третий раз уничтожается астероид
	if (as->scale > 0.3)
	{
		as->scale /= 2;	// уменьшит размер
		as->heading = bl->heading - 0.5;
		// создать вторую половину астероида
		for (int i=0; i<Asteroids_N; i++)
		{
			if (asteroids[i].gone)
			{
				asteroids[i].gone = 0;
				asteroids[i].color = al_map_rgb_f(0, 0, 1);
				asteroids[i].sx = as->sx;
				asteroids[i].sy = as->sy;
				asteroids[i].heading = bl->heading + 0.5;
				asteroids[i].speed = as->speed;
				asteroids[i].twist = as->twist;
				asteroids[i].rot_velocity = as->rot_velocity;
				asteroids[i].scale = as->scale;
				
				break;
			}
		}
	}
	else
		as->gone = 1;
}

// поведение после столкновения астероида и звездолета
void after_collide_ship(Spaceship *ss)
{
	// уменьшить количество жизней
	life--;
	ss->sx = DISP_W/2;
	ss->sy = DISP_H/2;
}

// прорисовка астероидов
void draw_asteroids()
{
	for (int i=0; i<Asteroids_N; i++)
	{
		if (!asteroids[i].gone)
		{
			ALLEGRO_TRANSFORM transform;
			al_identity_transform(&transform);
			al_rotate_transform(&transform, asteroids[i].twist);
			al_translate_transform(&transform, asteroids[i].sx, asteroids[i].sy);
			//al_scale_transform(&transform, asteroids[i].scale, asteroids[i].scale);
			al_use_transform(&transform);

			// координаты
			asteroids[i].sx += (asteroids[i].speed) * (sinf(asteroids[i].heading));
			asteroids[i].sy -= (asteroids[i].speed) * (cosf(asteroids[i].heading));
			
			// вращение
			asteroids[i].twist += asteroids[i].rot_velocity;
			
			// выход за пределы поля
			if (asteroids[i].sx > DISP_W)
				asteroids[i].sx = 0;
			if (asteroids[i].sx < 0)
				asteroids[i].sx = DISP_W;
			if (asteroids[i].sy > DISP_H)
				asteroids[i].sy = 0;
			if (asteroids[i].sy < 0)
				asteroids[i].sy = DISP_H;
			
			// проверка на столкновение с выстрелом
			for (int j=0; j<Blasts_N; j++)
				if (collide_blast(&asteroids[i], &blasts[j]))
				{	// если произошло столкновение с выстрелом
					after_collide_blast(&asteroids[i], &blasts[j]);
				}
			
			// проверка на столкновение с звездолетом
			if (collide_ship(&asteroids[i], &ss))
			{
				after_collide_ship(&ss);
			}
			
			float scale = asteroids[i].scale;
			
			al_draw_line(-20*scale,  20*scale, -25*scale,   5*scale, asteroids[i].color, 2.0f);
			al_draw_line(-25*scale,   5*scale, -25*scale, -10*scale, asteroids[i].color, 2.0f);
			al_draw_line(-25*scale, -10*scale,  -5*scale, -10*scale, asteroids[i].color, 2.0f);
			al_draw_line( -5*scale, -10*scale, -10*scale, -20*scale, asteroids[i].color, 2.0f);
			al_draw_line(-10*scale, -20*scale,   5*scale, -20*scale, asteroids[i].color, 2.0f);
			al_draw_line(  5*scale, -20*scale,  20*scale, -10*scale, asteroids[i].color, 2.0f);
			al_draw_line( 20*scale, -10*scale,  20*scale,  -5*scale, asteroids[i].color, 2.0f);
			al_draw_line( 20*scale,  -5*scale,   0*scale,   0*scale, asteroids[i].color, 2.0f);
			al_draw_line(  0*scale,   0*scale,  20*scale,  10*scale, asteroids[i].color, 2.0f);
			al_draw_line( 20*scale,  10*scale,  10*scale,  20*scale, asteroids[i].color, 2.0f);
			al_draw_line( 10*scale,  20*scale,   0*scale,  15*scale, asteroids[i].color, 2.0f);
			al_draw_line(  0*scale,  15*scale, -20*scale,  20*scale, asteroids[i].color, 2.0f);
		}
	}
}
// ---------------------- Функции для астероидов. Конец. -------------------------------

int main()
{
	// инициализация
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");	

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
	
	// звездолет
	ship_init();

	// выстрелы
	blasts_init();
	
	// астероид
	asteroids_init();
	
	// подготовка обработки нажатий клавиш
    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
			// обработка событий таймера
            case ALLEGRO_EVENT_TIMER:
				// клавиатура
                if(key[ALLEGRO_KEY_UP])
					if (ss.speed < 20)
						ss.speed += 1;
                if(key[ALLEGRO_KEY_DOWN])
					if (ss.speed > 0)
						ss.speed -= 1;
                if(key[ALLEGRO_KEY_LEFT])
					ss.heading -= 0.1;
                if(key[ALLEGRO_KEY_RIGHT])
					ss.heading += 0.1;
				if (key[ALLEGRO_KEY_SPACE])
					blasts_add(&ss);	// тут создать выстрелы

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;
				
				// перерисовать экран
                redraw = true;
                break;
			
			// обработка нажатий клавиш
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
			
			// нажатин на кнопку "закрыть" (крестик)
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

			draw_header(font);	// прорисовка заголовка
			draw_ship_life();	// прорисовка жизней
			
			if (life > 0)
			{
				draw_ship(&ss);		// прорисовка звездолета
				draw_blasts();		// прорисовкка выстрелов
				draw_asteroids();	// прорисовка астероидов
			}
			else
				al_draw_textf(font, al_map_rgb(255, 255, 255), DISP_W/2, DISP_H/2, ALLEGRO_ALIGN_CENTRE, "G A M E  O V E R");
			
            al_flip_display();

            redraw = false;
        }
    }

	// уничтожение
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}