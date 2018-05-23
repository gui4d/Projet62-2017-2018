#ifndef _TRAITEMENT
#define _TRAITEMENT
typedef struct{int l;int c;} COUPLE;
typedef struct{int inf;int sup;} BORNES;

int nb_erreurs_image(unsigned int** matrice);
  //Compte le nombre de pixels aberants dans l'image

unsigned int** moyenne_matrice(unsigned int*** tab_matrice,int nb_matrice);
  //Cree une matrice correspondant a la moyenne des matrices du tableau. Lesvaleurs aberantes ne sont pas prises en compte

unsigned int** profondeur_to_altitude(unsigned int** matrice_profondeur,int nl,int nc);
  //Cree une matrice et realise la transformation pour passer de mesures de profondeur a celle d'altitude

COUPLE calcul_gradient_point(unsigned int** matrice,int i,int j);
  //Calcule le gradient en 1 point

COUPLE** cree_matrice_gradient(unsigned int** matrice);
  //Cree une matrice ou chaque element correspond au gradient en ce point

int calcul_gradient_ligne(COUPLE** matrice_gradient,int numero,char mode);
  //Somme le gradient d'une ligne ou d'une colonne dans la direction opposee

int calcul_gradient_droite(COUPLE** matrice_gradient,COUPLE p1,COUPLE p2);
//Somme le gradient d'un droite quelconque

int trouve_bord_haut(COUPLE** matrice_gradient);
//Trouve la ligne ou le gradient est minimal dans la moitie haute

int trouve_bord_bas(COUPLE** matrice_gradient);
//Trouve la ligne ou le gradient est minimal dans la moitie basse

int trouve_bord_gauche(COUPLE** matrice_gradient);
//Trouve la colonne ou le gradient est minimal dans la partie gauche

int trouve_bord_droit(COUPLE** matrice_gradient);
//Trouve la colonne ou le gradient est maximal dans la partie droite


#endif
