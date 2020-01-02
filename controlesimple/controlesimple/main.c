#include "principal.h"

int main()
{
	InitMenu();
	InitOptions();
	InitGame();

	RunMenu();

	// lib�ration de la m�moire allou�e aux pointeurs
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
	if (!al_init_font_addon())
		Error("al_init_font_addon()");
	if (!al_init_ttf_addon())
		Error("al_init_ttf_addon()");

	// r�cup�ration de la police voulue
	arial72 = al_load_font("arial.ttf", 72, 0);
	if (!arial72)
		Error("al_load_font() arial72");
	// r�cup�ration de la police voulue
	arial32 = al_load_font("arial.ttf", 32, 0);
	if (!arial32)
		Error("al_load_font() arial32");

	//creation fenetre
	display = al_create_display(1024, 768);
	if (!display)
		Error("al_create_display(1024, 768)");

	al_set_window_title(display, "Projet allegro");

	SCREENX = al_get_display_width(display);
	SCREENY = al_get_display_height(display);
	SCREENXD = SCREENX / 2;
	SCREENYD = SCREENY / 2;

	// gerer les images
	if (!al_init_image_addon())
		Error("al_init_image_addon()");

	// creation de timer ( pour du graphisme � changer en 1.0/60 )
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
	al_flush_event_queue(queue);
	Menu = 1;

	//Couches backgrounds
	background0 = al_load_bitmap("BG_Decor.png");
	if (!background0)
		Error("al_load_background0()");
	background1 = al_load_bitmap("Middle_Decor.png");
	if (!background1)
		Error("al_load_background1()");
	background2 = al_load_bitmap("ground + fore.png");
	if (!background2)
		Error("al_load_background2()");

	while (Menu) {

		int x = SCREENXD;
		int y = SCREENYD;
		// 1 effacer le double buffer
		al_clear_to_color(SKY);
		// 2 le rectangle � sa position x,y dans le double buffer
		//al_draw_filled_rectangle(0, SCREENY - 100, SCREENX, SCREENY, GREEN);
		al_draw_scaled_bitmap(background0, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
		al_draw_scaled_bitmap(background1, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
		al_draw_scaled_bitmap(background2, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);

		if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.38))
			Button(SCREENX * 0.25, SCREENY * 0.25, SCREENX * 0.75, SCREENY * 0.38, BLACK, arial72, WHITE, options[language]);
		else
			Button(SCREENX * 0.25, SCREENY * 0.25, SCREENX * 0.75, SCREENY * 0.38, PURPLE, arial72, WHITE, options[language]);

		if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.42) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.55))
			Button(SCREENX * 0.25, SCREENY * 0.42, SCREENX * 0.75, SCREENY * 0.55, BLACK, arial72, WHITE, jouer[language]);
		else
			Button(SCREENX * 0.25, SCREENY * 0.42, SCREENX * 0.75, SCREENY * 0.55, BLUE, arial72, WHITE, jouer[language]);

		if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.59) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.72))
			Button(SCREENX * 0.25, SCREENY * 0.59, SCREENX * 0.75, SCREENY * 0.72, BLACK, arial72, WHITE, quitter[language]);
		else
			Button(SCREENX * 0.25, SCREENY * 0.59, SCREENX * 0.75, SCREENY * 0.72, LIGHTBLUE, arial72, WHITE, quitter[language]);

		// 3 passer le double buffer � l'�cran
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
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.38)) {
				Menu = 0;
				RunOptions(); // options
				Game = 0;
			}
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.42) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.55)) {
				Menu = 0;
				Options = 0; // jouer
				RunGame();
			}
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.59) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.72))
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
	// pr�paration
}

/*******************************************
	SOUS-MENU / BOUCLE
*******************************************/

void RunOptions()
{
	printf("========arrivee dans sous menu\n");
	al_flush_event_queue(queue);
	Options = 1;

	//Couches backgrounds
	background0 = al_load_bitmap("BG_Decor.png");
	if (!background0)
		Error("al_load_background0()");
	background1 = al_load_bitmap("Middle_Decor.png");
	if (!background1)
		Error("al_load_background1()");
	background2 = al_load_bitmap("ground + fore.png");
	if (!background2)
		Error("al_load_background2()");


	while (Options) {
		int x = SCREENXD;
		int y = SCREENYD;
		// 1 effacer le double buffer
		al_clear_to_color(SKY);
		// 2 rectangles
		//al_draw_filled_rectangle(0, SCREENY - 100, SCREENX, SCREENY, GREEN); // sol vert
		al_draw_scaled_bitmap(background0, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
		al_draw_scaled_bitmap(background1, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
		al_draw_scaled_bitmap(background2, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
		al_draw_filled_rectangle(SCREENX * 0.2, 0, SCREENX * 0.8, SCREENY, GREY); // middle

		if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
			Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
		}
		else {
			Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");
		}

		if (BSelectDisplay == 1) {
			// resolution
			if (mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.35))
				Button(SCREENX * 0.26, SCREENY * 0.25, SCREENX * 0.47, SCREENY * 0.35, BLACK, arial32, WHITE, resolution[language]);
			else
				Button(SCREENX * 0.26, SCREENY * 0.25, SCREENX * 0.47, SCREENY * 0.35, WHITE, arial32, BLACK, resolution[language]);
			// 1024x768
			if (mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.45))
				Button(SCREENX * 0.26, SCREENY * 0.35, SCREENX * 0.47, SCREENY * 0.45, LIGHTERGREY, arial32, LIGHTBLUE, "1024x768");
			else
				Button(SCREENX * 0.26, SCREENY * 0.35, SCREENX * 0.47, SCREENY * 0.45, LIGHTERGREY, arial32, BLACK, "1024x768");
			// 1600x1000
			if (mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.45) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.55))
				Button(SCREENX * 0.26, SCREENY * 0.45, SCREENX * 0.47, SCREENY * 0.55, LIGHTGREY, arial32, LIGHTBLUE, "1600x1000");
			else
				Button(SCREENX * 0.26, SCREENY * 0.45, SCREENX * 0.47, SCREENY * 0.55, LIGHTGREY, arial32, BLACK, "1600x1000");
			// fullscreen 1920x1080
			if (mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.55) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.65))
				Button(SCREENX * 0.26, SCREENY * 0.55, SCREENX * 0.47, SCREENY * 0.65, LIGHTERGREY, arial32, LIGHTBLUE, "1920x1080");
			else
				Button(SCREENX * 0.26, SCREENY * 0.55, SCREENX * 0.47, SCREENY * 0.65, LIGHTERGREY, arial32, BLACK, "1920x1080");
		}
		else {
			if (mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.35))
				Button(SCREENX * 0.26, SCREENY * 0.25, SCREENX * 0.47, SCREENY * 0.35, BLACK, arial32, WHITE, resolution[language]);
			else
				Button(SCREENX * 0.26, SCREENY * 0.25, SCREENX * 0.47, SCREENY * 0.35, WHITE, arial32, BLACK, resolution[language]);
		}

		if (BSelectDisplay2 == 1) {
			// langue
			if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.35))
				Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, BLACK, arial32, WHITE, lang[language]);
			else
				Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, WHITE, arial32, BLACK, lang[language]);
			// francais
			if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.45))
				Button(SCREENX * 0.53, SCREENY * 0.35, SCREENX * 0.74, SCREENY * 0.45, LIGHTERGREY, arial32, LIGHTBLUE, "Francais");
			else
				Button(SCREENX * 0.53, SCREENY * 0.35, SCREENX * 0.74, SCREENY * 0.45, LIGHTERGREY, arial32, BLACK, "Francais");
			// anglais
			if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.45) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.55))
				Button(SCREENX * 0.53, SCREENY * 0.45, SCREENX * 0.74, SCREENY * 0.55, LIGHTGREY, arial32, LIGHTBLUE, "English");
			else
				Button(SCREENX * 0.53, SCREENY * 0.45, SCREENX * 0.74, SCREENY * 0.55, LIGHTGREY, arial32, BLACK, "English");
		}
		else {
			if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.35))
				Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, BLACK, arial32, WHITE, lang[language]);
			else
				Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, WHITE, arial32, BLACK, lang[language]);
		}

		// 3 passer le double buffer � l'�cran
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
			// retour
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				RunMenu();
				Options = 0; // bt retour
				Game = 0;
			}
			// resolution
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.35)) {
				if (BSelectDisplay) {
					BSelectDisplay = 0;
				}
				else {
					BSelectDisplay = 1;
					BSelectDisplay2 = 0;
				}
			}
			// 1024x768
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.45)) {
				if (BSelectDisplay) {
					al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
					al_resize_display(display, 1024, 768);
					SCREENX = al_get_display_width(display);
					SCREENY = al_get_display_height(display);
					BSelectDisplay = 0;
				}
			}
			// 1600x1000
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.45) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.55)) {
				if (BSelectDisplay) {
					al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
					al_resize_display(display, 1600, 1000);
					SCREENX = al_get_display_width(display);
					SCREENY = al_get_display_height(display);
					BSelectDisplay = 0;
				}
			}
			// 1920x1080
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.55) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.65)) {
				if (BSelectDisplay) {
					al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 1);
					al_resize_display(display, 1920, 1080);					
					SCREENX = al_get_display_width(display);
					SCREENY = al_get_display_height(display); 
					BSelectDisplay = 0;
				}
			}

			// langue
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.35)) {
				if (BSelectDisplay2) {
					BSelectDisplay2 = 0;
				}
				else {
					BSelectDisplay2 = 1;
					BSelectDisplay = 0;
				}
			}
			// francais
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.45)) {
				if (BSelectDisplay2) {
					language = 0;
					BSelectDisplay2 = 0;
				}
			}
			// anglais
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.45) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.55)) {
				if (BSelectDisplay2) {
					language = 1;
					BSelectDisplay2 = 0;
				}
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
	// lib�ration m�moire des pointeurs allou�s pour le sous menu
}

/*******************************************
	JEU / INITIALISATION
*******************************************/

void InitGame()
{
	GROUND = SCREENY - 120;
	life = 3;
	star = 3;
	Death = 0;
	protect = 2.00;
	jump = 0.00;
	pulse = 20.00;
	gravity = -2.00;
	hitboxdisplay = 0;
	esheetdisplay = 0;
}

/*******************************************
	JEU / BOUCLE
*******************************************/

void RunGame()
{
	InitGame();
	printf("========arrivee dans jeu\n");
	al_flush_event_queue(queue);
	Game = 1;
	int x = SCREENX / 2+100; // position du rectangle
	int y = SCREENY / 2+100;
	int px = SCREENX / 2; // position du rectangle
	int py = SCREENY / 2;
	int debug = 0;




	// un ensemble de personnage = tableau de personnage
	Personnage* personnages[PERSONNAGEMAX];
	//parcours du tableau
	for (int i = 0; i < PERSONNAGEMAX; i++)
		personnages[i] = CreatePersonnage(RED);

	// un ensemble de personnage = tableau de personnage
	Personnage* personnagesy[3];
	//parcours du tableau
	for (int i = 0; i < 3; i++)
		personnagesy[i] = CreatePersonnage(YELLOW);

	//Couches backgrounds
	background0 = al_load_bitmap("BG_Decor.png");
	if (!background0)
		Error("al_load_background0()");
	background1 = al_load_bitmap("Middle_Decor.png");
	if (!background1)
		Error("al_load_background1()");
	background2 = al_load_bitmap("ground + fore.png");
	if (!background2)
		Error("al_load_background2()");
	background3 = al_load_bitmap("platform.png");
	if (!background3)
		Error("al_load_background3()");

	hitbox = al_load_bitmap("platformhitbox.png");
	if (!hitbox)
		Error("al_load_hitbox()");
	esheet = al_load_bitmap("esheet.bmp");
	if (!esheet)
		Error("al_load_esheet()");
	heart = al_load_bitmap("heart.png");
	if (!heart)
		Error("al_load_heart()");

	al_start_timer(timer); //ne pas oublier pour d�marer le timer
	while (Game) {
		debug = 0;

		//r�cup�ration des �v�nements
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		// clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = 1;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = 1;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = 1;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = 1;
				break;

			case ALLEGRO_KEY_F2: Game = 0; break;
			case ALLEGRO_KEY_F3: if (hitboxdisplay == 1) hitboxdisplay = 0; else hitboxdisplay = 1; break;
			case ALLEGRO_KEY_F4: if (esheetdisplay == 1) esheetdisplay = 0; else esheetdisplay = 1; break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
			printf("%d presse dans boucle jeu\n", event.keyboard.keycode);
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = 0;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = 0;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = 0;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = 0;
				break;

			}
			printf("%d relache dans boucle jeu\n", event.keyboard.keycode);
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			// spawn/hurt protection
			if (protect > 0.00)
				protect -= 0.02;

			// gravite/jump
			if (jump == 0)
			{
				if (c_down == 0) {
					y -= gravity;
					gravity -= 0.2;
					if (y > SCREENY-80)
						y = SCREENY-80;
				}
			}
			else if (jump > 0)
			{
				if (c_up == 0) {
					y -= pulse;
					pulse -= 0.1;
					if (pulse < 8.00) pulse = 0.00;
					jump *= 0.01;
					gravity = 1.00;
				}
				else {
					jump = 0.00;
					pulse = 0.00;
					gravity = 1.00;
				}
			}

			// controles
			if (Death == 0) {
				if (key[KEY_RIGHT] == 1 && c_right == 0) {
					//x += 10;
					dx0 += 2;
					dx1 += 5;
					dx2 += 10;
					dxe -= 10;
				}
				if (key[KEY_UP] == 1 && c_down == 1 && c_up == 0) {
					jump = 1.00;
					pulse = 10.00;
				}
				if (key[KEY_LEFT] == 1 && c_left == 0) {
					//x -= 10;
					dx0 -= 2;
					dx1 -= 5;
					dx2 -= 10;
					dxe += 10;
				}
				if (key[KEY_DOWN] == 1 && c_down == 0) {
					y += 10;
				}
			}
			Collision(&x, &y);
			px = x;
			py = y;
			debug = 1;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans le jeu\n", event.mouse.button);
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				RunMenu();
				Options = 0; // bt retour
				Game = 0;
			}
			if (event.mouse.button == 1 && Death == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.48)) {
				x = SCREENXD;
				y = SCREENYD; // rejouer
				InitGame();
			}
			if (event.mouse.button == 1 && Death == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.52) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.65)) {
				Game = 0;
				Menu = 1; // menu principal
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
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (debug == 1)
		{
			// 1 clear all
			al_clear_to_color(SKY);

			// 2 draw
			// background
			al_draw_scaled_bitmap(background0, dx0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background1, dx1, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background2, dx2, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background3, dx2, 0, 1024, 768, 0, 0, SCREENX, SCREENY, 0);
	


			// should display hitbox sheet?
			if (hitboxdisplay == 1)
				al_draw_scaled_bitmap(hitbox, dx2, 0, 1024, 768, 0, 0, SCREENX, SCREENY, 0);

			// should display enemy sheet?
			if (esheetdisplay == 1)
				al_draw_scaled_bitmap(esheet, dx2, 0, 1024, 768, 0, 0, SCREENX, SCREENY, 0);

			// should display hearts?
			if (life >= 1)
				al_draw_bitmap(heart, 100, 0, 0);
			if (life >= 2)
				al_draw_bitmap(heart, 150, 0, 0);
			if (life >= 3)
				al_draw_bitmap(heart, 200, 0, 0);
			if (life >= 4)
				al_draw_bitmap(heart, 250, 0, 0);
			if (life >= 5)
				al_draw_bitmap(heart, 300, 0, 0);
			if (life >= 6)
				al_draw_bitmap(heart, 350, 0, 0);

			// clear old enemy hitbox
			al_set_target_bitmap(esheet);
			al_clear_to_color(BLACK);
			al_set_target_backbuffer(al_get_current_display());

			// add new enemy hitbox
			for (int i = 0; i < PERSONNAGEMAX; i++) {
				AvancePersonnage(personnages[i]);
				AffichePersonnage(personnages[i]);
			}
			// add new star hitbox
			for (int i = 0; i < star; i++) {
				AvancePersonnage(personnagesy[i]);
				AffichePersonnage(personnagesy[i]);
			}

			// return button
			if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40)
				Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
			else
				Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");

			// death screen
			if (Death == 1)
			{
				al_draw_filled_rectangle(SCREENX * 0.2, SCREENY*0.3, SCREENX * 0.8, SCREENY*0.7, GREY); // middle
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.48))
					Button(SCREENX * 0.25, SCREENY * 0.35, SCREENX * 0.75, SCREENY * 0.48, BLACK, arial72, WHITE, rejouer[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.35, SCREENX * 0.75, SCREENY * 0.48, BLUE, arial72, WHITE, rejouer[language]);


				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.52) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.65))
					Button(SCREENX * 0.25, SCREENY * 0.52, SCREENX * 0.75, SCREENY * 0.65, BLACK, arial72, WHITE, menu_p[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.52, SCREENX * 0.75, SCREENY * 0.65, LIGHTBLUE, arial72, WHITE, menu_p[language]);
			}
			else {
				// cube
				if (protect > 0.00)
					al_draw_filled_rectangle(px, py, px + 20, py + 20, CUBEHIT);
				else
					al_draw_filled_rectangle(px, py, px + 20, py + 20, CUBE);
			}
			// 3 display all
			al_flip_display();
		}
	}
}

/*******************************************
	JEU / DESTRUCTION
*******************************************/

void DestroyGame()
{
	al_destroy_bitmap(hitbox);
	al_destroy_bitmap(background0);
	al_destroy_bitmap(background1);
	al_destroy_bitmap(background2);
	al_destroy_bitmap(esheet);
	al_destroy_timer(timer);
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
	fontsize = al_get_font_line_height(font)/2;
	al_draw_textf(font, textcolor, x1 + (x2 - x1) / 2, y1 - fontsize + ((y2-y1)/2), ALLEGRO_ALIGN_CENTER, text);
}

void Kill()
{
	if (life == 0) {
		Death = 1;
	}
	else if (protect <= 0.00) {
		life -= 1;
		protect = 2.00;
	}
}

void Collision(int* x, int* y)
{
	ALLEGRO_COLOR color_down = al_get_pixel(hitbox, *x + 10+dx2, *y + 21);
	ALLEGRO_COLOR color_up = al_get_pixel(hitbox, *x + 10+dx2, *y - 15);
	ALLEGRO_COLOR color_right = al_get_pixel(hitbox, *x + 21+dx2, *y + 10);
	ALLEGRO_COLOR color_left = al_get_pixel(hitbox, *x - 1+dx2, *y + 10);

	unsigned char r, g, b;

	//  ground
	al_unmap_rgb(color_down, &r, &g, &b);
	c_down = 0;
	if (r == 0 && g == 128 && b == 0) {
		c_down = 1;
	}
	printf("%d,%d,%d\n", r, g, b);

	al_unmap_rgb(color_up, &r, &g, &b);
	c_up = 0;
	if (r == 0 && g == 128 && b == 0) {
		c_up = 1;
	}

	al_unmap_rgb(color_right, &r, &g, &b);
	c_right = 0;
	if (r == 0 && g == 128 && b == 0) {
		c_right = 1;
	}

	al_unmap_rgb(color_left, &r, &g, &b);
	c_left = 0;
	if (r == 0 && g == 128 && b == 0) {
		c_left = 1;
	}

	color_down = al_get_pixel(esheet, *x + 10, *y + 21);
	color_up = al_get_pixel(esheet, *x + 10, *y - 15);
	color_right = al_get_pixel(esheet, *x + 21, *y + 10);
	color_left = al_get_pixel(esheet, *x - 1, *y + 10);

	//  enemy
	al_unmap_rgb(color_down, &r, &g, &b);
	if (r == 200 && g == 0 && b == 0) {
		Kill();
	}

	al_unmap_rgb(color_up, &r, &g, &b);
	if (r == 200 && g == 0 && b == 0) {
		Kill();
	}

	al_unmap_rgb(color_right, &r, &g, &b);
	if (r == 200 && g == 0 && b == 0) {
		Kill();
	}

	al_unmap_rgb(color_left, &r, &g, &b);
	if (r == 200 && g == 0 && b == 0) {
		Kill();
	}

	//  star
	al_unmap_rgb(color_down, &r, &g, &b);
	if (r == 255 && g == 200 && b == 0) {
		star -= 1;
		life += 1;
	}

	al_unmap_rgb(color_up, &r, &g, &b);
	if (r == 255 && g == 200 && b == 0) {
		star -= 1;
		life += 1;
	}

	al_unmap_rgb(color_right, &r, &g, &b);
	if (r == 255 && g == 200 && b == 0) {
		star -= 1;
		life += 1;
	}

	al_unmap_rgb(color_left, &r, &g, &b);
	if (r == 255 && g == 200 && b == 0) {
		star -= 1;
		life += 1;
	}

	//printf("(%d,%d,%d)\n", r, g, b);
}

//Cr�a Perso
Personnage* CreatePersonnage(ALLEGRO_COLOR color)
{
	Personnage* p = (Personnage*)malloc(sizeof(Personnage));
	p->ey = rand() % SCREENY;
	p->ex = rand() % SCREENX;
	
	p->edx = (float)rand() / RAND_MAX * 50 - 25;
	p->edy = (float)rand() / RAND_MAX * 50 - 25;

	p->etx = 20;
	p->ety = 20;
	p->color = color;

	//cr�a bitmap m�moire ram
	p->im = al_create_bitmap(p->etx, p->ety);

	//s�lec bitmap pour op� dessin
	al_set_target_bitmap(p->im);

	//le dessin
	al_clear_to_color(p->color);

	//retour au double buffer pour affiche �cran
	al_set_target_backbuffer(al_get_current_display());


	return p;
}
//affiche perso
void AffichePersonnage(Personnage* p)
{
	// draw enemy on enemy sheet
	al_set_target_bitmap(esheet);
	al_draw_filled_rectangle(p->ex-dx2, p->ey, p->ex + 20-dx2, p->ey + 20, p->color);
	al_set_target_backbuffer(al_get_current_display());
	// draw enemy on background
	al_draw_bitmap(p->im, p->ex-dx2, p->ey, 0);
}

void AvancePersonnage(Personnage* p)
{
	// moove x
	p->ex += p->edx;
	if (p->ex < 0) {
		p->ex = 0;
		p->edx = ((float)rand() / RAND_MAX) * 10;
	}
	if (p->ex + p->etx >= SCREENX) {
		p->ex = SCREENX - p->etx;
		p->edx = ((float)rand() / RAND_MAX) * -5;
	}

	// moove y
	p->ey += p->edy;
	if (p->ey < 0) {
		p->ey = 0;
		p->edy = ((float)rand() / RAND_MAX) * 10;
	}
	if (p->ey + p->ety >= SCREENY) {
		p->ey = SCREENY - p->ety;
		p->edy = ((float)rand() / RAND_MAX) * -5;
	}
}