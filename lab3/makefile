#флаги
CFLAGS = -Wall -Wextra -g

all: blasteroids
blasteroids.o: blasteroids.c constants.h spaceship.h blast.h asteroid.h
	gcc.exe -c blasteroids.c
constants.o: constants.c constants.h
	gcc.exe -c constants.c
spaceship.o: spaceship.c spaceship.h constants.h
	gcc.exe -c spaceship.c
blast.o: blast.c blast.h spaceship.h
	gcc.exe -c blast.c
asteroid.o: asteroid.c asteroid.h blast.h spaceship.h
	gcc.exe -c asteroid.c
blasteroids: blasteroids.o constants.o spaceship.o blast.o asteroid.o
	gcc.exe $(CFLAGS) blasteroids.o constants.o spaceship.o blast.o asteroid.o -o blasteroids -lallegro -lallegro_font -lallegro_primitives

clean:
	rm -rf *.o