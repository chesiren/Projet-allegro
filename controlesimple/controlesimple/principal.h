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
#define LIGHTGREY al_map_rgb(130,130,130)
#define LIGHTERGREY al_map_rgb(160,160,160)
#define VLIGHTGREY al_map_rgb(220,220,220)
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

int PERSONNAGEMAX = 10;
int ETOILEMAX = 3;
int TICK = 30;

// Le contrôle de la fuidité du clavier
enum { KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT, KEY_MAX };
_Bool key[KEY_MAX] = { 0 };

// Menu
void Initialisation(void);
void RunMenu(void);
void RunMenuCampagne(void);
void RunMenuSandbox(void);
void Destroy(void);

// Options
void RunOptions(void);

// Jeu
void ResetGame(void);
void RunGame(int niveau);

// Outils
void Error(char* txt);
void Button(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, ALLEGRO_FONT* font, ALLEGRO_COLOR textcolor, char text[]);
void Collision(int* x, int* y);
void Kill(void);

// Globales
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* arial22;
ALLEGRO_FONT* arial32;
ALLEGRO_FONT* arial72;

// Bitmap
ALLEGRO_BITMAP* backgroundmenu;
ALLEGRO_BITMAP* background0;
ALLEGRO_BITMAP* background1;
ALLEGRO_BITMAP* background2;
ALLEGRO_BITMAP* background3;
ALLEGRO_BITMAP* vignette1;
ALLEGRO_BITMAP* vignette2;
ALLEGRO_BITMAP* vignette3;
ALLEGRO_BITMAP* esheet;
ALLEGRO_BITMAP* or;
ALLEGRO_BITMAP* hitbox;
//Sprits personnages
ALLEGRO_BITMAP* Animwait[4];
ALLEGRO_BITMAP* Animrun[6];
ALLEGRO_BITMAP* Animjump[8];

int k, l = 0;
bool orientation = 0;
int SCREENX;
int SCREENY;
int SCREENXD;
int SCREENYD;
int mx, my, x, y;
int life;
int fond = 0;
int star;
int dx0=0, dx1=0, dx2=0, dx3=0; // Coordonnées des backgrounds et platforme
int fontsize;
int language = 0;
float protect;
float starprotect;
int sbplus[3][7] = { 51, 48, 50, 51, 50, 48, 49,
					 48, 49, 48, 48, 48, 49, 48,
					 3, 10, 2, 3, 2, 10, 1 };

float jump;
float pulse;
float dpulse;
float gravity;
float dgravity;

int dessiner = 0;

bool c_up = 0;
bool c_right = 0;
bool c_left = 0;
bool c_down = 0;
bool c_stuck = 0;

bool Menu = 0;
bool SousMenu = 0;
bool MenuCampagne = 0;
bool MenuSandbox = 0;
bool Options = 0;
bool Credit = 0;
bool Game = 0;
bool Death = 0;

bool HitboxDisplay = 0;
bool ESheetDisplay = 0;
bool BSelectDisplay = 0;
bool BSelectDisplay2 = 0;

// Menu
char options[2][16] = { "Options", "Parameters" };
char jouer[2][16] = { "Jouer", "Play" };
char quitter[2][16] = { "Quitter", "Leave" };
char campagne[2][16] = { "Campagne", "Story" };
char bacasable[2][16] = { "Bac a sable", "Sandbox" };

// Options
char lang[2][16] = { "Langage", "Language" };
char resolution[2][16] = { "Resolution", "Screen size" };
char fermer[2][16] = { "Fermer", "Close" };
char txtcredit1[2][50] = { "Images libres de droit de craftpix.net", "Free to use pictures from craftpix.net" };
char txtcredit2[2][100] = { "Fond: https://craftpix.net/freebies/free-cartoon-forest-game-backgrounds/", "Background: https://craftpix.net/freebies/free-cartoon-forest-game-backgrounds/" };
char txtcredit3[2][100] = { "Icones: https://craftpix.net/freebies/free-game-icons-of-fantasy-things-pack-15/", "Icons: https://craftpix.net/freebies/free-game-icons-of-fantasy-things-pack-15/" };

// Mort
char rejouer[2][16] = { "Rejouer", "Play again" };
char menu_p[2][16] = { "Menu principal", "Main menu" };

// Sandbox
char commencer[2][16] = { "Commencer", "Start" };
char etoile[2][16] = { "Etoiles", "Stars" };
char ennemi[2][16] = { "Ennemis", "Enemies" };
char tmpsprotec[2][18] = { "Temps protection", "Protect time" };
char vie[2][16] = { "Vies", "Life" };
char gravite[2][16] = { "Gravite", "Gravity" };
char psaut[2][18] = { "Puissance de saut", "Jump power" };
char niveau[2][16] = { "Niveau", "Level" };

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

Personnage* personnages[99];
Personnage* personnagesy[99];

#endif