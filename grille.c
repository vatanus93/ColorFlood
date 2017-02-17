#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grille.h"
#include "pile.h"


grille initialize(int size)
{
	int i;
	grille plateau = NULL;
	plateau = (grille) calloc(size, sizeof(element *));
	for (i=0 ; i<size ; i++)
	{
		plateau[i] = (element *) calloc(size, sizeof(element));
	}

	return plateau;
}

void display(grille plateau, int size)
{
	int i, j;
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			printf("%2c", plateau[i][j].color);
		}
		printf("\n");
	}
	printf("\n");
}

grille random(int size)
{
	int i, j, k;
	grille plateau = initialize(size);
	srand(time(NULL));
	
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			k = rand() % 6;
			switch (k)
			{
				case 0:
				plateau[i][j].color = 'B';
				break;

				case 1:
				plateau[i][j].color = 'V';
				break;

				case 2:
				plateau[i][j].color = 'R';
				break;

				case 3:
				plateau[i][j].color = 'J';
				break;

				case 4:
				plateau[i][j].color = 'M';
				break;

				case 5:
				plateau[i][j].color = 'G';
				break;
			}
			plateau[i][j].appartenance=0;
		}
	}
	return plateau;
}

grille change_color(int i, int j, char c, grille plateau)
{
	plateau[i][j].color = c;
	return plateau;
}

bool if_flood(grille plateau, int size)
{     
	int i, j; 
	bool res = 1;
	for(i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{   
			if(plateau[0][0].color != plateau[i][j].color)
			{
				return res = 0;
			}
		}
	}
	return res;
}

void free_space(grille plateau, int size)
{
	int i;
	for (i=0 ; i<size ; i++)
	{
		free(plateau[i]);
	}
	free(plateau);
}

/*
Pile extraire_fils(coordonnees pere, Pile P, char couleur_choisie, grille plateau, int size) 
{
	Pile res = P;

	int i = pere.x;
	int j = pere.y;
	char c = plateau[i][j].color;

	coordonnees fils_gauche, fils_droite, fils_haut, fils_bas;

	fils_gauche.x = i;
	fils_gauche.y = j-1;

	fils_droite.x = i;
	fils_droite.y = j+1;

	fils_haut.x = i-1;
	fils_haut.y = j;

	fils_bas.x = i+1;
	fils_bas.y = j;


	if ( j != 0 && (plateau[i][j-1].color == c || plateau[i][j-1].color == couleur_choisie) )
	{
		if (plateau[i][j-1].appartenance != 1)
			res = empiler(res, fils_gauche);
	}

	if ( j != size-1 && (plateau[i][j+1].color == c || plateau[i][j+1].color == couleur_choisie) )
	{
		if (plateau[i][j+1].appartenance != 1)
			res = empiler(res, fils_droite);
	}

	if ( i != 0 && (plateau[i-1][j].color == c || plateau[i-1][j].color == couleur_choisie) )
	{
		if (plateau[i-1][j].appartenance != 1)
			res = empiler(res, fils_haut);
	}

	if ( i != size-1 && (plateau[i+1][j].color == c || plateau[i+1][j].color == couleur_choisie) )
	{
		if (plateau[i+1][j].appartenance != 1)
			res = empiler(res, fils_bas);
	}

	return res;
}
*/

/*
Pile identifier_tache(grille plateau, char couleur_choisie, int size)
{
	Pile resultat, pile_des_fils;
	coordonnees pere;

	pere.x = 0; 
	pere.y = 0;

	resultat = pile_initialiser(); 

	pile_des_fils = pile_initialiser(); 
	pile_des_fils = empiler(pile_des_fils, pere);

	while( !pile_estVide(pile_des_fils) )
	{
		pere = pile_des_fils->tete;

		(plateau[pere.x][pere.y]).appartenance = 1; 
		resultat = empiler(resultat, pere); 
		pile_des_fils = depiler(pile_des_fils); 

		pile_des_fils = extraire_fils(pere, pile_des_fils, couleur_choisie, plateau, size); 
	}

	return resultat;
}
*/
int test_neighbour(grille plateau, coordonnees coord, int size, char couleur_choisie)
{
	int test=0;
	int i=coord.x;
	int j=coord.y;
	if (i!=0 && i!=size-1 && j!=0 && j!= size-1)
	{
		if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
			return test=1;

		if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
			return test=2;

		if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
			return test=3;

		if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
			return test=4;
	}
	if (i==0)
	{
		if (j==0)
		{
			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;
		}
		if (j==size-1)
		{
			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
		if(j!=0 && j!= size-1)
		{
			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
	}
	if (i==size-1)
	{
		if (j==0)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;
		}
		if (j==size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
		if (j !=0 && j!= size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
	}
	if (j==0)
	{
		if (i==0)
		{
			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;
		}
		if (i==size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;
		}
		if (i!=0 && i!= size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				return test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;
		}
	}
	if (j==size-1)
	{
		if(i==0)
		{
			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
		if(i==size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
		if (i!=0 && i!=size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				return test=1;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				return test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				return test=4;
		}
	}
	return 0 ;
}


void modif_color(char couleur_choisie, grille plateau, int size)
{
	coordonnees position;

	Pile P = NULL;

	int i,j;

	for (i=0 ; i<size ;i++)
	{
		for (j=0 ; j<size ; j++)
		{
			position.x = i; 
			position.y = j;
			if(plateau[i][j].appartenance==1)
			{
				change_color(i,j,couleur_choisie,plateau);
				P=empiler(P,position);
				while(pile_estVide(P)!=1)
				{
					position = P->tete; 
					P=Deep(couleur_choisie, plateau, size, position, P);
					P=depiler(P);
				}
			}
		}
	}

}

Pile Deep(char couleur_choisie, grille plateau, int size, coordonnees position_pere, Pile P)
{
	coordonnees position_fils;
	switch (test_neighbour(plateau, position_pere, size, couleur_choisie))
	{
		case 0:
		break;
		case 1:
		{
			position_fils.x=position_pere.x-1;
			position_fils.y=position_pere.y;
			plateau[position_fils.x][position_fils.y].appartenance=1;
			P=empiler(P,position_fils);
			P=Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 2:
		{
			position_fils.x=position_pere.x;
			position_fils.y=position_pere.y+1;
			plateau[position_fils.x][position_fils.y].appartenance=1;
			P=empiler(P,position_fils);
			P=Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 3:
		{
			position_fils.x=position_pere.x+1;
			position_fils.y=position_pere.y;
			plateau[position_fils.x][position_fils.y].appartenance=1;
			P=empiler(P,position_fils);
			P=Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 4:
		{
			position_fils.x=position_pere.x;
			position_fils.y=position_pere.y-1;
			plateau[position_fils.x][position_fils.y].appartenance=1;
			P=empiler(P,position_fils);
			P=Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}
	}
	return P;
}