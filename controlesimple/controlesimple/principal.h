#ifndef HPRINCIPALE
#define HPRINCIPALE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define BLACK al_map_rgb(0,0,0)
#define GREY al_map_rgb(50,50,50)
#define LIGHTGREY al_map_rgb(150,150,150)
#define LIGHTERGREY al_map_rgb(130,130,130)
#define WHITE al_map_rgb(255,255,255)
#define LIGHTBLUE al_map_rgb(0,100,255)
#define SKY al_map_rgb(50,128,200)
#define BLUE al_map_rgb(0,0,255)
#define CUBE al_map_rgb(0,0,255)
#define CUBEHIT al_map_rgb(100,0,150)
#define PURPLE al_map_rgb(128,0,255)
#define GREEN al_map_rgb(0,128,0)
#define RED al_map_rgb(200,0,0)
#define ORANGE al_map_rgb(200,100,0)
#define YELLOW al_map_rgb(255,200,0)

#define PERSONNAGEMAX	10
#define TICK 30

//le contrôle de la fuidité du clavier
enum { KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT, KEY_MAX };
_Bool key[KEY_MAX] = { 0 };

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
void Collision(int* x, int* y);
void Kill(void);

// globales
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* arial72;
ALLEGRO_FONT* arial32;

// bitmap
ALLEGRO_BITMAP* background0;
ALLEGRO_BITMAP* background1;
ALLEGRO_BITMAP* background2;
ALLEGRO_BITMAP* background3;
ALLEGRO_BITMAP* esheet;
ALLEGRO_BITMAP* heart;
ALLEGRO_BITMAP* hitbox;

int SCREENX;
int SCREENY;
int SCREENXD;
int SCREENYD;
int GROUND;
int mx, my, x, y;
int life;
int star;
int dx0=0, dx1=0, dx2=0, dxhb=0, dxe=0; // Coordonnées des backgrounds
int fontsize;

float jump;
float pulse;
float gravity;

float protect;

bool c_up = 0;
bool c_right = 0;
bool c_left = 0;
bool c_down = 0;

bool Menu = 0;
bool Options = 0;
bool Game = 0;
bool Death = 0;

bool hitboxdisplay = 0;
bool esheetdisplay = 0;
bool BSelectDisplay = 0;

char options[16] = "Options";
char jouer[16] = "Jouer";
char quitter[16] = "Quitter";
char lang[16] = "Langage";
char rejouer[16] = "Rejouer";
char menu_p[16] = "Menu principal";
char select[16] = "Selectionner";

typedef struct Personnage {
	float ex, ey;				//position
	float edx, edy;			//déplacement
	int etx, ety;				//taille
	ALLEGRO_COLOR color;	//couleur
	ALLEGRO_BITMAP* im;		//l'image associé
}Personnage;

Personnage* CreatePersonnage(ALLEGRO_COLOR color);
void AffichePersonnage(Personnage* p);
void AvancePersonnage(Personnage* p);

#endif