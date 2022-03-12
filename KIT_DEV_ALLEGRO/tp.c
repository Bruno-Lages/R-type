#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <string.h>
#include "equations.h"
#include "background.h"
#include "spaceship.h"
#include "obstacles.h"
#include "enemies.h"
#include "enemy_shot.h"
#include "shot.h"
#include "supershot.h"
#include "power_up.h"
#include "collisions.h"

float FPS = 60;  

int newRecord(int score, unsigned long long int *record) {
	FILE *arq = fopen("record.txt", "r");
	*record = 0;
	if(arq != NULL) {
		fscanf(arq, "%d", record);
		fclose(arq);
	}
	if(*record < score ) {
		arq = fopen("record.txt", "w");
		fprintf(arq, "%d", score);
		fclose(arq);
		return 1;
	}
	return 0;
	
}


int main() {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer2 = NULL;

    srand(time(NULL));

    //inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }


    // carrega a biblioteca de áudio
    if(!al_install_audio()) {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    };
    

    // carrega a biblioteca de codificação
    if(!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize codec!\n");
        return -1;
    };

    // reserva faixas de músicas
    al_reserve_samples(2);


    // carrega arquivo de música
    ALLEGRO_SAMPLE *background_song = al_load_sample("assets/sfx/background-song.ogg");
    ALLEGRO_SAMPLE *shot_sfx = al_load_sample("assets/sfx/SND.DAT_00092.wav");
    ALLEGRO_SAMPLE *cannon_shot_sfx = al_load_sample("assets/sfx/SND.DAT_00037.wav");

    // instancia o arquivo de música
    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(background_song);

    // configura a instância
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(songInstance, 0.6);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

    //cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    timer2 = al_create_timer(1.0 / 30);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
    if(!timer2) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}


    //cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

    // carrega a biblioteca de imagens
    if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

    // carrega o arquivo de imagem
    ALLEGRO_BITMAP *heart = al_load_bitmap("assets/sprites/life.png");
    ALLEGRO_BITMAP *gasoline_sprite = al_load_bitmap("assets/sprites/gasoline.png");
    ALLEGRO_BITMAP *screwdriver_sprite = al_load_bitmap("assets/sprites/screwdriver.png");
    ALLEGRO_BITMAP *spaceship_sprite = al_load_bitmap("assets/sprites/spaceship/spaceship-sprite.png");
    ALLEGRO_BITMAP *shot_sprite = al_load_bitmap("assets/sprites/shot/shot.png");
    ALLEGRO_BITMAP *rshot_sprite = al_load_bitmap("assets/sprites/shot/rshot.png");
    ALLEGRO_BITMAP *supershot_sprite = al_load_bitmap("assets/sprites/supershot/supershot.png");
    ALLEGRO_BITMAP *rsupershot_sprite = al_load_bitmap("assets/sprites/supershot/rsupershot.png");
    ALLEGRO_BITMAP *supershot_loading_sprites[16];
    char extension[] = ".png";
    char filenum[3];
    for(int i=0;i<=16;++i) {
        char filename[] = "assets/sprites/supershot/loading/";
        // if(i == 8) continue;
        if(i - 8 >= 0){
            filenum[0] = '+';
            filenum[1] = (i-7) + '0';
        } else {
            filenum[0] = '-';
            filenum[1] = ((i-8)*-1) + '0';
        }
        filenum[2] = '\0';
        strcat(filename, filenum);
        strcat(filename, extension);
        supershot_loading_sprites[i] = al_load_bitmap(filename);
    }
    ALLEGRO_BITMAP *enemy_shot_sprite = al_load_bitmap("assets/sprites/enemy_shot1.png");
    ALLEGRO_BITMAP *basic_enemy[8];
    char num[2];
    for(int i = 0; i < 8; i++) {
        char filename[] = "assets/sprites/basic-enemy/";
        num[0] = i + '0';
        num[1] = '\0';
        strcat(filename, num);
        strcat(filename, extension);
        basic_enemy[i] = al_load_bitmap(filename);
    }
    ALLEGRO_BITMAP *robot_sprite = al_load_bitmap("assets/sprites/robot/robot.png");
    ALLEGRO_BITMAP *floor_sprite = al_load_bitmap("assets/sprites/obstacles/floor1.png");
    ALLEGRO_BITMAP *wall_sprite = al_load_bitmap("assets/sprites/obstacles/wall1.png");
    ALLEGRO_BITMAP *floor_robot_sprite = al_load_bitmap("assets/sprites/robot/floor_robot.png");
    ALLEGRO_BITMAP *cannon_sprite = al_load_bitmap("assets/sprites/cannons/cannon.png");

    //inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

    //inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}

    //carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("assets/fonts/PressStart2P-Regular.ttf", 24, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

    //instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

    //cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

    //registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
    //registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    //registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer2));
    //registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source());

    //inicia a pontuação
    int score = 0;
    unsigned long long int record;

    //inicia gasolina
    Power_up power_up;
    init_power_up(&power_up);

    //inicia estrelas
    Star stars[3][TOTAL_STARS];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < TOTAL_STARS; j++) {
            init_star(&stars[i][j], i);
        }
    }

    //inicia a nave
    Spaceship spaceship[2];
    for(int i = 0; i < 2; ++i) {
        init_spaceship(&spaceship[i]);
    }

    //inicia a parede
    Obstacle wall[2];
    for(int i = 0; i < 2; ++i) {
        init_wall(&wall[i]);
    }

    //inicia o chão
    Obstacle floor[TOTAL_FLOOR_SPLITS];
    init_floor(floor);

    //inicia os inimigos
    Enemy enemy[TOTAL_ENEMIES];
    init_enemy_line(enemy, TOTAL_ENEMIES);
    
    Robot robot[TOTAL_ENEMIES];
    for(int i = 0; i < TOTAL_ENEMIES; i++) {
        init_robot(&robot[i]);
    }

    //inicia os tiros
    Shot shot[2][TOTAL_SHOTS];
    for(int h = 0; h < 2; ++h) {
        for(int i = 0; i < TOTAL_SHOTS; i++) {
            init_shot(&shot[h][i]);
        }
    }

    // inicia o tiro especial
    Supershot supershot[2];
    for(int i = 0; i < 2; ++i) {
        init_supershot(&supershot[i], spaceship[0]);
    }

    Floor_robot floor_robot[TOTAL_FLOOR_ROBOTS];
    for(int i = 0; i < TOTAL_FLOOR_ROBOTS; i++) {
        init_floor_robot(&floor_robot[i]);
    }

    Cannon cannon;
    init_cannon(&cannon, wall[rand() % 2]);

    // toca a instância
    al_play_sample_instance(songInstance);

    //inicia o temporizador
	al_start_timer(timer);
    al_start_timer(timer2);

    char string[200];

    int supershot_timer = 0;
    int timer_counter;

    
    int GAME_DIFFICULTY = 3;
    
    //min 1, max 10
    int SHOT_STORAGE; 

    //min 5, max 50
    int ENEMIES_ALIVE;

    //min 20(5), max 60(1.6)
    int shot_speed;

    //se o jogo está pausado
    int pause = 0;

    int multiplayer = 0;
    int TOTAL_SPACESHIPS;
    
    // enquanto a nave não estiver destruída
    while(spaceship[0].lifes > 0 || spaceship[1].lifes > 0) {

        if(!spaceship[0].lifes && !multiplayer) spaceship[1].lifes = 0;

        ALLEGRO_EVENT ev;
        //espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

        switch(ev.type) {

            //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
            case ALLEGRO_EVENT_TIMER:
                if(ev.timer.source == timer) {
                    timer_counter = al_get_timer_count(timer);

                    //altera p fps de acordo com a pontuação até o limite                    
                    FPS = 90 - (int)(60 / (score*pow(10,(-4 + GAME_DIFFICULTY)) + 1));

                    TOTAL_SPACESHIPS = multiplayer + 1;

                    //altera a quantidade de tiros de acordo com a pontuação até o limite
                    SHOT_STORAGE = TOTAL_SHOTS - ((TOTAL_SHOTS-1) /(score*pow(10, -(GAME_DIFFICULTY + 1)) + 1));

                    //altera a velocidade dos inimigos
                    ENEMIES_SPEED = MAX_ENEMIES_SPEED - ((MAX_ENEMIES_SPEED-1) / (score*pow(10, -GAME_DIFFICULTY) + 1)) || 1;

                    //altera a quantidade de inimigos
                    ENEMIES_ALIVE = TOTAL_ENEMIES - ((int)(0.7*TOTAL_ENEMIES) /(score*pow(10, -GAME_DIFFICULTY) + 1));


                    if(pause) {
                        al_flip_display();
                        continue;
                    }

                    // cria o background
                    al_clear_to_color(al_map_rgb(0, 0, 0));

                    // carrega as estrelas
                    for(int i = 0; i < 3; i++) {
                        for(int j = 0; j < TOTAL_STARS; j++) {
                            update_star(&stars[i][j]);
                            draw_star(stars[i][j]);
                        }
                    }

                    // desenha as vidas da nave
                    for(int i = 0; i < TOTAL_SPACESHIPS; ++i) {
                        for(int j = 0; j < spaceship[i].lifes; j++) {
                            al_draw_bitmap(heart, SCREEN_W - 10 - (1+j)*(al_get_bitmap_width(heart)) + 5, 10 + i*(SCREEN_BORDER_H), 0);
                        }
                    }
    
                    // mostra um texto com a pontuação
                    sprintf(string, "score: %d", score);
                    al_draw_text(size_32, al_map_rgb(250, 250, 250), 10, 5, 0, string);
    
                    //===================================Obstáculos===================================

                    //atualiza a posição da parede
                    for(int i = 0; i < 2; ++i) {
                        update_wall(&wall[i]);
                    }

                    //atualiza o chão
                    update_floor(floor);

                    //colisão de paredes
                    obstacles_collision(&wall[0], &wall[1]);
    
                    // adiciona a parede
                    for(int i = 0; i < 2; ++i) {
                        draw_wall(wall[i], wall_sprite);
                    }

                    // adiciona o chão
                    draw_floor(floor, floor_sprite);
    
                    //========================================nave=======================================
                    
                    // desenha a nave
                    for(int i = 0; i < TOTAL_SPACESHIPS; ++i) {
                        draw_spaceship(&spaceship[i], spaceship_sprite);
                        update_spaceship(&spaceship[i]);
                    }
    
                    // observa colisões da nave com obstáculos
                    for(int i = 0; i < TOTAL_SPACESHIPS; ++i) {
                        spaceship_obstacle_collision(floor[0], &spaceship[i]);
                        for(int j = 0; j < 2; j++) {
                            spaceship_obstacle_collision(wall[j], &spaceship[i]);
                        }
                    }
    
                    //===========================================tiros==========================================

                    //observa colisões entre tiros atirados, inimigos e paredes na tela
                    for(int h = 0; h < 2; ++h) {
                        for(int i = 0; i < SHOT_STORAGE; i++) {
                            if(shot[h][i].shooted) {
                                //colisões com chão e parede
                                shot_obstacle_collision(floor[0], &shot[h][i]);
                                for(int j = 0; j < 2; j++) {
                                    shot_obstacle_collision(wall[j], &shot[h][i]);
                                }
    
                                //colisões com inimigos simples
                                for(int j = 0; j < ENEMIES_ALIVE; j++) {
                                    shot_basic_enemy_collision(&shot[h][i], &enemy[j], &score);
                                    shot_robot_collision(&shot[h][i], &robot[j], &score);
                                    shot_enemy_shot_collision(&shot[h][i], &robot[j].shot, &score);
                                }
    
                                //calcula a colisão com robôs de chão
                                for(int j = 0; j < TOTAL_FLOOR_ROBOTS; j++) {
                                    shot_floor_robot_collision(&shot[h][i], &floor_robot[j], &score);
                                    for(int k = 0; k < FLOOR_ROBOT_TOTAL_SHOTS; ++k) {
                                        shot_enemy_shot_collision(&shot[h][i], &floor_robot[j].shot[k], &score);
                                    }
                                }
    
                                //colisão de tiros e canhões
                                shot_cannon_collision(&shot[h][i], &cannon, &score);
                                for(int j = 0; j < CANNON_TOTAL_SHOTS; ++j) {
                                    shot_enemy_shot_collision(&shot[h][i], &cannon.shot[j], &score);
                                }
    
                                //colisão de tiro e gasolina
                                shot_power_up_collision(&shot[h][i], &power_up);
                            }
                        }
                    }

                    //adiciona o tiro
                    for(int h = 0; h < 2; ++h) {
                        for(int i = 0; i < SHOT_STORAGE; i++) {
                            if(shot[h][i].shooted) {
                                draw_shot(shot[h][i], shot_sprite, rshot_sprite);
                            }
                        }
                    }

                    //=======================================supertiro=====================================

                    //observa a colisão do supertiro
                    for(int h = 0; h < 2; ++h) {
                        if(supershot[h].shooted) {
                            //colisões com obstáculos
                            // supershot_obstacle_collision(floor[0], &supershot);
                            for(int i = 0; i < 2; i++) {
                                supershot_obstacle_collision(wall[i], &supershot[h]);
                            }
    
                            //colisões dos inimigos simples, robôs e seus tiros
                            for(int i = 0; i < ENEMIES_ALIVE; i++) {
                                supershot_basic_enemy_collision(&supershot[h], &enemy[i], &score);
                                supershot_robot_collision(&supershot[h], &robot[i], &score);
                                supershot_enemy_shot_collision(&supershot[h], &robot[i].shot, &score);
                            }
    
                            //colisão do supertiro com o robô de chão e seus tiros
                            for(int i = 0; i < TOTAL_FLOOR_ROBOTS; i++) {
                                supershot_floor_robot_collision(&supershot[h], &floor_robot[i], &score);
                                for(int j = 0; j < FLOOR_ROBOT_TOTAL_SHOTS; ++j) {
                                    supershot_enemy_shot_collision(&supershot[h], &floor_robot[i].shot[j], &score);
                                }
                            }
    
                            //colisão do supertiro com o canhão e seus tiros
                            supershot_cannon_collision(&supershot[h], &cannon, &score);
                            for(int i = 0; i < CANNON_TOTAL_SHOTS; ++i) {
                                supershot_enemy_shot_collision(&supershot[h], &cannon.shot[i], &score);
                            }
    
    
                            //colisão do supertiro com power ups
                            supershot_power_up_collision(&supershot[h], &power_up);
    
                        }
                    }

                    //atualiza a posição do supertiro
                    for(int i = 0; i < 2; ++i) {
                        
                        update_supershot(&supershot[i], spaceship[i]);
    
                        //adiciona o tiro especial
                        if(supershot[i].loading || supershot[i].shooted) {

                            //converte os quadros da animação de carregamento para 10fps
                            if(timer_counter % 6 == 0) {
                                supershot_timer < 8 ? (supershot_timer++) : (supershot_timer = 0);
                            }
                                draw_supershot(supershot[i], supershot_sprite, rsupershot_sprite, supershot_loading_sprites, supershot_timer);

                        }
                    }
    
                    //============================================inimigos simples=========================================
                    //observa colisões envolvendo inimigos simples
                    for(int i = 0; i < ENEMIES_ALIVE; i++) {
                            
                        //colisões com obstáculos
                        for(int j = 0; j < 2; ++j) {
                            basic_enemies_obstacle_collision(wall[j], &enemy[i]);
                        }
                        
                        for(int j = 0; j < TOTAL_FLOOR_SPLITS; ++j) {
                            basic_enemies_obstacle_collision(floor[j], &enemy[i]);
                        }

                        //colisões com a nave
                        for(int j = 0; j < TOTAL_SPACESHIPS; ++j) {
                            spaceship_basic_enemy_collision(&spaceship[j], &enemy[i]);
                        }

                        // observa a colisão entre dois inimigos
                        for(int j = 0; j < ENEMIES_ALIVE; j++) {
                            if(i != j) {
                                basic_enemies_collision(&enemy[i], &enemy[j]);
                            }
                        }

                        //colisões com robôs
                        for(int j = 0; j < CANNON_TOTAL_SHOTS; ++j) {
                            basic_enemies_robot_collision(&enemy[i], &robot[j]);
                        }

                        //observa a colisão de robôs de chão
                        for(int j = 0; j < TOTAL_FLOOR_ROBOTS; j++) {
                            basic_enemies_floor_robot_collision(&enemy[i], &floor_robot[j]);
                            for(int k = 0; k < FLOOR_ROBOT_TOTAL_SHOTS; k++) {
                                enemy_shot_basic_enemy_collision(&floor_robot[j].shot[k], &enemy[i]);
                            }
                        }

                        //colisões com canhão e seus tiros
                        basic_enemies_cannon_collision(&enemy[i], &cannon);
                        for(int j = 0; j < CANNON_TOTAL_SHOTS; ++j) {
                            enemy_shot_basic_enemy_collision(&cannon.shot[j], &enemy[i]);
                        }
                        
                        //colisões com canhão e power ups
                        basic_enemies_power_up_collision(&enemy[i], &power_up);
                    }

                    //atualiza os inimigos simples
                    update_enemy_line(enemy, ENEMIES_ALIVE);
    
                    //adiciona inimigos
                    for(int i = 0; i < ENEMIES_ALIVE; i++) {
                        draw_enemy(enemy[i], basic_enemy);
                    }
    
                    //=====================================robôs============================================

                    //observa colisões envolvendo robôs
                    for(int i = 0; i < ENEMIES_ALIVE; i++) {

                        //observa a colisão dos robôs com o chão
                            robots_obstacle_collision(floor[0], &robot[i]);
                            enemy_shot_obstacle_collision(floor[0], &robot[i].shot);
                        
                        //observa a colisão dos robôs e seus tiros com obstáculos
                        for(int j = 0; j < 2; ++j) {
                            robots_obstacle_collision(wall[j], &robot[i]);
                            enemy_shot_obstacle_collision(wall[j], &robot[i].shot);
                        }

                        //calcula a colisão dos robôs e seus tiros com a nave
                        for(int j = 0; j < TOTAL_SPACESHIPS; ++j) {
                            spaceship_robot_collision(&spaceship[j], &robot[i]);
                            spaceship_enemy_shot_collision(&spaceship[j], &robot[i].shot);
                        }
                                                        
                        // observa a colisão entre dois robôs e seus tiros
                        for(int j = 0; j < ENEMIES_ALIVE; j++) {
                            if(i != j) {
                                //colisão de robôs
                                robots_collision(&robot[i], &robot[j]);
                                
                                //colisão de robôs e tiros
                                enemy_shot_robot_collision(&robot[i], &robot[j].shot);

                                //colisão de tiros de robôs
                                enemy_shots_collision(&robot[i].shot, &robot[j].shot);
                            }
                        }

                        //colisão com robôs de chão e seus tiros
                        for(int j = 0; j < TOTAL_FLOOR_ROBOTS; ++j) {
                            robots_floor_robot_collision(&robot[i], &floor_robot[j]);
                            for(int k = 0; k < 0; ++k) {
                                enemy_shot_robot_collision(&robot[i], &floor_robot[j].shot[k]);
                                enemy_shots_collision(&robot[i].shot, &floor_robot[j].shot[k]);
                            }
                        }

                        //colisões com canhão e seus tiros
                        robots_cannon_collision(&robot[i], &cannon);
                        for(int j = 0; j < CANNON_TOTAL_SHOTS; ++j) {
                            enemy_shot_robot_collision(&robot[i], &cannon.shot[j]);
                            enemy_shots_collision(&robot[i].shot, &cannon.shot[j]);
                        }

                        //colisões com power ups
                        robots_power_up_collision(&robot[i], &power_up);
                        enemy_shot_power_up_collision(&power_up, &robot[i].shot);

                    }

                    //configura os robôs
                    for(int i = 0; i < ENEMIES_ALIVE; i++) {
                        for(int j = 0; j < TOTAL_SPACESHIPS; ++j) {
                            update_robot(&robot[i], spaceship[j], (al_get_timer_count(timer) % (int)(FPS*2)) == 0);
                        }
                        update_enemy_shot(&robot[i].shot, 0);
                        draw_robot(robot[i], robot_sprite, timer, FPS);
                        draw_enemy_shot(robot[i].shot, enemy_shot_sprite);
                    }

                    //============================================robôs de chão============================================
                    
                    //observa colisões envolvendo robôs de chão
                    for(int i = 0; i < 2; i++) {

                        //calcula a colisão dos robôs de chão com a parede e a nave
                        for(int j = 0; j < 2; ++j) {
                            floor_robot_obstacle_collision(wall[j], &floor_robot[i]);
                        }
                        for(int j = 0; j < TOTAL_SPACESHIPS; ++j) {
                            spaceship_floor_robot_collision(&spaceship[j], &floor_robot[i]);
                        }
                        
                        //observa a colisão dos tiros de robôs de chão com obstáculos e a nave
                        for(int j = 0; j < FLOOR_ROBOT_TOTAL_SHOTS; ++j) {
                            for(int k = 0; k < 2; ++k) {
                                enemy_shot_obstacle_collision(wall[k], &floor_robot[i].shot[j]);
                            }
                            for(int k = 0; k < TOTAL_SPACESHIPS; ++k) {
                                spaceship_enemy_shot_collision(&spaceship[k], &floor_robot[i].shot[j]);
                            }
                        }
                        
                        // observa a colisão entre dois robôs de chão e seus tiros
                        for(int j = 0; j < 2; j++) {
                            if(i != j) {
                                //colisão de robôs
                                floor_robot_collision(&floor_robot[i], &floor_robot[j]);
                                
                                for(int k = 0; k < FLOOR_ROBOT_TOTAL_SHOTS; ++k) {
                                    //colisão de robôs e tiros
                                    enemy_shot_floor_robot_collision(&floor_robot[i], &floor_robot[j].shot[k]);
                                    for(int l = 0; l < FLOOR_ROBOT_TOTAL_SHOTS; ++l) {
                                        enemy_shots_collision(&floor_robot[i].shot[l], &floor_robot[j].shot[k]);
                                    }
                                }
                            }
                        }

                        //colisão do canhão
                        floor_robot_cannon_collision(&floor_robot[i], &cannon);
                        for(int j = 0; j < CANNON_TOTAL_SHOTS; ++j) {
                            enemy_shot_floor_robot_collision(&floor_robot[i], &cannon.shot[j]);
                        }

                        //colisão com power up
                        floor_robot_power_up_collision(&floor_robot[i], &power_up);
                        for(int j = 0; j < FLOOR_ROBOT_TOTAL_SHOTS; ++j) {
                            enemy_shot_power_up_collision(&power_up, &floor_robot[i].shot[j]);
                        }

                    }

                    //atualiza o tiro dos robôs de chão
                    for(int i = 0; i < TOTAL_FLOOR_ROBOTS; i++) {
                        for(int j = 0; j < FLOOR_ROBOT_TOTAL_SHOTS; j++) {
                            update_enemy_shot(&floor_robot[i].shot[j], 1);
                            draw_enemy_shot(floor_robot[i].shot[j], enemy_shot_sprite);
                        }
                    }

                    //atualiza os robôs de chão
                    for(int i = 0; i < TOTAL_FLOOR_ROBOTS; i++) {
                        for(int j = 0; j < TOTAL_SPACESHIPS; ++j) {
                            update_floor_robot(&floor_robot[i], spaceship[j], (al_get_timer_count(timer) % (int)(FPS*1) == 0));
                        }
                        draw_floor_robot(floor_robot[i], floor_robot_sprite, timer, FPS);
                    }

                    //============================================canhão============================================

                    //calcula a colisão do canhão com a parede
                    for(int i = 0; i < 2; ++i) {
                        cannon_obstacle_collision(wall[i], &cannon);
                    }

                    //calcula colisão da nave com o canhão e seus tiros
                    for(int i = 0; i < TOTAL_SPACESHIPS; ++i) {
                        spaceship_cannon_collision(&spaceship[i], &cannon);
                        for(int j = 0; j < CANNON_TOTAL_SHOTS; ++j) {
                            spaceship_enemy_shot_collision(&spaceship[i], &cannon.shot[j]);
                        }
                    }

                    //calcula a colisão do canhão com o power up
                    cannon_power_up_collision(&cannon, &power_up);

                    //atualiza os tiros de canhões
                    for(int i = 0; i < CANNON_TOTAL_SHOTS; i++) {
                        update_enemy_shot(&cannon.shot[i], 0);
                        draw_enemy_shot(cannon.shot[i], enemy_shot_sprite);
                    }

                    //atualiza o canhão
                    for(int j = 0; j < TOTAL_SPACESHIPS; ++j) {
                        update_cannon(&cannon, wall[rand() % 2], spaceship[j], (al_get_timer_count(timer) % (int)(FPS*3) == 0), cannon_shot_sfx);
                    }
                    draw_cannon(cannon, cannon_sprite);
                    
                    //============================================power up============================================

                    //calcula colisão do power up com a nave
                    for(int i = 0; i < TOTAL_SPACESHIPS; ++i) {
                        spaceship_power_up_collision(&spaceship[i], &power_up);
                    }

                    //calcula colisão do power up com obstáculos
                    for(int i = 0; i < 2; ++i) {
                        power_up_obstacle_collision(&power_up, wall[i]);
                    }
                    for(int i = 0; i < TOTAL_FLOOR_SPLITS; ++i) {
                        power_up_obstacle_collision(&power_up, floor[i]);
                    }

                    //configura os power ups
                    update_power_up(&power_up);
                    draw_power_up(power_up, gasoline_sprite, screwdriver_sprite);
    
                    //atualiza a tela (quando houver algo para mostrar)
                    al_flip_display();

                }

                if(ev.timer.source == timer2 && !pause) {
                    //carrega o tiro especial
                    for(int i = 0; i < 2; ++i) {
                        if(supershot[i].loading) load_supershot(&supershot[i], spaceship[i]);
                    }

                    //atualiza o tiro
                    for(int h = 0; h < 2; ++h) {
                        for(int i = 0; i < TOTAL_SHOTS; i++) {
                            if(shot[h][i].shooted) {
                                update_shot(&shot[h][i], spaceship[0]);
                            }
                        }
                    }

                }


                break;


            //se o tipo de evento for o fechamento da tela (clique no x da janela)
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                spaceship[0].lifes = 0;
                spaceship[1].lifes = 0;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch(ev.keyboard.keycode) {
                    // ao apertar para cima, verifica se ultrapassará o limite de tela e move a nave pra cima
                    case ALLEGRO_KEY_UP:
                        spaceship[multiplayer].y_movement = 1;
                        break;

                    // ao apertar w, verifica se ultrapassará o limite de tela e move a nave pra cima
                    case ALLEGRO_KEY_W:
                        spaceship[0].y_movement = 1;
                        break;

                    // ao apertar para a esquerda, verifica se ultrapassará o limite de tela e move a nave pra trás
                    case ALLEGRO_KEY_LEFT:
                        spaceship[multiplayer].x_movement = -1;
                        break;
                    
                    // ao apertar a, verifica se ultrapassará o limite de tela e move a nave pra trás
                    case ALLEGRO_KEY_A:
                        spaceship[0].x_movement = -1;
                        break;

                    // ao apertar s, verifica se ultrapassará o limite de tela e move a nave pra baixo 
                    case ALLEGRO_KEY_DOWN:
                        spaceship[multiplayer].y_movement = -1;
                        break;

                    // ao apertar s, verifica se ultrapassará o limite de tela e move a nave pra baixo 
                    case ALLEGRO_KEY_S:
                        spaceship[0].y_movement = -1;
                        break;

                    // ao apertar para a direita, verifica se ultrapassará o limite de tela e move a nave pra frente 
                    case ALLEGRO_KEY_RIGHT:
                        spaceship[multiplayer].x_movement = 1;
                        break;

                    // ao apertar d, verifica se ultrapassará o limite de tela e move a nave pra frente 
                    case ALLEGRO_KEY_D:
                        spaceship[0].x_movement = 1;
                        break;

                    case ALLEGRO_KEY_ESCAPE:
                        pause = !pause;
                        break;

                    case ALLEGRO_KEY_M:
                        multiplayer = !multiplayer;
                        TOTAL_SPACESHIPS = multiplayer + 1;
                        printf("\n%d %d", multiplayer, TOTAL_SPACESHIPS);
                        break;

                    // ao apertar espaço atira
                    case ALLEGRO_KEY_SPACE:

                        if(spaceship[0].lifes) {
                            // procura pelo primeiro tiro não atirado e atira
                            for(int i = 0; i < SHOT_STORAGE; i++) {
                                if(shot[0][i].shooted == 0) {
                                    al_play_sample(shot_sfx, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                                    shoot_out(&shot[0][i], spaceship[0]);
                                    break;
                                }
                            }
                        }
                        break;
                    
                    case ALLEGRO_KEY_ENTER:

                        if(spaceship[1].lifes) {
                            // procura pelo primeiro tiro não atirado e atira
                            for(int i = 0; i < SHOT_STORAGE; i++) {
                                if(shot[1][i].shooted == 0) {
                                    al_play_sample(shot_sfx, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                                    shoot_out(&shot[1][i], spaceship[1]);
                                    break;
                                }
                            }
                        }
                        break;
                    
                    case ALLEGRO_KEY_PAD_ENTER:

                        if(spaceship[1].lifes) {
                            // procura pelo primeiro tiro não atirado e atira
                            for(int i = 0; i < SHOT_STORAGE; i++) {
                                if(shot[1][i].shooted == 0) {
                                    al_play_sample(shot_sfx, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                                    shoot_out(&shot[1][i], spaceship[1]);
                                    break;
                                }
                            }
                        }
                        break;
                }
                break;

            case ALLEGRO_EVENT_KEY_CHAR:
                switch(ev.keyboard.keycode) {
                    // ao apertar para cima, verifica se ultrapassará o limite de tela e move a nave pra cima
                    case ALLEGRO_KEY_UP:
                        if(ev.keyboard.repeat) {
                            spaceship[multiplayer].y_movement = 2;
                        }
                        break;

                    // // ao apertar w, verifica se ultrapassará o limite de tela e move a nave pra cima
                    case ALLEGRO_KEY_W:
                        if(ev.keyboard.repeat){
                    spaceship[0].y_movement = 2;
                        }
                        break;
                    
                    // ao apertar s, verifica se ultrapassará o limite de tela e move a nave pra baixo 
                    case ALLEGRO_KEY_DOWN:
                        if(ev.keyboard.repeat){
                            spaceship[multiplayer].y_movement = -2;
                        }
                        break;

                    // ao apertar s, verifica se ultrapassará o limite de tela e move a nave pra baixo 
                    case ALLEGRO_KEY_S:
                        if(ev.keyboard.repeat){
                            spaceship[0].y_movement = -2;
                        }
                        break;

                    //ao pressionar espaço, carrega o supertiro
                    case ALLEGRO_KEY_SPACE:

                        if(ev.keyboard.repeat) {
                            //verifica e o supertiro não foi atirado ou se já está carregando
                            if(!supershot[0].shooted && !supershot[0].loading) {
                                reload_supershot(&supershot[0], spaceship[0]);
                                supershot[0].loading = 1;
                            }
                        }
                        break;
                    case ALLEGRO_KEY_ENTER:

                        if(ev.keyboard.repeat) {
                            //verifica e o supertiro não foi atirado ou se já está carregando
                            if(!supershot[1].shooted && !supershot[1].loading) {
                                reload_supershot(&supershot[1], spaceship[1]);
                                supershot[1].loading = 1;
                            }
                        }
                        break;
                    
                    case ALLEGRO_KEY_PAD_ENTER:

                        if(ev.keyboard.repeat) {
                            //verifica e o supertiro não foi atirado ou se já está carregando
                            if(!supershot[1].shooted && !supershot[1].loading) {
                                reload_supershot(&supershot[1], spaceship[1]);
                                supershot[1].loading = 1;
                            }
                        }
                        break;
                }
                break;

                case ALLEGRO_EVENT_KEY_UP:
                    switch(ev.keyboard.keycode) {
                        case ALLEGRO_KEY_UP:
                            spaceship[multiplayer].y_movement = 0;
                            break;

                        case ALLEGRO_KEY_W:
                            spaceship[0].y_movement = 0;
                            break;

                        case ALLEGRO_KEY_LEFT:
                            spaceship[multiplayer].x_movement = 0;
                            break;

                        case ALLEGRO_KEY_A:
                            spaceship[0].x_movement = 0;
                            break;

                        case ALLEGRO_KEY_DOWN:
                            spaceship[multiplayer].y_movement = 0;
                            break;

                        case ALLEGRO_KEY_S:
                            spaceship[0].y_movement = 0;
                            break;

                        case ALLEGRO_KEY_RIGHT:
                            spaceship[multiplayer].x_movement = 0;
                            break;

                        case ALLEGRO_KEY_D:
                            spaceship[0].x_movement = 0;
                            break;
                        
                        // ao soltar o espaço, se o supertiro estiver carregando, solta ele
                        case ALLEGRO_KEY_SPACE:
                            if(supershot[0].loading) {
                                supershot[0].loading = 0;
                                if(supershot[0].coordenates.radius > 10) {
                                    supershot[0].shooted = 1;
                                    supershot[0].direction = -spaceship[0].multiplicator;
                                    supershot[0].coordenates.x1 += supershot[0].direction * 113;
                                }
                            }
                            break;
                        
                        case ALLEGRO_KEY_ENTER:
                            if(supershot[1].loading) {
                                supershot[1].loading = 0;
                                if(supershot[1].coordenates.radius > 10) {
                                    supershot[1].shooted = 1;
                                    supershot[1].direction = -spaceship[1].multiplicator;
                                    supershot[1].coordenates.x1 += supershot[1].direction * 113;
                                }
                            }
                            break;
                        
                        case ALLEGRO_KEY_PAD_ENTER:
                            if(supershot[1].loading) {
                                supershot[1].loading = 0;
                                if(supershot[1].coordenates.radius > 10) {
                                    supershot[1].shooted = 1;
                                    supershot[1].direction = -spaceship[1].multiplicator;
                                    supershot[1].coordenates.x1 += supershot[1].direction * 113;
                                }
                            }
                            break;
                        
                        case ALLEGRO_KEY_C:
                            printf("\nInimigos vivos: %i", ENEMIES_ALIVE);
                            break;
                    }
                    break;

            
        }
    }

    char string2[200];
    unsigned long long int god = 1000000;
    if(newRecord(score, &record)) {
        // cria o background
        al_clear_to_color(al_map_rgb(200,100,150));
        if(score > 1000000) {
            god = (double)score / god;
            sprintf(string, "New record: %.2fM!", god);
        } else sprintf(string, "New record: %d!", score);
        al_draw_text(size_32, al_map_rgb(250, 250, 250), SCREEN_W/2 - 100, SCREEN_H/2, 0, string);

        al_flip_display();
        al_rest(4);
    } else {
        al_clear_to_color(al_map_rgb(40,10,150));
        if(record > 1000000) {
            god = (double)record / god;
            sprintf(string, "Record: %dM", god);
        } else {
            sprintf(string, "Record: %d", record);
        }
        sprintf(string2, "Score: %d", score);
        al_draw_text(size_32, al_map_rgb(250, 250, 250), SCREEN_W/2 - 100, SCREEN_H/2, 0, string);
        al_draw_text(size_32, al_map_rgb(250, 250, 250), SCREEN_W/2 - 100, SCREEN_H/2 + 5 + al_get_font_line_height(size_32), 0, string2);

        al_flip_display();
        al_rest(1);
    }

    //fecha as configuraçãoes
    al_destroy_sample(background_song);
    al_destroy_sample(shot_sfx);
    al_destroy_sample(cannon_shot_sfx);
    al_destroy_sample_instance(songInstance);
	al_destroy_timer(timer);
    al_destroy_bitmap(heart);
    al_destroy_bitmap(gasoline_sprite);
    al_destroy_bitmap(screwdriver_sprite);
    al_destroy_bitmap(spaceship_sprite);
    al_destroy_bitmap(shot_sprite);
    al_destroy_bitmap(rshot_sprite);
    al_destroy_bitmap(supershot_sprite);
    al_destroy_bitmap(rsupershot_sprite);
    for(int i=0; i<=16;i++) {
        al_destroy_bitmap(supershot_loading_sprites[i]);
    }
    for(int i = 0; i < 8; i++) {
        al_destroy_bitmap(basic_enemy[i]);
    }
    al_destroy_bitmap(floor_sprite);
    al_destroy_bitmap(wall_sprite);
    al_destroy_bitmap(robot_sprite);
    al_destroy_bitmap(floor_robot_sprite);
    al_destroy_bitmap(cannon_sprite);
    al_destroy_display(display);
	al_destroy_event_queue(event_queue);
    
    return 0;
}