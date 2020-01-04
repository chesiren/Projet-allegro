#ifndef HPRINCIPAL
#define HPRINCIPAL

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
#define CUBEHITSTAR al_map_rgb(0,100,150)
#define PURPLE al_map_rgb(128,0,255)
#define GREEN al_map_rgb(0,128,0)
#define RED al_map_rgb(200,0,0)
#define ORANGE al_map_rgb(200,100,0)
#define YELLOW al_map_rgb(255,200,0)

#define PERSONNAGEMAX	10
#define ETOILEMAX	3
#define TICK 30

// Le contrôle de la fuidité du clavier
enum { KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT, KEY_MAX };
_Bool key[KEY_MAX] = { 0 };

// Menu
void Initialisation(void);
void RunMenu(void);
void Destroy(void);

// Options
void RunOptions(void);

// Jeu
void ResetGame(void);
void RunGame(void);

// Outils
void Error(char* txt);
void Button(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, ALLEGRO_FONT* font, ALLEGRO_COLOR textcolor, char text[]);
void Collision(int* x, int* y);
void Kill(void);

// globales
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* arial32;
ALLEGRO_FONT* arial72;

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
int mx, my, x, y;
int life;
int star;
int dx0=0, dx1=0, dx2=0; // Coordonnées des backgrounds
int fontsize;
int language = 0;
float protect;
float starprotect;

float jump;
float pulse;
float gravity;

int dessiner = 0;

bool c_up = 0;
bool c_right = 0;
bool c_left = 0;
bool c_down = 0;

bool Menu = 0;
bool Options = 0;
bool Game = 0;
bool Death = 0;

bool HitboxDisplay = 0;
bool ESheetDisplay = 0;
bool BSelectDisplay = 0;
bool BSelectDisplay2 = 0;

char options[2][16] = { "Options", "Parameters" };
char jouer[2][16] = { "Jouer", "Play" };
char quitter[2][16] = { "Quitter", "Leave" };
char lang[2][16] = { "Langage", "Language" };
char rejouer[2][16] = { "Rejouer", "Play again" };
char menu_p[2][16] = { "Menu principal", "Main menu" };
char resolution[2][16] = { "Resolution", "Screen size" };

typedef struct Personnage {
	float ex, ey;				// Position
	float edx, edy;				// Déplacement
	int etx, ety;				// Taille
	ALLEGRO_COLOR color;		// Couleur
	ALLEGRO_BITMAP* im;			// L'image associé
}Personnage;

Personnage* CreatePersonnage(ALLEGRO_COLOR color);
void AffichePersonnage(Personnage* p);
void AvancePersonnage(Personnage* p);

Personnage* personnages[PERSONNAGEMAX];
Personnage* personnagesy[ETOILEMAX];

#endif