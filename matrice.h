#include<SDL2/SDL.h>
#include"traitement.h"
#define maxint 65535

unsigned int** alloueMatriceInt(int nl,int nc);
////Realise l'allocation dynamique d'une matrice de taille nl*nc

void libereMatrice(void** matrice);
//Realise la liberation memoire d'un matrice cree avec alloueMatriceInt

unsigned int trouveMaximunI(unsigned int ** matrice, int nl, int nc);
//Renvoie l'element maximum d'une matrice de taille nl*nc

unsigned int trouveMinimunI(unsigned int** matrice, int nl, int nc);
//Renvoie l'element minimum d'une matrice de taille nl*nc

int visualiseMatriceInt(unsigned int** matrice, int nl, int nc);
/*Cree une fenetre SDL representant la matrice de taille nl*nc en niveaux de gris
Le noir correspond à des valeurs importantes et le blanc à des valeurs faibles
Retourne non zero en cas d'erreur */

int indice_max(int* tab,int debut,int fin);
//Cherche l'indice de l'element maximum entre l'indice de debut inclu et l'indice de fin exclu

int indice_min(int* tab,int debut,int fin);
//Cherche l'indice de l'element minimum entre l'indice de debut inclu et l'indice de fin exclu

void visualise_image_kinect(unsigned int** matrice,COUPLE p1,COUPLE p2);//inutile

void dessine_rectangle(SDL_Renderer* pRenderer,COUPLE haut_gauche,COUPLE haut_droit,
		       COUPLE bas_droit,COUPLE bas_gauche);
//Dessine un rectangle en reliant les point sur le renderer en parametre

int est_dans_trapeze(int i,int j,COUPLE haut_gauche,COUPLE haut_droit,COUPLE bas_droit,
		      COUPLE bas_gauche);
//Retourne 1 si le point de coordonee i j est dans le trapeze delimite par les quatres points donnes, 0 sinon


void recupere_calibrage_manuel(COUPLE* haut_gauche,COUPLE* haut_droit,
			       COUPLE* bas_droit,COUPLE* bas_gauche);
//Fonction recupererant les coordonnees de 4 points ou la souris clique et realisant un traitement pour obtenir un trapèze adéquat

unsigned int** recopie_matrice(unsigned int** matrice,COUPLE haut_gauche,
			       COUPLE haut_droit,COUPLE bas_droit,COUPLE bas_gauche);
//Cree une matrice afin de recopier les information se trouvant dans le trapeze delimite par les point en parametre

void calibrage_manuel(unsigned int** matrice, COUPLE* haut_gauche,COUPLE* haut_droit,
		      COUPLE* bas_droit,COUPLE* bas_gauche);
//Fonction permettant le calibrage manuel sur une matrice donnee

unsigned int** remplace_matrice(unsigned int** matrice,int nl_init,int nc_init,
				int nl_cible,int nc_cible);
unsigned int** retouche_matrice(unsigned int** matrice,int nl ,int nc);
void completter_matrice(unsigned int** matrice_cible, unsigned int** matrice_marqueurs,int nl,int nc);
