#ifndef _TRAITEMENT
#define _TRAITEMENT
typedef struct{int l;int c;} COUPLE;
typedef struct{int inf;int sup;} BORNES;

int nb_erreurs_image(unsigned int** matrice);
unsigned int** moyenne_matrice(unsigned int*** tab_matrice,int nb_matrice);
unsigned int** profondeur_to_altitude(unsigned int** matrice_profondeur,int nl,int nc);

#endif
