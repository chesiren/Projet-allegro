#ifndef HPRINCIPALE
#define HPRINCIPALE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define BLACK al_map_rgb(0,0,0)
#define GREY al_map_rgb(50,50,50)
#define WHITE al_map_rgb(255,255,255)
#define LIGHTBLUE al_map_rgb(0,100,255)
#define SKY al_map_rgb(50,128,200)
#define BLUE al_map_rgb(0,0,255)
#define PURPLE al_map_rgb(128,0,255)
#define GREEN al_map_rgb(0,128,0)
#define RED al_map_rgb(200,0,0)

// menu
void InitMenu(void);
void RunMenu(void);
void DestroyMenu(void);

// options
void InitOptions(void);
void RunOptions(void);
void DestroyOptions(void);

// jeu
void InitGame(void);
void RunGame(void);
void DestroyGame(void);

// outils
void Error(char* txt);
void Button(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, ALLEGRO_FONT* font, ALLEGRO_COLOR textcolor, char text[]);

// globales
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* arial72;
ALLEGRO_FONT* arial32;

int SCREENX;
int SCREENY;
int mx, my, x, y;
int language = 1;

bool Menu = 0;
bool Options = 0;
bool Game = 0;

char options[16] = "Options";
char jouer[16] = "Jouer";
char quitter[16] = "Quitter";
char lang[16] = "Langage";
#endif