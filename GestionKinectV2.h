#include "Fonctions.h"
#include "Relief.h"


		//Dans le fichier FonctionsElementairesMatrices.c



/**Alloue dynamiquement et en contigue une matrice d' unsigned short de taille nl x nc*/
unsigned short** alloueMatriceUnsignedShort(int nl, int nc);
/**Libere l'espace memoire lie a la matrice d'unsigned short */
void libereMatriceUnsignedShort(unsigned short** matrice);
/**Retourne le maximun d'une matrice d'entier de taille nl x nc*/
int trouveMaximun(int** matrice, int nl, int nc);
/**Retourne le minimum d'une matrice d'entier de taille nl x nc*/
int trouveMinimun(int** matrice, int nl, int nc);

		//Dans le fichier VisualiseMatrice.c




		//Dans le fichier CreationMatricesTest.c

/**Cree une matrice de taile(nl,nc) comportant une pente entre un niveau en haut de la fenetre et en bas*/
int** creeMatricePenteAxeX(int nl, int nc, int niveauHaut, int niveauBas);
/**Cree une matrice de taile(nl,nc) comportant une pente entre un niveau a gauche et a droite de la fenetre*/
int** creeMatricePenteAxeY(int nl, int nc, int niveauGauche, int niveauDroit);

/**Modifie et retourne la matrice1 pour que chaque element soit le max des deux matrices. Libere egalement matrice2 */
int** maxMatrice(int** matrice1, int** matrice2, int nl, int nc);
/**Modifie et retourne la matrice1 pour que chaque element soit la moyenne des deux matrices. Libere egalement matrice2 */
int** moyMatrice(int** matrice1, int ** matrice2, int nl, int nc);

		//Dans le fichier SauvegardeFichier.c
/**Ecrit les elements de la matrice dans le fichier texte demande*/
void sauvegardeMatriceInt(char* nomfichier, int** matrice, int nl, int nc);

int** chargeMatriceInt(char* nomfichier, int* pnl, int* pnc);

int** interpolationLineaireColonne(int** matrice_depart, int nl, int nc, int coef_multiplicatif);
