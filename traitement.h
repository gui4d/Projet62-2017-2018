#ifndef _TRAITEMENT
#define _TRAITEMENT
typedef struct{int l;int c;} COUPLE;
typedef struct{int inf;int sup;} BORNES;

int nb_erreurs_image(unsigned int** matrice);
unsigned int** moyenne_matrice(unsigned int*** tab_matrice,int nb_matrice);
unsigned int** profondeur_to_altitude(unsigned int** matrice_profondeur,int nl,int nc);

COUPLE calcul_gradient_point(unsigned int** matrice,int i,int j);
COUPLE** cree_matrice_gradient(unsigned int** matrice);
int calcul_gradient_ligne(COUPLE** matrice_gradient,int numero,char mode);
int calcul_gradient_droite(COUPLE** matrice_gradient,COUPLE p1,COUPLE p2);
int trouve_bord_haut(COUPLE** matrice_gradient);
int trouve_bord_bas(COUPLE** matrice_gradient);
int trouve_bord_gauche(COUPLE** matrice_gradient);
int trouve_bord_droit(COUPLE** matrice_gradient);

#endif
