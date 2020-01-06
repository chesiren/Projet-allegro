#include "principal.h"

int main()
{
	Initialisation();

	RunMenu();

	Destroy();

	return 0;
}

/*******************************************
	INITIALISATION
*******************************************/

void Initialisation()
{
	// Initialisation d'allegro
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
	if (!al_init_image_addon())
		Error("al_init_image_addon()");

	// Récupération de la police voulue
	arial22 = al_load_font("arial.ttf", 22, 0);
	if (!arial22)
		Error("al_load_font(\"arial.ttf\", 22, 0)");

	arial32 = al_load_font("arial.ttf", 32, 0);
	if (!arial32)
		Error("al_load_font(\"arial.ttf\", 72, 0)");

	arial72 = al_load_font("arial.ttf", 72, 0);
	if (!arial72)
		Error("al_load_font(\"arial.ttf\", 72, 0)");

	// Création fenêtre
	display = al_create_display(1024, 768);
	if (!display)
		Error("al_create_display(1024, 768)");

	al_set_window_title(display, "Projet allegro");

	// Création de timer ( pour du graphisme à changer en 1.0/60 )
	timer = al_create_timer(1.0 / TICK);
	if (!timer)
		Error("al_create_timer(1.0/30)");

	// Mise en place d'une file d'évenements
	queue = al_create_event_queue();
	if (!queue)
		Error("al_create_event_queue()");

	// Les types d'évenements à récuperer
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(display));

	// Lancer le timer
	al_start_timer(timer);

	// Images de fond
	backgroundmenu = al_load_bitmap("forest1/forest1.png");
	if (!backgroundmenu)
		Error("al_load_backgroundmenu()");

	// Images personages
	Animwait[0] = al_load_bitmap("joueur/Animwait1.png");
	if (!Animwait[0])
		Error("Animwait1");
	Animwait[1] = al_load_bitmap("joueur/Animwait2.png");
	if (!Animwait[1])
		Error("Animwait2");
	Animwait[2] = al_load_bitmap("joueur/Animwait3.png");
	if (!Animwait[2])
		Error("Animwait3");
	Animwait[3] = al_load_bitmap("joueur/Animwait4.png");
	if (!Animwait[3])
		Error("Animwait4");

	Animrun[0] = al_load_bitmap("joueur/Animrun1.png");
	if (!Animrun[0])
		Error("Animrun1");
	Animrun[1] = al_load_bitmap("joueur/Animrun2.png");
	if (!Animrun[1])
		Error("Animrun2");
	Animrun[2] = al_load_bitmap("joueur/Animrun3.png");
	if (!Animrun[2])
		Error("Animrun3");
	Animrun[3] = al_load_bitmap("joueur/Animrun4.png");
	if (!Animrun[3])
		Error("Animrun4");
	Animrun[4] = al_load_bitmap("joueur/Animrun5.png");
	if (!Animrun[4])
		Error("Animrun5");
	Animrun[5] = al_load_bitmap("joueur/Animrun6.png");
	if (!Animrun[5])
		Error("Animrun6");

	Animjump[0] = al_load_bitmap("joueur/Animjump1.png");
	if (!Animjump[0])
		Error("Animjump1");
	Animjump[1] = al_load_bitmap("joueur/Animjump2.png");
	if (!Animjump[1])
		Error("Animjump2");
	Animjump[2] = al_load_bitmap("joueur/Animjump3.png");
	if (!Animjump[2])
		Error("Animjump3");
	Animjump[3] = al_load_bitmap("joueur/Animjump4.png");
	if (!Animjump[3])
		Error("Animjump4");
	Animjump[4] = al_load_bitmap("joueur/Animjump5.png");
	if (!Animjump[4])
		Error("Animjump5");
	Animjump[5] = al_load_bitmap("joueur/Animjump6.png");
	if (!Animjump[5])
		Error("Animjump6");
	Animjump[6] = al_load_bitmap("joueur/Animjump7.png");
	if (!Animjump[6])
		Error("Animjump7");
	Animjump[7] = al_load_bitmap("joueur/Animjump8.png");
	if (!Animjump[7])
		Error("Animjump8");

	vignette1 = al_load_bitmap("forest1/forest1.png");
	if (!vignette1)
		Error("al_load_vignette1()");
	vignette2 = al_load_bitmap("forest2/forest2.png");
	if (!vignette2)
		Error("al_load_vignette2()");
	vignette3 = al_load_bitmap("forest3/forest3.png");
	if (!vignette3)
		Error("al_load_vignette3()");

	esheet = al_load_bitmap("esheet.bmp");
	if (!esheet)
		Error("al_load_esheet()");
	or = al_load_bitmap("or.png");
	if (!or)
		Error("al_load_or()");

	// Initialisation variables
	SCREENX = al_get_display_width(display);
	SCREENY = al_get_display_height(display);
	SCREENXD = SCREENX / 2;
	SCREENYD = SCREENY / 2;
	x = SCREENXD;
	y = SCREENYD;
}

/*******************************************
	MENU / BOUCLE
*******************************************/

void RunMenu()
{
	printf("========arrivee dans menu principal\n"); // debug
	al_flush_event_queue(queue); // Vider la file d'évènements
	Menu = 1;
	
	while (Menu) {
		dessiner = 0;

		// Récupérer les évenements
		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);

		// Evenement clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("touche presse dans boucle principale\n"); // debug
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F1: RunOptions(); break;
			case ALLEGRO_KEY_F2: RunGame(1);  break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
		}
		// Evenement souris appuit
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans la boucle principale\n", event.mouse.button); // debug
			if (SousMenu) {
				// Bouton retour
				if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
					SousMenu = 0;
				}
				// Bouton campagne
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.48)) {
					RunMenuCampagne();
				}
				// Bouton bac à sable
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.52) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.65)) {
					RunMenuSandbox();
				}
			}
			else {
				// Bouton options
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.38)) {
					Menu = 0;
					RunOptions();
					Game = 0;
				}
				// Bouton jouer
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.42) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.55)) {
					SousMenu = 1;
					Options = 0;
				}
				// Bouton quitter
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.59) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.72))
					exit(EXIT_SUCCESS);
			}
		}
		// Evenement souris relâche
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans la boucle principale\n", event.mouse.button); // debug
		}
		// Evenement souris bougé
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans boucle principale\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// Evenement timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			dessiner = 1;
		}
		// Contrôle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (dessiner == 1) {
			// Nettoyer
			al_clear_to_color(SKY);

			// Image de fond
			al_draw_scaled_bitmap(backgroundmenu, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);

			if (SousMenu) {
				// Bouton retour
				if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40)
					Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
				else
					Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");
				// Bouton campagne
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.48))
					Button(SCREENX * 0.25, SCREENY * 0.35, SCREENX * 0.75, SCREENY * 0.48, BLACK, arial72, WHITE, campagne[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.35, SCREENX * 0.75, SCREENY * 0.48, BLUE, arial72, WHITE, campagne[language]);
				// Bouton bac à sable
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.52) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.65))
					Button(SCREENX * 0.25, SCREENY * 0.52, SCREENX * 0.75, SCREENY * 0.65, BLACK, arial72, WHITE, bacasable[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.52, SCREENX * 0.75, SCREENY * 0.65, LIGHTBLUE, arial72, WHITE, bacasable[language]);
			}
			else {
				// Bouton options
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.38))
					Button(SCREENX * 0.25, SCREENY * 0.25, SCREENX * 0.75, SCREENY * 0.38, BLACK, arial72, WHITE, options[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.25, SCREENX * 0.75, SCREENY * 0.38, PURPLE, arial72, WHITE, options[language]);
				// Bouton jouer
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.42) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.55))
					Button(SCREENX * 0.25, SCREENY * 0.42, SCREENX * 0.75, SCREENY * 0.55, BLACK, arial72, WHITE, jouer[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.42, SCREENX * 0.75, SCREENY * 0.55, BLUE, arial72, WHITE, jouer[language]);
				// Bouton quitter
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.59) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.72))
					Button(SCREENX * 0.25, SCREENY * 0.59, SCREENX * 0.75, SCREENY * 0.72, BLACK, arial72, WHITE, quitter[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.59, SCREENX * 0.75, SCREENY * 0.72, LIGHTBLUE, arial72, WHITE, quitter[language]);
			}

			// Passer le double buffer à l'écran
			al_flip_display();
		}
	}
}

void RunMenuCampagne()
{
	printf("========arrivee dans menu campagne\n"); // debug
	al_flush_event_queue(queue); // Vider la file d'évènements
	MenuCampagne = 1;

	while (MenuCampagne) {
		dessiner = 0;

		// Récupérer les évenements
		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);

		// Evenement clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("touche presse dans boucle campagne\n"); // debug
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F1: MenuCampagne = 0; break;
			case ALLEGRO_KEY_F2: RunGame(1);  break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
		}
		// Evenement souris appuit
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans la boucle campagne\n", event.mouse.button); // debug
			// Bouton retour
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				MenuCampagne = 0;
			}

			// Bouton niveau 1
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.04) && my >= (SCREENY * 0.3) && mx <= (SCREENX * 0.3) && my <= (SCREENY * 0.7)) {
				RunGame(1);
			}

			// Bouton niveau 2
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.37) && my >= (SCREENY * 0.3) && mx <= (SCREENX * 0.63) && my <= (SCREENY * 0.7)) {
				RunGame(2);
			}

			// Bouton niveau 3
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.7) && my >= (SCREENY * 0.3) && mx <= (SCREENX * 0.96) && my <= (SCREENY * 0.7)) {
				RunGame(3);
			}
		}
		// Evenement souris relâche
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans la boucle campagne\n", event.mouse.button); // debug
		}
		// Evenement souris bougé
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans boucle principale\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// Evenement timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			dessiner = 1;
		}
		// Contrôle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (dessiner == 1) {
			// Nettoyer
			al_clear_to_color(SKY);

			// Image de fond
			al_draw_scaled_bitmap(backgroundmenu, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);

			// Rectangle gris
			al_draw_filled_rectangle(0, SCREENY * 0.2, SCREENX, SCREENY * 0.8, GREY);

			// Carré gauche
			if (mx >= SCREENX * 0.04 && my >= SCREENY * 0.3 && mx <= SCREENX * 0.3 && my <= SCREENY * 0.7)
				al_draw_filled_rectangle(SCREENX * 0.04, SCREENY * 0.3, SCREENX * 0.3, SCREENY * 0.7, VLIGHTGREY);
			else 
				al_draw_filled_rectangle(SCREENX * 0.04, SCREENY * 0.3, SCREENX * 0.3, SCREENY * 0.7, LIGHTGREY);
				
			al_draw_scaled_bitmap(vignette1, 0, 0, 1920, 1080, SCREENX * 0.05, SCREENY * 0.31, SCREENX * 0.24, SCREENY * 0.22, 0);
			al_draw_textf(arial72, BLACK, SCREENX * 0.17, SCREENY * 0.55, ALLEGRO_ALIGN_CENTER, "1");
			
			// Carré milieu
			if (mx >= SCREENX * 0.37 && my >= SCREENY * 0.3 && mx <= SCREENX * 0.63 && my <= SCREENY * 0.7)
				al_draw_filled_rectangle(SCREENX * 0.37, SCREENY * 0.3, SCREENX * 0.63, SCREENY * 0.7, VLIGHTGREY);
			else
				al_draw_filled_rectangle(SCREENX * 0.37, SCREENY * 0.3, SCREENX * 0.63, SCREENY * 0.7, LIGHTGREY);

			al_draw_scaled_bitmap(vignette2, 0, 0, 1920, 1080, SCREENX * 0.38, SCREENY * 0.31, SCREENX * 0.24, SCREENY * 0.22, 0);
			al_draw_textf(arial72, BLACK, SCREENX * 0.5, SCREENY * 0.55, ALLEGRO_ALIGN_CENTER, "2");
			
			// Carré droit
			if (mx >= SCREENX * 0.7 && my >= SCREENY * 0.3 && mx <= SCREENX * 0.96 && my <= SCREENY * 0.7)
				al_draw_filled_rectangle(SCREENX * 0.7, SCREENY * 0.3, SCREENX * 0.96, SCREENY * 0.7, VLIGHTGREY);
			else
				al_draw_filled_rectangle(SCREENX * 0.7, SCREENY * 0.3, SCREENX * 0.96, SCREENY * 0.7, LIGHTGREY);

			al_draw_scaled_bitmap(vignette3, 0, 0, 1920, 1080, SCREENX * 0.71, SCREENY * 0.31, SCREENX * 0.24, SCREENY * 0.22, 0);
			al_draw_textf(arial72, BLACK, SCREENX * 0.83, SCREENY * 0.55, ALLEGRO_ALIGN_CENTER, "3");

			// Bouton retour
			if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40)
				Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
			else
				Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");

			// Passer le double buffer à l'écran
			al_flip_display();
		}
	}
}

void RunMenuSandbox()
{
	printf("========arrivee dans menu sandbox\n"); // debug
	al_flush_event_queue(queue); // Vider la file d'évènements
	MenuSandbox = 1;

	while (MenuSandbox) {
		dessiner = 0;

		// Récupérer les évenements
		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);

		// Evenement clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("touche presse dans boucle sandbox\n"); // debug
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F1: MenuSandbox = 0; break;
			case ALLEGRO_KEY_F2: RunGame(0);  break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
			
		}
		// Evenement souris appuit
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans la boucle sandbox\n", event.mouse.button); // debug
			// Selection case à remplir
			int y1, y2, y3, y4;
			for (int i = 0; i < 7; i++) {
				// 1/0.26 = 3,846
				y1 = SCREENY * 1000 / 3846 + SCREENY * i * 6 / 100;
				y2 = SCREENY * 1000 / 3521 + SCREENY * i * 6 / 100;
				y3 = SCREENY * 1000 / 3496 + SCREENY * i * 6 / 100;
				y4 = SCREENY * 1000 / 3225 + SCREENY * i * 6 / 100;

				// Bouton plus
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.73) && my >= y1 && mx <= (SCREENX * 0.77) && my <= y2) {
					if (sbplus[0][i] == 57 && sbplus[1][i] == 57)
						sbplus[0][i] = 56;

					sbplus[0][i] += 1;

					if (sbplus[0][i] > 57) {
						sbplus[1][i] += 1;
						sbplus[0][i] = 48;
					}

					sbplus[2][i] = sbplus[0][i] - 48 + (sbplus[1][i] - 48) * 10;
				}

				// Bouton moins
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.73) && my >= y3 && mx <= (SCREENX * 0.77) && my <= y4) {
					if (sbplus[0][i] == 48 && sbplus[1][i] == 48)
						sbplus[0][i] = 49;

					sbplus[0][i] -= 1;

					if (sbplus[0][i] < 48) {
						sbplus[1][i] -= 1;
						sbplus[0][i] = 57;
					}

					sbplus[2][i] = sbplus[0][i] - 48 + (sbplus[1][i] - 48) * 10;
				}
				if (sbplus[0][6] > 51)
					sbplus[0][6] = 51;
				if (sbplus[0][6] < 49)
					sbplus[0][6] = 49;
			}

			// Bouton retour
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				MenuSandbox = 0;
			}
			// Bouton commencer
			if (event.mouse.button == 1 && mx >= (SCREENX * 0.55) && my >= (SCREENY * 0.70) && mx <= (SCREENX * 0.77) && my <= (SCREENY * 0.77)) {
				RunGame(0);
			}
		}
		// Evenement souris relâche
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans la boucle sandbox\n", event.mouse.button); // debug
		}
		// Evenement souris bougé
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans boucle principale\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// Evenement timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			dessiner = 1;
		}
		// Contrôle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (dessiner == 1) {
			// Nettoyer
			al_clear_to_color(SKY);

			// Image de fond
			al_draw_scaled_bitmap(backgroundmenu, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);

			// Rectangle gris
			al_draw_filled_rectangle(SCREENX * 0.2, SCREENY * 0.2, SCREENX * 0.8, SCREENY * 0.8, LIGHTGREY);

			// Texte
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.26, ALLEGRO_ALIGN_LEFT, etoile[language]);
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.32, ALLEGRO_ALIGN_LEFT, ennemi[language]);
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.38, ALLEGRO_ALIGN_LEFT, tmpsprotec[language]);
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.44, ALLEGRO_ALIGN_LEFT, vie[language]);
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.50, ALLEGRO_ALIGN_LEFT, gravite[language]);
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.56, ALLEGRO_ALIGN_LEFT, psaut[language]);
			al_draw_textf(arial32, BLACK, SCREENX * 0.25, SCREENY * 0.62, ALLEGRO_ALIGN_LEFT, niveau[language]);
			
			int y1, y2, y3, y4;
			for (int i = 0; i < 7; i++) {
				// 1/0.26 = 3,846
				y1 = SCREENY * 1000 / 3846 + SCREENY * i * 6 / 100;
				y2 = SCREENY * 1000 / 3521 + SCREENY * i * 6 / 100;
				y3 = SCREENY * 1000 / 3496 + SCREENY * i * 6 / 100;
				y4 = SCREENY * 1000 / 3225 + SCREENY * i * 6 / 100;

				// Fond blanc
				if (mx >= (SCREENX * 0.55) && my >= y1 && mx <= (SCREENX * 0.77) && my <= y4)
					al_draw_filled_rectangle(SCREENX * 0.55, y1, SCREENX * 0.77, y4, VLIGHTGREY);
				else
					al_draw_filled_rectangle(SCREENX * 0.55, y1, SCREENX * 0.77, y4, WHITE);

				// Texte
				char a = (char)sbplus[1][i];
				char b = (char)sbplus[0][i];
				if (sbplus[1][i] != 48)
					al_draw_textf(arial32, BLACK, SCREENX * 0.70, y1, ALLEGRO_ALIGN_RIGHT, &a);

				al_draw_textf(arial32, BLACK, SCREENX * 0.72, y1, ALLEGRO_ALIGN_RIGHT, &b);

				// Plus
				if (mx >= (SCREENX * 0.73) && my >= y1 && mx <= (SCREENX * 0.77) && my <= y2)
					Button(SCREENX * 0.73, y1, SCREENX * 0.77, y2, BLACK, arial22, WHITE, "+");
				else
					Button(SCREENX * 0.73, y1, SCREENX * 0.77, y2, LIGHTERGREY, arial22, BLACK, "+");

				// Moins
				if (mx >= (SCREENX * 0.73) && my >= y3 && mx <= (SCREENX * 0.77) && my <= y4)
					Button(SCREENX * 0.73, y3, SCREENX * 0.77, y4, BLACK, arial22, WHITE, "-");
				else
					Button(SCREENX * 0.73, y3, SCREENX * 0.77, y4, LIGHTERGREY, arial22, BLACK, "-");
			}

			// Bouton commencer
			if (mx >= (SCREENX * 0.55) && my >= (SCREENY * 0.70) && mx <= (SCREENX * 0.77) && my <= (SCREENY * 0.77))
				Button(SCREENX * 0.55, SCREENY * 0.70, SCREENX * 0.77, SCREENY * 0.77, BLACK, arial32, WHITE, commencer[language]);
			else
				Button(SCREENX * 0.55, SCREENY * 0.70, SCREENX * 0.77, SCREENY * 0.77, LIGHTERGREY, arial32, BLACK, commencer[language]);

			// Bouton retour
			if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40)
				Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
			else
				Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");

			// Passer le double buffer à l'écran
			al_flip_display();
		}
	}
}

/*******************************************
	OPTIONS / BOUCLE
*******************************************/

void RunOptions()
{
	printf("========arrivee dans sous menu\n"); // debug
	al_flush_event_queue(queue); // Vider la file d'évènements
	Options = 1;

	while (Options) {
		dessiner = 0;		
		
		// Récupérer les évenements
		ALLEGRO_EVENT event = { 0 };
		al_wait_for_event(queue, &event);

		// Evenement clavier
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("touche presse dans boucle sous menu\n");
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_F1: Options = 0; break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
		}
		// Evenement souris appuit
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans le sous menu\n", event.mouse.button);
			// Bouton retour
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				if (Credit) {
					Credit = 0;
				}
				else {
					RunMenu();
					Options = 0;
					Game = 0;
				}
			}
			if (Credit) {
				// Bouton fermer
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.405) && my >= (SCREENY * 0.66) && mx <= (SCREENX * 0.605) && my <= (SCREENY * 0.76)) {
					Credit = 0;
				}
			}
			else {
				// Bouton crédit
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.405) && my >= (SCREENY * 0.66) && mx <= (SCREENX * 0.605) && my <= (SCREENY * 0.76)) {
					Credit = 1;
					BSelectDisplay = 0;
					BSelectDisplay2 = 0;
				}
				// Menu déroulant résolution
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

				// Menu déroulant langage
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.35)) {
					if (BSelectDisplay2) {
						BSelectDisplay2 = 0;
					}
					else {
						BSelectDisplay2 = 1;
						BSelectDisplay = 0;
					}
				}
				// Français
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.45)) {
					if (BSelectDisplay2) {
						language = 0;
						BSelectDisplay2 = 0;
					}
				}
				// Anglais
				if (event.mouse.button == 1 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.45) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.55)) {
					if (BSelectDisplay2) {
						language = 1;
						BSelectDisplay2 = 0;
					}
				}
			}
		}
		// Evenement souris relâche
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans le sous menu\n", event.mouse.button);
		}
		// Evenement souris bougé
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans le sous menu\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// Evenement timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			dessiner = 1;
		}
		// Contrôle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (dessiner == 1) {
			// Nettoyer
			al_clear_to_color(SKY);

			// Image de fond
			al_draw_scaled_bitmap(backgroundmenu, 0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);

			// Rectangle gris au milieu
			al_draw_filled_rectangle(SCREENX * 0.2, 0, SCREENX * 0.8, SCREENY, GREY);

			// Bouton retour
			if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40)
				Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
			else
				Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");

			// Menu déroulant résolution
			if (BSelectDisplay == 1) {
				// résolution
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
				// 1920x1080
				if (mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.55) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.65))
					Button(SCREENX * 0.26, SCREENY * 0.55, SCREENX * 0.47, SCREENY * 0.65, LIGHTERGREY, arial32, LIGHTBLUE, "1920x1080");
				else
					Button(SCREENX * 0.26, SCREENY * 0.55, SCREENX * 0.47, SCREENY * 0.65, LIGHTERGREY, arial32, BLACK, "1920x1080");
			}
			else {
				if ( Credit == 0 && mx >= (SCREENX * 0.26) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.47) && my <= (SCREENY * 0.35))
					Button(SCREENX * 0.26, SCREENY * 0.25, SCREENX * 0.47, SCREENY * 0.35, BLACK, arial32, WHITE, resolution[language]);
				else
					Button(SCREENX * 0.26, SCREENY * 0.25, SCREENX * 0.47, SCREENY * 0.35, WHITE, arial32, BLACK, resolution[language]);
			}

			// Menu déroulant langage
			if (BSelectDisplay2 == 1) {
				// Langage
				if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.35))
					Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, BLACK, arial32, WHITE, lang[language]);
				else
					Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, WHITE, arial32, BLACK, lang[language]);
				// Français
				if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.45))
					Button(SCREENX * 0.53, SCREENY * 0.35, SCREENX * 0.74, SCREENY * 0.45, LIGHTERGREY, arial32, LIGHTBLUE, "Francais");
				else
					Button(SCREENX * 0.53, SCREENY * 0.35, SCREENX * 0.74, SCREENY * 0.45, LIGHTERGREY, arial32, BLACK, "Francais");
				// Anglais
				if (mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.45) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.55))
					Button(SCREENX * 0.53, SCREENY * 0.45, SCREENX * 0.74, SCREENY * 0.55, LIGHTGREY, arial32, LIGHTBLUE, "English");
				else
					Button(SCREENX * 0.53, SCREENY * 0.45, SCREENX * 0.74, SCREENY * 0.55, LIGHTGREY, arial32, BLACK, "English");
			}
			else {
				if ( Credit == 0 && mx >= (SCREENX * 0.53) && my >= (SCREENY * 0.25) && mx <= (SCREENX * 0.74) && my <= (SCREENY * 0.35))
					Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, BLACK, arial32, WHITE, lang[language]);
				else
					Button(SCREENX * 0.53, SCREENY * 0.25, SCREENX * 0.74, SCREENY * 0.35, WHITE, arial32, BLACK, lang[language]);
			}

			// Bouton crédit
			if ( Credit == 0 && mx >= (SCREENX * 0.405) && my >= (SCREENY * 0.66) && mx <= (SCREENX * 0.605) && my <= (SCREENY * 0.76))
				Button(SCREENX * 0.405, SCREENY * 0.66, SCREENX * 0.605, SCREENY * 0.76, BLACK, arial32, WHITE, "Credit");
			else
				Button(SCREENX * 0.405, SCREENY * 0.66, SCREENX * 0.605, SCREENY * 0.76, WHITE, arial32, BLACK, "Credit");
		
			if (Credit) {
				// Rectangle des crédits au milieu
				al_draw_filled_rectangle(SCREENX * 0.1, SCREENY * 0.35, SCREENX * 0.9, SCREENY * 0.7, LIGHTGREY);

				// Bouton fermer
				if (mx >= (SCREENX * 0.405) && my >= (SCREENY * 0.66) && mx <= (SCREENX * 0.605) && my <= (SCREENY * 0.76))
					Button(SCREENX * 0.405, SCREENY * 0.66, SCREENX * 0.605, SCREENY * 0.76, BLACK, arial32, WHITE, fermer[language]);
				else
					Button(SCREENX * 0.405, SCREENY * 0.66, SCREENX * 0.605, SCREENY * 0.76, WHITE, arial32, BLACK, fermer[language]);

				// Texte
				al_draw_textf(arial32, BLACK, SCREENX * 0.5, SCREENY * 0.4, ALLEGRO_ALIGN_CENTER, txtcredit1[language]);
				al_draw_textf(arial22, BLACK, SCREENX * 0.5, SCREENY * 0.5, ALLEGRO_ALIGN_CENTER, txtcredit2[language]);
				al_draw_textf(arial22, BLACK, SCREENX * 0.5, SCREENY * 0.6, ALLEGRO_ALIGN_CENTER, txtcredit3[language]);
			}

			// Passer le double buffer à l'écran
			al_flip_display();
		}
	}
}

/*******************************************
	JEU / RESET
*******************************************/

void ResetGame()
{
	// Remettre aux valeurs par défaut les variables
	PERSONNAGEMAX = 10;
	ETOILEMAX = 3;
	TICK = 30;
	life = 3;
	star = ETOILEMAX;
	Death = 0;
	protect = 2.00;
	starprotect = 0.00;
	jump = 0.00;
	pulse = 20.00;
	gravity = -2.00;
	HitboxDisplay = 0;
	ESheetDisplay = 0;
	x = SCREENXD+100; // Position du joueur
	y = SCREENYD+100;
	dx0 = 0;
	dx1 = 0;
	dx2 = 0;

	for (int i = 0; i < PERSONNAGEMAX; i++)
		personnages[i] = CreatePersonnage(RED);

	for (int i = 0; i < ETOILEMAX; i++)
		personnagesy[i] = CreatePersonnage(YELLOW);
}

/*******************************************
	JEU / BOUCLE
*******************************************/

void RunGame(int niveau)
{
	switch (niveau) {
	case 0: // sandbox
		ETOILEMAX = sbplus[2][0];
		PERSONNAGEMAX = sbplus[2][1];
		protect = (float)sbplus[2][2];
		life = sbplus[2][3];
		gravity = (float)(sbplus[2][4] * -1);
		dgravity = (float)(sbplus[2][4] * 0.1);
		pulse = (float)sbplus[2][5];
		dpulse = (float)sbplus[2][5];
		fond = sbplus[2][6];

		star = ETOILEMAX;
		Death = 0;
		starprotect = 0.00;
		jump = 0.00;
		HitboxDisplay = 0;
		ESheetDisplay = 0;
		x = SCREENXD + 100; // Position du joueur
		y = SCREENYD + 100;
		dx0 = 0;
		dx1 = 0;
		dx2 = 0;
		dx3 = 0;

		for (int i = 0; i < PERSONNAGEMAX; i++)
			personnages[i] = CreatePersonnage(RED);

		for (int i = 0; i < ETOILEMAX; i++)
			personnagesy[i] = CreatePersonnage(YELLOW);

		switch (fond) {
		case 1: // niveau 1
			background0 = al_load_bitmap("forest1/Layers/0.png");
			if (!background0)
				Error("al_load_background0()");
			background1 = al_load_bitmap("forest1/Layers/1.png");
			if (!background1)
				Error("al_load_background1()");
			background2 = al_load_bitmap("forest1/Layers/2.png");
			if (!background2)
				Error("al_load_background2()");
			background3 = al_load_bitmap("forest1/Layers/platform.png");
			if (!background3)
				Error("al_load_background3()");
			hitbox = al_load_bitmap("forest1/Layers/platformhitbox.png");
			if (!hitbox)
				Error("al_load_hitbox()");
			break;
		case 2: // niveau 1
			background0 = al_load_bitmap("forest2/Layers/0.png");
			if (!background0)
				Error("al_load_background0()");
			background1 = al_load_bitmap("forest2/Layers/1.png");
			if (!background1)
				Error("al_load_background1()");
			background2 = al_load_bitmap("forest2/Layers/2.png");
			if (!background2)
				Error("al_load_background2()");
			background3 = al_load_bitmap("forest2/Layers/platform.png");
			if (!background3)
				Error("al_load_background3()");
			hitbox = al_load_bitmap("forest2/Layers/platformhitbox.png");
			if (!hitbox)
				Error("al_load_hitbox()");
			break;
		case 3: // niveau 1
			background0 = al_load_bitmap("forest3/Layers/0.png");
			if (!background0)
				Error("al_load_background0()");
			background1 = al_load_bitmap("forest3/Layers/1.png");
			if (!background1)
				Error("al_load_background1()");
			background2 = al_load_bitmap("forest3/Layers/2.png");
			if (!background2)
				Error("al_load_background2()");
			background3 = al_load_bitmap("forest3/Layers/platform.png");
			if (!background3)
				Error("al_load_background3()");
			hitbox = al_load_bitmap("forest3/Layers/platformhitbox.png");
			if (!hitbox)
				Error("al_load_hitbox()");
			break;
		}
		break;
		
	case 1: // niveau 1
		ResetGame();
		background0 = al_load_bitmap("forest1/Layers/0.png");
		if (!background0)
			Error("al_load_background0()");
		background1 = al_load_bitmap("forest1/Layers/1.png");
		if (!background1)
			Error("al_load_background1()");
		background2 = al_load_bitmap("forest1/Layers/2.png");
		if (!background2)
			Error("al_load_background2()");
		background3 = al_load_bitmap("forest1/Layers/platform.png");
		if (!background3)
			Error("al_load_background3()");
		hitbox = al_load_bitmap("forest1/Layers/platformhitbox.png");
		if (!hitbox)
			Error("al_load_hitbox()");
		break;
	case 2: // niveau 2
		ResetGame();
		background0 = al_load_bitmap("forest2/Layers/0.png");
		if (!background0)
			Error("al_load_background0()");
		background1 = al_load_bitmap("forest2/Layers/1.png");
		if (!background1)
			Error("al_load_background1()");
		background2 = al_load_bitmap("forest2/Layers/2.png");
		if (!background2)
			Error("al_load_background2()");
		background3 = al_load_bitmap("forest2/Layers/platform.png");
		if (!background3)
			Error("al_load_background3()");
		hitbox = al_load_bitmap("forest2/Layers/platformhitbox.png");
		if (!hitbox)
			Error("al_load_hitbox()");
		break;
	case 3: // niveau 3
		ResetGame();
		background0 = al_load_bitmap("forest3/Layers/0.png");
		if (!background0)
			Error("al_load_background0()");
		background1 = al_load_bitmap("forest3/Layers/1.png");
		if (!background1)
			Error("al_load_background1()");
		background2 = al_load_bitmap("forest3/Layers/2.png");
		if (!background2)
			Error("al_load_background2()");
		background3 = al_load_bitmap("forest3/Layers/platform.png");
		if (!background3)
			Error("al_load_background3()");
		hitbox = al_load_bitmap("forest3/Layers/platformhitbox.png");
		if (!hitbox)
			Error("al_load_hitbox()");
		break;
	}

	printf("========arrivee dans jeu\n"); // debug
	al_flush_event_queue(queue); // Vider la file d'évènements
	Game = 1;
	
	while (Game) {
		dessiner = 0;

		// Récupération des événements
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		// Evenement clavier appuit
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
			case ALLEGRO_KEY_F3: if (HitboxDisplay == 1) HitboxDisplay = 0; else HitboxDisplay = 1; break;
			case ALLEGRO_KEY_F4: if (ESheetDisplay == 1) ESheetDisplay = 0; else ESheetDisplay = 1; break;
			case ALLEGRO_KEY_ESCAPE: exit(EXIT_SUCCESS); break;
			}
			printf("%d presse dans boucle jeu\n", event.keyboard.keycode); // debug
		}
		// Evenement clavier relâche
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
			printf("%d relache dans boucle jeu\n", event.keyboard.keycode); // debug
		}
		// Evenement timer
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			// spawn protection
			if (protect > 0.00)
				protect -= 0.02;

			// protection étoile
			if (starprotect > 0.00)
				starprotect -= 0.02;

			// gravitée/saut
			// en train de sauter?
			if (jump == 0)
			{
				// est au sol?
				if (c_down == 0) {
					y -= gravity;
					if (niveau == 0)
						gravity -= dgravity;
					else
						gravity -= 0.2;
					// empêche de sortir de l'écran
					if (y > SCREENY-80)
						y = SCREENY-80;
				}
			}
			else if (jump > 0)
			{
				// rien au dessus qui bloque?
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

			// Contrôles
			if (Death == 0) {
				if (key[KEY_RIGHT] == 1 && c_right == 0) {
					dx0 += 2;
					dx1 += 5;
					dx2 += 10;
					dx3 += 10;
				}
				if (key[KEY_UP] == 1 && c_down == 1 && c_up == 0) {
					jump = 1.00;
					if (niveau == 0)
						pulse = dpulse;
					else
						pulse = 10.00;
				}
				if (key[KEY_LEFT] == 1 && c_left == 0) {
					dx0 -= 2;
					dx1 -= 5;
					dx2 -= 10;
					dx3 -= 10;
				}
				if (key[KEY_DOWN] == 1 && c_down == 0) {
					y += 8;
				}
			}
			Collision(&x, &y);
			dessiner = 1;
		}
		// Evenement souris appuit
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("bouton %d presse dans le jeu\n", event.mouse.button); // debug
			if (event.mouse.button == 1 && mx >= 0 && my >= 0 && mx <= 60 && my <= 40) {
				RunMenu();
				Options = 0; // Bouton retour
				Game = 0;
			}
			if (event.mouse.button == 1 && Death == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.48)) {
				x = SCREENXD;
				y = SCREENYD; // Bouton rejouer
				RunGame(niveau);
			}
			if (event.mouse.button == 1 && Death == 1 && mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.52) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.65)) {
				Game = 0;
				Menu = 1; // Bouton menu principal
			}
		}
		// Evenement souris relâche
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("bouton %d relache dans le jeu\n", event.mouse.button); // debug
		}
		// Evenement souris bouge
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			//printf("x:%4d y:%4d dx:%4d dy:%4d z:%3d w%3d dans le jeu\n",
				//event.mouse.x, event.mouse.y, // position hori et verti
				//event.mouse.x, event.mouse.y, // mouvement hori et verti
				//event.mouse.x, event.mouse.y); // position molette verticale, hori
			mx = event.mouse.x;
			my = event.mouse.y;
		}
		// Contrôle fin du programme
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(EXIT_SUCCESS);
		}

		if (dessiner == 1)
		{
			// Nettoyer
			al_clear_to_color(SKY);

			// Images de fond
			al_draw_scaled_bitmap(background0, dx0, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background1, dx1, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background2, dx2, 0, 1920, 1080, 0, 0, SCREENX, SCREENY, 0);
			al_draw_scaled_bitmap(background3, dx3, 0, 1024, 768, 0, 0, SCREENX, SCREENY, 0);

			//défilement infini des backgrounds
			if (dx0 > 1920) {
				dx0 = 0;
			}
			if (dx0 < 0) {
				dx0 = 1920;
			}

			if (dx1 > 1920) {
				dx1 = 0;
			}
			if (dx1 < 0) {
				dx1 = 1920;
			}

			if (dx2 > 1920) {
				dx2 = 0;
			}
			if (dx2 < 0) {
				dx2 = 1920;
			}

			// Image des hitbox obstacles/sol
			if (HitboxDisplay == 1)
				al_draw_scaled_bitmap(hitbox, dx3, 0, 1024, 768, 0, 0, SCREENX, SCREENY, 0);

			// Image des hitbox d'ennemis/étoiles
			if (ESheetDisplay == 1)
				al_draw_scaled_bitmap(esheet, dx3, 0, 1024, 768, 0, 0, SCREENX, SCREENY, 0);

			// Images des coeurs
			if (life >= 1)
				al_draw_bitmap(or, 100, 0, 0);
			if (life >= 2)
				al_draw_bitmap(or, 150, 0, 0);
			if (life >= 3)
				al_draw_bitmap(or, 200, 0, 0);
			if (life >= 4)
				al_draw_bitmap(or, 250, 0, 0);
			if (life >= 5)
				al_draw_bitmap(or, 300, 0, 0);
			if (life >= 6)
				al_draw_bitmap(or, 350, 0, 0);

			// Nettoyage des anciennes images d'ennemis/étoiles
			al_set_target_bitmap(esheet);
			al_clear_to_color(BLACK);
			al_set_target_backbuffer(al_get_current_display());

			// Affichage des ennemis
			for (int i = 0; i < PERSONNAGEMAX; i++) {
				AvancePersonnage(personnages[i]);
				AffichePersonnage(personnages[i]);
			}
			// Affichage des étoiles
			for (int i = 0; i < star; i++) {
				AvancePersonnage(personnagesy[i]);
				AffichePersonnage(personnagesy[i]);
			}

			// Bouton retour
			if (mx >= 0 && my >= 0 && mx <= 60 && my <= 40)
				Button(0, 0, 60, 40, BLACK, arial32, WHITE, "<==");
			else
				Button(0, 0, 60, 40, RED, arial32, BLACK, "<==");

			// Menu de mort
			if (Death == 1)
			{
				// Rectangle gris milieu
				al_draw_filled_rectangle(SCREENX * 0.2, SCREENY*0.3, SCREENX * 0.8, SCREENY*0.7, GREY);

				// Bouton rejouer
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.35) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.48))
					Button(SCREENX * 0.25, SCREENY * 0.35, SCREENX * 0.75, SCREENY * 0.48, BLACK, arial72, WHITE, rejouer[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.35, SCREENX * 0.75, SCREENY * 0.48, BLUE, arial72, WHITE, rejouer[language]);

				// Bouton menu principal
				if (mx >= (SCREENX * 0.25) && my >= (SCREENY * 0.52) && mx <= (SCREENX * 0.75) && my <= (SCREENY * 0.65))
					Button(SCREENX * 0.25, SCREENY * 0.52, SCREENX * 0.75, SCREENY * 0.65, BLACK, arial72, WHITE, menu_p[language]);
				else
					Button(SCREENX * 0.25, SCREENY * 0.52, SCREENX * 0.75, SCREENY * 0.65, LIGHTBLUE, arial72, WHITE, menu_p[language]);
			}
			else {
				// Cube joueur
				if (protect > 0.00)
					al_draw_filled_rectangle(x, y, x + 20, y + 20, CUBEHIT);
				else if (starprotect > 0.00)
					al_draw_filled_rectangle(x, y, x + 20, y + 20, CUBEHITSTAR);
				else
					al_draw_filled_rectangle(x, y, x + 20, y + 20, CUBE);
			}

			//Animation personnage principale
			if (Death == 0) {
				if (key[KEY_RIGHT] == 1 && c_right == 0) {
					//La vitesse entre les sprits
					k += 1;
					if (k > 3) {
						l += 1;
						if (l > 5) {
							l = 0;
						}
						k = 0;
					}
					orientation = 1;
					al_draw_bitmap(Animrun[l], x + 2, y - 2, 0);
				}
				else if (key[KEY_LEFT] == 1 && c_left == 0) {
					k += 1;
					if (k > 3) {
						l += 1;
						if (l > 5) {
							l = 0;
						}
						k = 0;
					}
					orientation = 0;
					al_draw_bitmap(Animrun[l], x + 2, y - 2, ALLEGRO_FLIP_HORIZONTAL);
				}
				else if (jump > 0) {
					k += 1;
					if (k > 3) {
						l += 1;
						if (l > 7) {
							l = 0;
						}
						k = 0;
					}
					if (orientation)
						al_draw_bitmap(Animjump[l], x + 2, y - 2, 0);
					else
						al_draw_bitmap(Animjump[l], x + 2, y - 2, ALLEGRO_FLIP_HORIZONTAL);
				}
				if (key[KEY_DOWN] == 0 && key[KEY_UP] == 0 && key[KEY_LEFT] == 0 && key[KEY_RIGHT] == 0 && jump <= 0)
				{
					k += 1;
					if (k > 6) {
						l += 1;
						if (l > 3) {
							l = 0;
						}
						k = 0;
					}
					if (orientation)
						al_draw_bitmap(Animwait[l], x + 2, y - 2, 0);
					else
						al_draw_bitmap(Animwait[l], x + 2, y - 2, ALLEGRO_FLIP_HORIZONTAL);
				}
			}

			// Passer le double buffer à l'écran
			al_flip_display();
		}
	}
}

/*******************************************
	DESTRUCTION
*******************************************/

void Destroy()
{
	// Libérer la mémoire allouée
	al_destroy_event_queue(queue);
	al_destroy_font(arial32);
	al_destroy_font(arial72);
	al_destroy_bitmap(hitbox);
	al_destroy_bitmap(esheet);
	al_destroy_bitmap(background0);
	al_destroy_bitmap(background1);
	al_destroy_bitmap(background2);
	al_destroy_bitmap(background3);
	al_destroy_timer(timer);
	al_destroy_display(display);
}

/*******************************************
	OUTILS
*******************************************/

void Error(char* txt)
{
	// Afficher une fenêtre d'erreur et quitter le programme
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Error", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}

void Button(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, ALLEGRO_FONT* font, ALLEGRO_COLOR textcolor, char text[])
{
	// Rectangle du bouton
	al_draw_filled_rectangle(x1, y1, x2, y2, color);

	// Le texte du bouton
	fontsize = al_get_font_line_height(font)/2;
	al_draw_textf(font, textcolor, x1 + (x2 - x1) / 2, y1 - fontsize + ((y2-y1)/2), ALLEGRO_ALIGN_CENTER, text);
}

void Kill()
{
	// Mort si on n'a plus de vies
	if (life == 0) {
		Death = 1;
	}
	// Enlever une vie et mettre une protection pour éviter d'être touché plusieures fois en 1 seconde
	else if (protect <= 0.00) {
		life -= 1;
		protect = 2.00;
	}
}

void Collision(int* x, int* y)
{
	// Collisions sol/obstacles 
	// Objectif autoriser le déplacement ou pas
	ALLEGRO_COLOR color_down = al_get_pixel(hitbox, *x + 10+dx3, *y + 21);
	ALLEGRO_COLOR color_up = al_get_pixel(hitbox, *x + 10+dx3, *y - 15);
	ALLEGRO_COLOR color_right = al_get_pixel(hitbox, *x + 21+dx3, *y + 10);
	ALLEGRO_COLOR color_left = al_get_pixel(hitbox, *x - 1+dx3, *y + 10);

	unsigned char r, g, b;

	al_unmap_rgb(color_down, &r, &g, &b);
	c_down = 0;
	if (r == 0 && g == 128 && b == 0) {
		c_down = 1;
	}
	//printf("%d,%d,%d\n", r, g, b); // debug

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

	// Objectif détecter la collision avec un ennemi
	color_down = al_get_pixel(esheet, *x + 10, *y + 21);
	color_up = al_get_pixel(esheet, *x + 10, *y - 15);
	color_right = al_get_pixel(esheet, *x + 21, *y + 10);
	color_left = al_get_pixel(esheet, *x - 1, *y + 10);

	if (protect <= 0.00) {
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
	}

	// Objectif détécter la collision avec un allié
	if (starprotect <= 0.00) {
		al_unmap_rgb(color_down, &r, &g, &b);
		if (r == 255 && g == 200 && b == 0) {
			star -= 1;
			life += 1;
			starprotect = 1.00;
		}

		al_unmap_rgb(color_up, &r, &g, &b);
		if (r == 255 && g == 200 && b == 0) {
			star -= 1;
			life += 1;
			starprotect = 1.00;
		}

		al_unmap_rgb(color_right, &r, &g, &b);
		if (r == 255 && g == 200 && b == 0) {
			star -= 1;
			life += 1;
			starprotect = 1.00;
		}

		al_unmap_rgb(color_left, &r, &g, &b);
		if (r == 255 && g == 200 && b == 0) {
			star -= 1;
			life += 1;
			starprotect = 1.00;
		}
	}

	//printf("(%d,%d,%d)\n", r, g, b); // debug
}

Personnage* CreatePersonnage(ALLEGRO_COLOR color)
{
	Personnage* p = (Personnage*)malloc(sizeof(Personnage));
	// Localisation
	p->ey = rand() % SCREENY;  
	p->ex = rand() % SCREENX;
	
	//p->edx = (float)rand() / RAND_MAX * 50 - 25;
	//p->edy = (float)rand() / RAND_MAX * 50 - 25;

	// Taille
	p->etx = 20; 
	p->ety = 20;

	p->color = color;

	// Création d'une bitmap dans la mémoire ram
	p->im = al_create_bitmap(p->etx, p->ety);

	// Sélectionner la bitmap pour dessiner
	al_set_target_bitmap(p->im);

	// Changer la couleur de la bitmap
	al_clear_to_color(p->color);

	// Retour au double buffer pour affiche écran
	al_set_target_backbuffer(al_get_current_display());

	return p;
}

void AffichePersonnage(Personnage* p)
{
	// Dessiner la hitbox
	al_set_target_bitmap(esheet);
	al_draw_filled_rectangle(p->ex-dx3, p->ey, p->ex + 20-dx3, p->ey + 20, p->color);
	
	// Dessiner sur l'image de fond
	al_set_target_backbuffer(al_get_current_display());
	al_draw_bitmap(p->im, p->ex-dx3, p->ey, 0);
}

void AvancePersonnage(Personnage* p)
{
	// Déplacement horizontal
	p->ex += p->edx;
	if (p->ex < 0) {
		p->ex = 0;
		p->edx = ((float)rand() / RAND_MAX) * 10;
	}
	if (p->ex + p->etx >= SCREENX) {
		p->ex = SCREENX - p->etx;
		p->edx = ((float)rand() / RAND_MAX) * -5;
	}

	// Déplacement vertical
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