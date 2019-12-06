#include "principale.h"

/*enum{rien, survol, clique, max_im};

typedef struct bouton {
	int x, y;
	int tx, ty;
	int etat; // 0,1 ou 2
	ALLEGRO_BITMAP* im[max_im];
};*/

int main()
{
	InitMenu();
	InitOptions();
	InitGame();
	
	RunMenu();

	// libération de la mémoire allouée aux pointeurs
	DestroyMenu();
	DestroyOptions();
	DestroyGame();

	return 0;
}
/*******************************************
	PRINCIPAL / INITIALISATION
*******************************************/

void InitMenu()
{
	if (!al_init())
		Error("al_init()");
	if (!al_install_keyboard())
		Error("al_install_keyboard()");
	if (!al_install_mouse())
		Error("al_install_mouse()");
	if (!al_init_primitives_addon())
		Error("al_init_primitives_addon()");
	al_init_font_addon();
	if (!al_init_ttf_addon())
		Error("al_init_ttf_addon()");

	// récupération de la police voulue
	arial72 = al_load_font("arial.ttf", 72, 0);
	if (!arial72)
		Error("al_load_font() arial72");
	// récupération de la police voulue
	arial32 = al_load_font("arial.ttf", 32, 0);
	if (!arial32)
		Error("al_load_font() arial32");

	//creation fenetre
	display = al_create_display(1024, 768);
	if (!display)
		Error("al_create_display(1024, 768)");

	SCREENX = al_get_display_width(display);
	SCREENY = al_get_display_height(display);

	// gerer les images
	if (!al_init_image_addon())
		Error("al_init_image_addon()");

	// creation de timer ( pour du graphisme à changer en 1.0/60 )
	timer = al_create_timer(1.0 / TICK);
	if (!timer)
		Error("al_create_timer(1.0/60)");

	// mise en place d'une file d'evenements
	queue = al_create_event_queue();
	if (!queue)
		Error("al_create_event_queue()");

	// les types d'evenements a recuperer
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(display));

	al_start_timer(timer);
}

/*******************************************
	PRINCIPAL / BOUCLE
*******************************************/

void RunMenu()
{
	printf("========arrivee dans menu principal\n");
	al_flush_event_queue;
	Menu = 1;

	while (Menu) {

		int x = SCREENX / 2;
		int y = SCREENY / 2;
		// 1 effacer le double buffer
		al_clear_to_color(SKY);
		// 2 le rectangle à sa position x,y dans le double buffer
		al_draw_filled_rectangle(0, SCREENY - 100, SCREENX, SCREENY, GREEN);
		if (mx >= (x - 200) && my >= (y - 200) && mx <= (x + 200) && my <= (y - 100)) {
			Button(x - 200, y - 200, x + 200, y - 100, BLACK, arial72, WHITE, options);
		}
		else {
			Button(x - 200, y - 200, x + 200, y - 100, PURPLE, arial72, WHITE, options);
		}
		if (mx >= (x - 200) && my >= (y - 50) && mx <= (x + 200) && my <= (y + 50)) {
			Button(x - 200, y - 50, x + 200, y + 50, BLACK, arial72, WHITE, jouer);
		}
		else {
			Button(x - 200, y - 50, x + 200, y + 50, BLUE, arial72, WHITE, jouer);
		}
		if (mx >= (x - 200) && my >= (y + 100) && mx <= (x + 200) && my <= (y + 200)) {
			Button(x - 200, y + 100, x + 200, y + 200, BLACK, arial72, WHITE, quitter);
		}
		else {
			
			Button(x - 200, y + 100, x + 200, y + 200, LIGHTBLUE, arial72, WHITE, quitter);
		}
		
		// 3 passer le double buffer à l'écran
		al_flip_display();

		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);
		// clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("touche presse dans boucle principale\n");
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F1: RunOptions(); break;
			case ALLEGRO_KEY_F2: RunGame();  break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
		}
		// souris
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans la boucle principale\n", event.mouse.button);
			if (event.mouse.button == 1 && mx >= (x - 200) && my >= (y - 200) && mx <= (x + 200) && my <= (y - 100)) {
				Menu = 0;
				RunOptions(); // options
				Game = 0;
			}
			if (event.mouse.button == 1 && mx >= (x - 200) && my >= (y - 50) && mx <= (x + 200) && my <= (y + 50)){
				Menu = 0;
				Options = 0; // jouer
				RunGame();
			}
			if (event.mouse.button == 1 && mx >= (x - 200) && my >= (y + 100) && mx <= (x + 200) && my <= (y + 200))
				exit(EXIT_SUCCESS);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans la boucle principale\n", event.mouse.button);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans boucle principale\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			//printf("bp");
		}
		// controle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}
	}
}

/*******************************************
	PRINCIPAL / DESTRUCTION
*******************************************/

void DestroyMenu()
{
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_font(arial72);
}

/*******************************************
	SOUS-MENU / INITIALISATION
*******************************************/

void InitOptions()
{
	// préparation
}

/*******************************************
	SOUS-MENU / BOUCLE
*******************************************/

void RunOptions()
{
	printf("========arrivee dans sous menu\n");
	al_flush_event_queue;
	Options = 1;

	while (Options) {
		int x = SCREENX / 2;
		int y = SCREENY / 2;
		// 1 effacer le double buffer
		al_clear_to_color(SKY);
		// 2 le rectangle à sa position x,y dans le double buffer
		al_draw_filled_rectangle(0, SCREENY - 100, SCREENX, SCREENY, GREEN);
		al_draw_filled_rectangle(SCREENX*0.2, 0, SCREENX*0.8, SCREENY, GREY);
		if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
			Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
		}
		else {
			Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");
		}
		
		// 3 passer le double buffer à l'écran
		al_flip_display();

		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);

		// clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("touche presse dans boucle sous menu\n");
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F1: Options = 0; break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
		}
		// souris
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans le sous menu\n", event.mouse.button);
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				RunMenu();
				Options = 0; // bt retour
				Game = 0;
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans le sous menu\n", event.mouse.button);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans le sous menu\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori

			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			//printf("bp");
		}
		// controle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}
	}
}

/*******************************************
	SOUS-MENU / DESTRUCTION
*******************************************/

void DestroyOptions()
{
	// libération mémoire des pointeurs alloués pour le sous menu
}

/*******************************************
	JEU / INITIALISATION
*******************************************/

void InitGame()
{
	// préparation
}

/*******************************************
	JEU / BOUCLE
*******************************************/

void RunGame()
{
	printf("========arrivee dans jeu\n");
	al_flush_event_queue;
	Game = 1;	
	int x = SCREENX / 2; // position du rectangle
	int y = SCREENY / 2;

	while (Game) {
		// 1 effacer le double buffer
		al_clear_to_color(SKY);
		// 2 le rectangle à sa position x,y dans le double buffer
		al_draw_filled_rectangle(0, SCREENY - 100, SCREENX, SCREENY, GREEN);
		al_draw_filled_rectangle(x, y, x + 20, y + 20, BLUE); // cube
		if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
			Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
		}
		else {
			Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");
		}
		// 3 passer le double buffer à l'écran
		al_flip_display();

		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);

		
		// clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("%d presse dans boucle jeu\n", event.keyboard.keycode);
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F2: Game = 0; break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_UP) up = 1;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				right = 1;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				down = 1;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT){
				left = 1;
			}
		}
		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			printf("%d relache dans boucle jeu\n", event.keyboard.keycode);
			if (event.keyboard.keycode == ALLEGRO_KEY_UP) up = 0;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				right = 0;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				down = 0;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
				left = 0;
			}
		}
		// caractères et répétitions
		/*else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
			char* label = event.keyboard.repeat ? "repeat" : "KEY_CHAR";
			if (event.keyboard.keycode == ALLEGRO_KEY_UP && y == (SCREENY - 120)) {
				jump = 1.00;
				pulse = 10.00;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) x += 10; 
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) y += 10;
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) x -= 10;
		}*/
		// souris
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans le jeu\n", event.mouse.button);
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				RunMenu();
				Options = 0; // bt retour
				Game = 0;
			}
			if (event.mouse.button == 1 && mx >= x && my >= y && mx <= (x + 20) && my <= (y + 20)) {
				RunMenu();
				Options = 0; // cube milieu
				Game = 0;
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans le jeu\n", event.mouse.button);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans le jeu\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			//printf("|");

			//gravite
			if (jump == 0)
			{
				//y += GRAVITY;

				y -= gravity;
				gravity -= 0.1;
				if (y > SCREENY - 120) 
					y = SCREENY - 120;
			}
			else if (jump>0)
			{
				y -= pulse;
				pulse -= 0.1;
				jump *= 0.01;
				gravity = 1.00;
			}

			// controles
			if (right == 1) {
				x += 5;
			}
			if (up == 1) {
				if (y == (SCREENY - 120)) {
					jump = 1.00;
					pulse = 10.00;
				}
			}
			if (left == 1) {
				x -= 5;
			}
			if (down == 1) {
				y += 5;
			}
		}
		// controle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}
	}
}

/*******************************************
	JEU / DESTRUCTION
*******************************************/

void DestroyGame()
{
	// libération mémoire des pointeurs alloués pour le jeu
}

/*******************************************
	OUTILS
*******************************************/

void Error(char* txt)
{
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Error", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}

void Button(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, ALLEGRO_FONT* font, ALLEGRO_COLOR textcolor, char text[])
{
	
	al_draw_filled_rectangle(x1, y1, x2, y2, color);
	al_draw_textf(font, textcolor, x1 + (x2 - x1) / 2, y1, ALLEGRO_ALIGN_CENTER, text);
}