
#ifndef _RT_H
#define _RT_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include "random.h"
#include "solution.h"

// cette classe d�finie les param�tres d'une ex�cution
// de la recherche tabou ainsi que la proc�dure principale de recherche
class rechercheTabou{
public:
	// ATTRIBUTS
	int iter_courante;
	int nbiterations;              // nombre d'it�rations apr�s quoi la recherche est arr�t�e
	int duree_tabou;               // dur�e tabou en nombre d'it�rations
	int taille_solution;           // nombre de villes dans le solution
	solution *courant;             // solution courante g�r�e par la RechercheTabou
	int **list_tabou2;             // taboo solution list
	int **list_tabou;              // list of dur�es taboo associ�es � each couple of cities

	int alphaTabu;
	int constantTabu;
	double meanTabuDuration;

	int **list_actions;
	int *list_first_city;
    int *list_second_city;
    double *list_mean_city;

	int **les_distances;           // matrice des distances entre les villes	                                                 // le voisinage est au sens voisinage 2-opt

	// CONSTRUCTEURS
	rechercheTabou(int nbiter, int dt, int nv, int alphaT, int constantT,  char* nom_fichier);  // construction de la rechercheTabou
	~rechercheTabou();

	// METHODES
	bool nonTabou(int i,int j);                      // le couple (ville i, ville j) est tabou : oui ou non
	bool nonTabou2(solution* sol);                   // la solution 'sol' est tabou : oui ou non
	void voisinage_2_opt(int& best_i, int &best_j);  // donne le meilleur voisinage non tabou
	solution* optimiser();                           // lancement de la rechercheTabou
	void constuction_distance(int nv, char* nom_fichier);
	void mise_a_jour_liste_tabou_2(solution* sol, int& position);
	                                                 // ajout de la solution 'sol' � la position 'position'
	                                                 //  de la liste tabou
	int rangeTabuDynamicDuration();
	int frequencyTabuDynamicDurationV1(int i, int j);
	int frequencyTabuDynamicDurationV2(int i);
};

# endif
