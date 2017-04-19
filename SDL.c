#include "SDL.h"


void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
{
	SDL_Rect rect;
	rect.y=px;
	rect.x=py;
	rect.h=rect.w=size;
	SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
}

void fillScreen(SDL_Surface *ecran, RGB couleur)
{
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);	/*MàJ de l'écran*/
}

SDL_Surface *menu(TTF_Font *police1, TTF_Font *police2, int *size, int *difficulte)
{
	SDL_Surface *ecran, *texte1, *texte2, *texte3, *texte4,*fond;
	SDL_Event event;
	SDL_Rect position1, position2, position3, position4, positionFond;
	SDL_Color couleur_texte = {255, 255, 255, 42};

	int continuer = 1, compteur = 3, niveau = 1;
	char compteur_txt[50], niveau_txt[50];

	positionFond.x = 0;
	positionFond.y = 0;

	position1.x = 1;
	position1.y = 5;
	position4.x = 1;
	position4.y = 30;
	position2.x = 5;
	position2.y = 120;
	position3.x = 39;
	position3.y = 220;

	ecran = SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE); /*fenêtre au début à cette taille par défaut*/
	fond = SDL_LoadBMP("fond2.bmp");
	SDL_BlitSurface(fond, NULL, ecran, &positionFond);
	SDL_Flip(ecran);
	SDL_WM_SetCaption("Menu ColorFlood", NULL);
	
	texte1 = TTF_RenderUTF8_Blended(police1, "Flèches 'gauche/droite' : difficulté.", couleur_texte);
	texte4 = TTF_RenderUTF8_Blended(police1, "Flèches 'haut/bas' : taille. Puis 'espace'", couleur_texte);
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
			*size = 0;
			continuer = 0;
			break;
			
			case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				*size = 0;
				continuer = 0;
				break;

					case SDLK_UP: // Flèche haut
					if (compteur < 24) /* pour le solveur */
					compteur ++;
					break;

					case SDLK_DOWN: // Flèche bas
					if (compteur > 3)
						compteur --;
					break;

					case SDLK_RIGHT:
					if (niveau < 3)
						niveau++;
					break;

					case SDLK_LEFT:
					if (niveau > 1)
						niveau--;
					break;

					case SDLK_SPACE:
					*size = compteur;
					*difficulte = niveau;
					continuer = 0;
					break;

					default:
					break;
				}
				break;
			}
			sprintf(compteur_txt, "Taille choisie : %d", compteur);
			texte2 = TTF_RenderUTF8_Blended(police2, compteur_txt, couleur_texte);
			sprintf(niveau_txt, "Difficulté : %d", niveau);
			texte3 = TTF_RenderUTF8_Blended(police2, niveau_txt, couleur_texte);

			SDL_BlitSurface(fond, NULL, ecran, &positionFond);
			SDL_BlitSurface(texte1, NULL, ecran, &position1);
			SDL_BlitSurface(texte2, NULL, ecran, &position2);
			SDL_BlitSurface(texte3, NULL, ecran, &position3);
			SDL_BlitSurface(texte4, NULL, ecran, &position4);
			SDL_Flip(ecran);
		}

	SDL_FreeSurface(texte1); //libération de mémoire
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(texte3);
	SDL_FreeSurface(texte4);

	return ecran;
}


SDL_Surface *initialize_screen(int size_window)
{
	SDL_Surface *ecran = NULL;
	
	RGB init_screen = {255, 255, 255};	//blanc

	ecran = SDL_SetVideoMode(size_window, size_window+200, 8, SDL_HWSURFACE);
	/* nom de la fenêtre */
	SDL_WM_SetCaption("Color Flood (THOR)", NULL);
	/* écran tout blanc */
	fillScreen(ecran, init_screen);

	return ecran;
}

void initialize_text(SDL_Surface *ecran, char *nbr_coup_texte, TTF_Font *police)
{
	SDL_Rect position1, position2, position3;
	SDL_Color texteNoir = {0, 0, 0, 42}, fondBlanc = {255, 255, 255, 42};	/* 4ème paramètre inutile */
	SDL_Surface *texte1, *texte2, *texte3;

	texte1 = TTF_RenderUTF8_Shaded(police, "Pour jouer : taper 'B', 'V', 'R', 'J', 'M' ou 'G'.", texteNoir, fondBlanc);
	texte2 = TTF_RenderUTF8_Shaded(police, "Pour le solveur : taper 'S'. Pour quitter : taper 'échap'.", texteNoir, fondBlanc);
	texte3 = TTF_RenderUTF8_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);

	position1.x = 5;
	position1.y = 610;
	position2.x = 5;
	position2.y = 660;
	position3.x = 5;
	position3.y = 510;

	SDL_BlitSurface(texte1, NULL, ecran, &position1);
	SDL_BlitSurface(texte2, NULL, ecran, &position2);
	SDL_BlitSurface(texte3, NULL, ecran, &position3);
	
	SDL_FreeSurface(texte1);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(texte3);
}

void display_SDL(SDL_Surface *ecran, grille plateau, int size, int size_window)
{
	RGB J = {255, 215, 0};
	RGB R = {219, 23, 2};
	RGB G = {127, 127, 127};
	RGB V = {1, 215, 88};
	RGB B = {0, 127, 255};
	RGB M = {128, 0, 128};
	int i, j;
	char couleur;

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			couleur = plateau[i][j];
			switch (couleur)
			{
				case 'B':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, B);
				break;

				case 'V':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, V);
				break;

				case 'R':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, R);
				break;

				case 'J':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, J);
				break;

				case 'M':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, M);
				break;

				case 'G':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, G);
				break;
			}
		}

	}
	SDL_Flip(ecran);
}
int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police, int size_window)
{
	int continuer = 1, nbr_coup = 0;
	SDL_Surface *texte;
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42}, fondBlanc = {255, 255, 255, 42};
	SDL_Rect position;
	position.x = 5;
	position.y = 510;

	int nbr_coups_min;
	char* chemin;
	bool flip = true;
	while(if_flood(plateau, size) != 1 && nbr_coup < nbr_coups_max && continuer)
	{
		char ancienne_couleur = plateau[0][0];
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
			continuer = 0;
			break;

			case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x = event.button.x * size / size_window;
				int y = event.button.y * size / size_window;
				if(x >= 0 && x < size && y >= 0 && y < size)
				{
					if(plateau[y][x] != ancienne_couleur)
					{
						modif_color(0,0, plateau[y][x], ancienne_couleur, plateau, size);
						nbr_coup++;
						flip = true;
					}
				}
			}break;

			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_s:
				printf("Solveur en cours...\n");
				chemin = solveur_perf(plateau, size, &nbr_coups_min);
				printf("[%s] en %d coups.\n", chemin, nbr_coups_min);
				free(chemin);
				break;

				case SDLK_ESCAPE:
				continuer = 0;
				break;

				default:
				break;
			}
		}

		if(flip)
		{
			flip = false;
			sprintf(nbr_coup_texte, "Nombre de coups : %d/%d", nbr_coup, nbr_coups_max);
			texte = TTF_RenderUTF8_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);
			SDL_BlitSurface(texte, NULL, ecran, &position);
			display_SDL(ecran, plateau, size,size_window);
			SDL_Flip(ecran);
			SDL_FreeSurface(texte);
		}
	}
	return nbr_coup;
}
void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police)
{
	SDL_Color texteNoir = {0, 0, 0, 42};

	SDL_Surface *texte = NULL;
	SDL_Rect position;

	if (nbr_coup >= nbr_coups_max && if_flood(plateau, size) == 0)
	{
		texte = TTF_RenderUTF8_Blended(police, "GAME OVER", texteNoir);
		position.x = 110;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(4);
	}
	if (if_flood(plateau, size) == 1)
	{
		texte = TTF_RenderUTF8_Blended(police, "WIN", texteNoir);
		position.x = 190;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(2);
	}	
	SDL_FreeSurface(texte);
}