#include "rechercheTabou.h"

using namespace std;

// Initialisation des param�tres de la RechercheTabou
// et g�n�ration de la solution initiale.
// Initialisation  de la liste tabou
rechercheTabou::rechercheTabou(int nbiter,int dt,int nv, char* nom_fichier)
{
  nbiterations    = nbiter;
  iter_courante   = 0;
  duree_tabou     = dt;
  taille_solution = nv;
  constuction_distance(taille_solution, nom_fichier);
  courant         = new solution(nv);
  courant->evaluer(les_distances);

  list_tabou = new int*[nv];
  for(int i=0; i<nv; i++)
    {
      list_tabou[i] = new int[nv];
      for(int j=0; j<nv; j++)
	list_tabou[i][j] = -1;
    }

  cout << "La solution initiale aleatoire est   : ";
  courant->afficher();

  list_tabou2 = new int*[duree_tabou];
  for(int i=0; i<duree_tabou; i++)
    {
      list_tabou2[i] = new int[taille_solution];
      for(int j=0; j<taille_solution; j++)
	list_tabou2[i][j] = -1;
    }
}

rechercheTabou::~rechercheTabou()
{
  delete courant;
  for(int i=0; i<taille_solution; i++)
    {
      delete list_tabou[i];
      delete les_distances[i];
    }
  for(int i=0; i<duree_tabou; i++)
    delete list_tabou2[i];
  delete[] list_tabou;
  delete[] list_tabou2;
  delete[] les_distances;
}

void rechercheTabou::constuction_distance(int nv, char* nom_fichier)
{
  les_distances = new int*[nv];
  for(int i=0; i<nv; i++)
    les_distances[i] = new int[nv];

  ifstream fichier;
  // Ouvre le fichier des distances entre villes
  fichier.open(nom_fichier, ifstream::in);
  if(!fichier.is_open())
    {
      cerr<<"Fichier [" << nom_fichier << "] invalide."<<endl;
      exit(-1);
    }

  for (int i=0; i<nv; i++)
    {
      for(int j=i+1; j<nv; j++)
	{
	  fichier >> les_distances[i][j];
	  les_distances[j][i] = les_distances[i][j];
	}
    }

  for (int i=0; i<nv; i++)
    les_distances[i][i] = -10;

  fichier.close();
}

bool rechercheTabou::nonTabou(int i, int j)
{
  if(list_tabou[i][j]<iter_courante)
    return true;
  else
    return false;
}

bool rechercheTabou::nonTabou2(solution* sol)
{
  for(int i=0; i<duree_tabou; i++)
    {
      for(int j=1; j<taille_solution; j++)
	{
	  if (list_tabou2[i][j]!=sol->ville[j])
	    j = taille_solution;
	  else if (j == taille_solution-1)
	    return false;
	}
    }
  for(int i=0; i<duree_tabou; i++)
    {
      for(int j=1; j<taille_solution; j++)
	{
	  if (list_tabou2[i][j]!=sol->ville[taille_solution-j])
	    j = taille_solution;
	  else if (j == taille_solution-1)
	    return false;
	}
    }
  return true;
}

void rechercheTabou::mise_a_jour_liste_tabou_2(solution* sol, int&position)
{
  if (duree_tabou != 0)
    {
      for(int j=0; j<taille_solution; j++)
	list_tabou2[position][j] = sol->ville[j];
      position++;
      if (position == duree_tabou)
	position = 0;
    }
}

void rechercheTabou::voisinage_2_opt(int &best_i, int &best_j)
{
  int best_vois;
  bool tous_tabou = true;
  best_vois = 100000;

  // on s�l�ctionne une premi�re ville pour le mouvement
  for(int i=0;i<taille_solution;i++)
    {
      // on s�l�ctionne une seconde ville pour le mouvement
      for(int j=i+1;j<taille_solution;j++)
	{
	  if(   ((i!=0)||(j!=taille_solution-1))
		&& ((i!=0)||(j!=taille_solution-2)) )
            {
	      // on transforme la solution courante vers le voisin
	      //    gr�ce au mouvement d�finit par le couple de ville
	      courant->inversion_sequence_villes(i,j);
	      // on estime ce voisin
	      courant->evaluer(les_distances);
	      // si ce mouvement est non tabou et
	      // si ce voisin a la meilleure fitness
	      // alors ce voisin devient le meilleur voisin non tabou
	      if(nonTabou(i,j) && courant->fitness<best_vois)
                //if(nonTabou2(courant) && courant->fitness<best_vois)
                {
		  best_vois  = courant->fitness;
		  best_i     = i;
		  best_j     = j;
		  tous_tabou = false;
                }
	      // on re-transforme ce voisin en la solution courante
	      courant->inversion_sequence_villes(i,j);
	      // on r�-�value la solution courante
	      courant->evaluer(les_distances);
            }
	}
    }
}

//proc�dure principale de la recherche
solution* rechercheTabou::optimiser()
{
  bool first            = true; // indique si c'est la premiere fois
  //         que l'on est dans un mimium local
  bool descente         = false;// indique si la solution courzntz corresponds � une descente
  int ameliore_solution = -1;   // indique l'iteration o� l'on a am�lior� la solution
  int f_avant, f_apres;         // valeurs de la fitness avant et apr�s une it�ration

  // La meilleure solution trouv�e (= plus petit minium trouv�) � conserver
  solution* best_solution = new solution(taille_solution);


  int best_i    = 0;            // Le couple (best_i, best_j) repr�sente le meilleur mouvement non tabou
  int best_j    = 0;
  int best_eval = courant->fitness;
  f_avant       = 10000000;

  // Tant que le nombre d'it�rations limite n'est pas atteint
  for(iter_courante=0; iter_courante<nbiterations; iter_courante++)
    {
      voisinage_2_opt(best_i, best_j);            // La fonction 'voisinage_2_opt' retourne le meilleur
      //   mouvement non tabou; c'est le couple (best_i, best_j)
      courant->inversion_sequence_villes(best_i, best_j);
      //  On d�place la solution courante gr�ce � ce mouvement

      courant->ordonner();                        // On r�ordonne la solution en commen�ant par 0
      courant->evaluer(les_distances);            // On �value la nouvelle solution courante

      f_apres = courant->fitness;                 // valeur de la fitness apres le mouvement

      if(courant->fitness < best_eval)            // si on am�liore le plus petit minimum rencontr�
	{                                           // alors on l'enregistre dans 'best_solution'
	  best_eval = courant->fitness;           // on mets � jour 'best_eval'
	  best_solution->copier(courant);         // on enregistre la solution corante comme best_solution
	  best_solution->evaluer(les_distances);  // on �value la best solution
	  ameliore_solution = iter_courante;      // on indique que l'am�lioration � eu lieu � cette it�ration
	}
      else // Si on n'est pas dans le plus petit minimum rencontr� mais dans un minimum local
	{
	  // Crit�res de d�tection d'un minimum local. 2 cas:
	  //  1. si la nouvelle solution est + mauvaise que l'ancienne
	  //         et que on est en train d'effectuer une descente
	  //  2. si la nouvelle solution est identique � l'ancienne
	  //         et que c'est la premi�re fois que cela se produit
	  if (    ((f_avant<f_apres)&&(descente==true))
		  || ((f_avant == f_apres)&&(first)) )
            {
	      
	      cout << "On est dans un minimum local a l'iteration "
		   << iter_courante-1 << " -> min = " << f_avant
		   << " km (le + petit min local deja trouve = "
		   << best_eval << " km)" << endl;
	      first = false;
            }

	  if (f_avant<=f_apres)  // la solution courente se d�grade
	    descente = false;
	  else
	    descente = true;   // la solution courante s'am�liore : descente

	  if ((f_avant!=f_apres)&&(!first)) //
	    first = true;



			
        }


      

      // mise � jour de la liste tabou
      list_tabou[best_i][best_j] = iter_courante+duree_tabou;
      //mise_a_jour_liste_tabou_2(courant, position);
      f_avant = f_apres; 

      // output: index of iteration and the optimal solution so far en C
      printf("%d\t%d\t%d\n", iter_courante, courant->fitness, best_eval);
    }
  return best_solution;
}
