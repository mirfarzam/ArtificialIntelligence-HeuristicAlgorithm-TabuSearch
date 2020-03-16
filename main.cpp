#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "random.h"
#include "rechercheTabou.h"
#include "solution.h"

using namespace std;

int main(int argc, char **argv)
// argc : nombre de parametres
// argv : tableau contenant les parametres
// Soit l'executable 'algo_tabou' ne prend pas d'arguments soit il prend 4 arguments :
//   1.  nombre d'itéreation (critère d'arret de l'algo)
//   2.  durée de la liste Tabou
//   3.  nombre de villes
//   4.  nom du fichier indiquant les distances entre villes
{
	//initialise le générateur de nombre aléatoire
	Random::randomize();

	// valeurs par defaut
	int nb_iteration = 10;
	int duree_tabou  = 0;
	int nb_villes    = 10;
	char fileDistances[100];
	strcpy(fileDistances,"distances_entre_villes_10.txt");

	if (argc == 5)
	{
		nb_iteration = atoi(argv[1]);
		duree_tabou  = atoi(argv[2]);
		nb_villes    = atoi(argv[3]);
		strcpy(fileDistances,argv[4]);
	}
	else if (argc == 1)
	{
		cout << "Parametres par default" << endl;
	}
	else
	{
		cout << "Nombre d'arguments n'est pas correct." << endl;
		cout << "Soit l'executable 'algo_tabou' ne prend pas d'arguments soit il prend 4 arguments : " << endl;
		cout << "   1. nombre d'iteration (entier > 0)" << endl;
		cout << "   2. duree Tabou (entier > 0)" << endl;
		cout << "   3. nombre de villes (=taille de la solution)" << endl;
		cout << "   4. nom du fichier indiquant les distances entre villes" << endl;
		exit(EXIT_FAILURE);
	}

	// Intialise les paramètre de la RechercheTabou et crée la solution initiale
	rechercheTabou algo(nb_iteration, duree_tabou, nb_villes, fileDistances);
	//   1ier  paramètre : nombre d'itéreation (critère d'arret de l'algo)
	//   2ième paramètre : durée de la liste Tabou
	//   3ième paramètre : nombre de villes
	//   4ième paramètre : fichier contenant les disantances entre les villes

	// Lance la recherche avec la méthode Tabou
	solution* best = algo.optimiser();
	// Affiche la meilleure solution rencontrée
	cout << endl << "la meilleure solution rencontrée est : ";
	best->afficher();

	delete best;

	return 0;
}
