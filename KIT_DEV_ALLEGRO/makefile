PASTINHA_CONJUNTA=../




CC = $(PASTINHA_CONJUNTA)\MINGW\bin\gcc
PATH_ALLEGRO=$(PASTINHA_CONJUNTA)\allegro-5.0.10-mingw-4.7.0

all:  equations.o background.o collision_equations.o collisions.o spaceship.o obstacles.o enemy_shot.o enemies.o shot.o supershot.o power_up.o tp.exe

clean:
	-del *.o

equations.o:
	$(CC) -O2 -c equations.c

background.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c background.c

collision_equations.o:
	$(CC) -O2 -c collision_equations.c 

collisions.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c collisions.c 

spaceship.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c spaceship.c

obstacles.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c obstacles.c -std=c99

enemy_shot.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c enemy_shot.c -std=c99

enemies.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c enemies.c -std=c99

shot.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c shot.c -std=c99

supershot.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c supershot.c -std=c99

power_up.o:
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c power_up.c -std=c99


tp.o: tp.c
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c tp.c -std=c99 equations.o background.o collision_equations.o collisions.o spaceship.o obstacles.o enemy_shot.o enemies.o shot.o supershot.o power_up.o


tp.exe: tp.o
	$(CC) -O2 -o tp.exe tp.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a equations.o background.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a collision_equations.o collisions.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a spaceship.o obstacles.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a enemy_shot.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a enemies.o shot.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a supershot.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a power_up.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a