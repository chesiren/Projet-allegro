#include "main.h"
#include "menu.h"


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
	if (!al_init_ttf_addon())
		Error("al_init_font_addon()");
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

	al_set_window_title(display, "Projet allegro");

	SCREENX = al_get_display_width(display);
	SCREENY = al_get_display_height(display);
	SCREENXD = SCREENX / 2;
	SCREENYD = SCREENY / 2;

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
	al_flush_event_queue(queue);
	Menu = 1;
	x = SCREENXD;
	y = SCREENYD;

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
		debug = 0;

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
			debug = 1;
		}
		// controle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (debug == 1) {
			// clear
			al_clear_to_color(SKY);

			// background
			al_draw_scaled_bitmap(background0, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background1, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background2, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);

			// options
			if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.38))
				Button(SCREENX * 0.25, SCREENY * 0.25, SCREENX * 0.75, SCREENY * 0.38, BLACK, arial72, WHITE, options[language]);
			else
				Button(SCREENX * 0.25, SCREENY * 0.25, SCREENX * 0.75, SCREENY * 0.38, PURPLE, arial72, WHITE, options[language]);
			// jouer
			if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.42) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.55))
				Button(SCREENX * 0.25, SCREENY * 0.42, SCREENX * 0.75, SCREENY * 0.55, BLACK, arial72, WHITE, jouer[language]);
			else
				Button(SCREENX * 0.25, SCREENY * 0.42, SCREENX * 0.75, SCREENY * 0.55, BLUE, arial72, WHITE, jouer[language]);
			// quitter
			if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.59) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.72))
				Button(SCREENX * 0.25, SCREENY * 0.59, SCREENX * 0.75, SCREENY * 0.72, BLACK, arial72, WHITE, quitter[language]);
			else
				Button(SCREENX * 0.25, SCREENY * 0.59, SCREENX * 0.75, SCREENY * 0.72, LIGHTBLUE, arial72, WHITE, quitter[language]);

			// passer le double buffer à l'écran
			al_flip_display();
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
