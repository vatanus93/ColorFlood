/**
 * \file pile.h
 * \brief Stucture de pile (implémentation à l'aide de liste chainée) + Fonctions de bases.
 * 															 
 * \author THOR
 * \date février 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "coordonnees.h"

#ifndef PILE_H
#define PILE_H

#define type_element coordonnees 

/**
 * \struct liste
 * \brief Structure d'une liste
 *
 * Une liste est définie par un élément en tête (ici une case donc de type coordonnees),
 * ainsi que par son reste.
 */
typedef struct liste
{
    type_element tete;
    struct liste * suivant;
} Cellule, *Pile;


/**
 * \fn Pile pile_initialiser()
 * \brief créer une pile vide.
 *
 * \return NULL.
 */
Pile pile_initialiser();

/**
 * \fn int pile_estVide(Pile P)
 * \brief tester si la pile est vide ou pas.
 *
 * \param P la pile que l'on test.
 * \return 1 si elle est vide, 0 sinon.
 */
int pile_estVide(Pile P);


/**
 * \fn Pile empiler(Pile P, coordonnees elem)
 * \brief Empiler : ajout d'un élément au sommet 
 *
 * \param P la pile qui va être empilée.
 * \param elem la coordonnée que l'on souhaite empiler.
 * \return La pile avec le nouvel élément en tête.
 */
Pile empiler(Pile P, coordonnees elem);

/**
 * \fn Pile depiler(Pile P)
 * \brief Dépiler : supprimer le sommet
 *
 * \param P la pile qui va être dépilée.
 * \return NULL si la pile est déjà vide, la pile avec un élément de moins sinon.
 */
Pile depiler(Pile P);

/**
 * \fn int pile_taille(Pile P)
 * \brief Délivrer la taille de la pile.
 *
 * \param P la pile dont on souhaite connaître la taille.
 * \return La taille de la pile.
 */
int pile_taille(Pile P);


#endif
