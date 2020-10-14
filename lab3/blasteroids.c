#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "constants.h"
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"

// общие переменные и константы
#define MAX_LIFE 3
int life = MAX_LIFE;	// жизней
int score = 0;			// счет игрока

// Переменные звездолета
Spaceship ss;				// звездолет
Spaceship ss_l[MAX_LIFE];	// количество жизней

// массив выстрелов
Blast blasts[Blasts_N];	

// массив астероидов
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
	ship_init(&ss);	// боевой звездолет
	ship_life_init(&ss_l[0], MAX_LIFE);	// жизни в шапке

	// выстрелы
	blasts_init(&blasts[0]);
	
	// астероид
	asteroids_init(&asteroids[0]);
	
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
					blasts_add(&ss, &blasts[0]);	// тут создать выстрелы

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
			// черный фон
            al_clear_to_color(al_map_rgb(0, 0, 0));

			// шапка
			draw_header(font);	// прорисовка заголовка
			draw_ship_life(&ss_l[0], life);	// прорисовка жизней
			
			// игровой сценарий
			if (life > 0)
			{	// если звездолет живой
				draw_ship(&ss);					// прорисовка звездолета
				draw_blasts(&blasts[0]);		// прорисовкка выстрелов
				draw_asteroids(&asteroids[0]);	// прорисовка астероидов
				// проверить на столкновения астероиды и выстрелы
				check_collide_asteroid_blast(&asteroids[0], &blasts[0], &score);
				// проверить на столкновения звездолет и астреоиды
				check_collide_ship_asteroid(&ss, &asteroids[0], &life);
			}
			else
				// если жизни кончились - вывести "game over"
				al_draw_textf(font, al_map_rgb(255, 255, 255), DISP_W/2, DISP_H/2, 
												ALLEGRO_ALIGN_CENTRE, "G A M E  O V E R");
			
			// обновить экран
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