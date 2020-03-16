
#ifndef SOLUTION_H
#define SOLUTION_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "random.h"

// La classe solution represente la structure
// d'une solution du probleme du voyageur de commerce
class solution{
public:
	// ATTRIBUTS
	int *ville;                  // les variables de la solution
	int taille;                  // la taille du solution
	int fitness;                 // la valeur de fitness de la solution = longueur de la boucle

	// CONSTRUCTEURS
	solution(int nv);
	~solution();

	// METHODES
	void evaluer(int **distance);     // fonction d'�valuation de la solution (c-�-d calcul la fitness)
                                      //   Elle doit etre lanc�e � la creation des solution et apres
                                      //   l'ex�cution des operateurs de mutation et de croisement
	void afficher();                  // fonction affichant la solution
	void ordonner();                  // ordonne le sens de la tourn�e si ville[1] > ville[taille-1]
	void copier(solution* source);    // copie la solution 'source'
	bool identique(solution* chro);   // test si 2 solutions sont identiques
	void echange_2_villes(int ville1, int ville2);          // interchange 2 villes de la solution
	void inversion_sequence_villes(int ville1, int ville2); // inverse une s�quence de villes de la solution
	void deplacement_1_ville(int ville1, int ville2);       // d�place un ville dans la solution

};

# endif

