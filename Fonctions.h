#ifndef _FONCTIONS
#define _FONCTIONS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include "Constantes.h"
#include "Structures.h"
#include "Relief.h"

#include "acquisition.h"
#include "matrice.h"
#include "traitement.h"
#include "calibrage.h"



/*                              FONCTION DU FICHIER InitialisationEtFin.c                                  */

/**permet d'initialiser toutes les commandes (video/son/ecriture...), appel aussi la fonction
 * LoadAll()*/
void InitAll(CONTEXT* C,int *erreur);

/**permet de charger les images, la police, les sons ... dans le context*/
void LoadAll(CONTEXT *C,int *erreur);

/**permet de fermer toutes les SDL (video/son/ecriture) et de liberer le context*/
int Release(CONTEXT *C);

/**fonction qui gere toutes les erreurs possibles liees au demarrage et chargement*/
int gestion_erreur(CONTEXT C,int erreur);

/**fonction qui initialise la fonction random*/
void Init_rand();

/**met a la valeur voulu les coordonnees du circuit*/
void mise_a(int valeur,Coordonnee *circuit,int taille);

/**permet d'augmenter le nombre dde joystick disponible quand on veut*/
int ReallocationJoystick(CONTEXT *C);



/*                              FONCTION DU FICHIER GestionEvent.c                                  */

/**met a 0 tout les champs de la structure In*/
void mise_a_zero_input(Input* in);

/**met a jour le tableau des evenements en continue**/
void UpdateEventsP(Input* in);

/**met a jour le tableau des evenements en faisant des poses**/
void UpdateEventsW(Input* in);

/**switch contenant toutes les possibilites d'evenements **/
void GestionEvents(Input *in, SDL_Event event);

/*                              FONCTION DU FICHIER GestionMenu.c                                  */


/**permet de debuter ou de quitter l'application*/
void MenuStart(CONTEXT *C, int* quitter, int* start,int *precedent);

/**permet de recuperer le choix de l'utilisateur dans le menu*/
void MenuJeu(CONTEXT *C, int *precedent, int *choix);

/**permet de recuperer le nombre de joueurs*/
void MenuJoueur(CONTEXT *C,int *precedent);

/**permet d'afficher un warning sur le nombre de mannettes*/
void Avertissement(CONTEXT C, SDL_Rect menu);

/**affiche le menu pause et permet au joueur de choisir ce qu'il veut*/
void MenuPause(CONTEXT C,int* precedent,int *option,int joueur);

/**affiche le menu option et permet au joueur de choisir ce qu'il veut*/
void MenuOption(CONTEXT C, int joueur);

/**afiche le menu aide comportant l'ensemble des commandes du jeu*/
void MenuAide(CONTEXT C, int joueur);

/**affiche le detail concernant comment le programme comprend ou est chaque personne autout du bac à sable*/
void DetailPerspective(CONTEXT C, int joueur);

/**affiche le detail sur le controle de la voiture, explique plus en detail le controle en mode absolu*/
void ExplicationControle(CONTEXT C, int joueur);



/*                           FONCTION DU FICHIER GestionInstruction.c                                  */

/**gere le demande du joueur lorqu'il veut changer de place physiquement (autour du bac a sable)*/
int gestion_position_joueur(Input *in, POSITION *voiture, int numero);

/**gere la position du joystick et donc l'angle voulue lorque le joueur est derriere le videoprojecteur*/
void gestion_derriere(POSITION *voiture, double *angle_voulu, int x, int y);

/**gere la position du joystick et donc l'angle voulue lorque le joueur est devant le videoprojecteur*/
void gestion_devant(POSITION *voiture, double *angle_voulu, int x, int y);

/**gere la position du joystick et donc l'angle voulue lorque le joueur est a gauche le videoprojecteur*/
void gestion_gauche(POSITION *voiture, double *angle_voulu, int x, int y);

/**gere la position du joystick et donc l'angle voulue lorque le joueur est a droite le videoprojecteur*/
void gestion_droite(POSITION *voiture, double *angle_voulu, int x, int y);


/**gere toutes les demandes de l'utilisateur (si il veut freiner, de combien il veut
accelerer, tourner ...) faites grâce a une manette*/
void gestion_instruction_joystick(CONTEXT *C,Input *in,POSITION *voiture,double* angle_voulu,int numero,int* pause);




/*                           FONCTION DU FICHIER GestionVoiture.c                                  */


/**calcul la nouvelle rotation demande par l'utilisateur grâce a ujne manette*/
double calcul_rotation_joystick(double angle_voulu,POSITION* voiture);

/**calcul la nouvelle vitesse de la voiture suivant si l'utilisateur veut freiner,
de combien est la force moteur...*/
void calcul_vitesse_joystick(POSITION *voiture,double F_pente, double F_frottement_solide, double virage);

/**calcul la nouvelle position de la voiture suivant sa vitesse et sa rotation*/
void calcul_position_joystick(POSITION* voiture);

/**calcul si la voiture fait un saut ou non*/
int calcul_saut_joystick(CONTEXT C, POSITION *voiture, double beta, SDL_Rect *positionV);

/**cacul le zoom applique a la voiture a chaque iteration*/
double calcul_zoom(POSITION voiture, int temps_actuel);

/**calcul si une voiture va percuter le bord de l'ecran*/
int percute_bord_joystick(CONTEXT C,POSITION *voiture);

/**si on doit rebondir, cette fonction s'en occupe*/
int percute_mur(CONTEXT C,POSITION *voiture, double beta, int joueur);

/**calcul si deux voitures vont se percuter*/
int percute_voiture_joystick(POSITION *voiture1,POSITION *voiture2,int *collision);

/**gestion de la collision d'une voiture avec un objet represente par un cercle*/
int percute_objet_joystick(POSITION voiture,SDL_Rect Objet);

/**gestion du derapage des voitures*/
int gestion_derapage(POSITION *voiture, double virage, double *rot_graphique);

/**permet de gerer toutes la physique liee a une voiture*/
void gestion_globale_voiture(CONTEXT C,POSITION *voiture,SDL_Rect *POSITIONV,double *rot_graphique,double angle_voulu, int joueur);


/*                           FONCTION DU FICHIER GestionMusique.c                                  */

/**gere le bruit que fait le moteur*/
void gestion_bruit_moteur(CONTEXT C, POSITION *voiture, int joueur);

/**gere le bruit que fait le derapage, lorqu'il occure*/
void gestion_bruit_derapage(CONTEXT C, POSITION *voiture, int joueur);

/**gere le bruit que fait le crash entre 2 voitures, lorqu'il occure*/
void gestion_bruit_crash(CONTEXT, POSITION *voiture, int joueur);

/**gere le bruit que fait une voiture lorsqu'elle rebondit sur un mur*/
void gestion_bruit_rebond(CONTEXT C, POSITION *voiture, int joueur);


/*                              FONCTION DU FICHIER Fonction.c                                  */

/**variante de la fonction SDL_BlitSurface()*/
int Blit(SDL_Surface* ecran,SDL_Surface *image,int x,int y);

/**fonction qui renvoit un entier entre a inclus et b exclus*/
int rand_a_b(int a,int b);

/**fonction qui calcul la norme de la vitesse de la voiture*/
double norme(Information voiture);

/**fonction qui calcul le signe de la vitesse de la voiture*/
int signe(double vitesse);

/**calcul le PGCD de a et de b avec a>b !!!*/
int PGCD(int a,int b);

/**Met tout a 0 dans la structure Position*/
void InitVoiture(POSITION *voiture);

/**Permet la conversion d'une position exprime avec des doubles en une position exprime avec des entiers*/
void PassagePositionRect(POSITION voiture, SDL_Rect* position);

/**Permet l'affichage d'une texture d'un chiffre ou d'une lettre*/
void SDL_AffichageCaractere(SDL_Renderer *Renderer, SDL_Texture *Lettre, int x, int y);

/**Permet l'affichage du score de tous les joueurs a un endroits pre-definie*/
void SDL_AffichageScore(CONTEXT C, int *score);

/**Permet de definir le centre de rotation de la Texture de la voiture*/
void AttributionCentre(SDL_Rect position, SDL_Point *centre);

/**renvoit la valeur absolue d'un double*/
double abs_double(double x);

/**retourne le modulo entre deux nombres reelles*/
double modulo(double a, double b);



/*                              FONCTION DU FICHIER TrameExempleJoysttick.c                                  */

/**initialise cettaines variables utiles pour la suite du programme*/
void init_position_joystick(SDL_Rect* positionV,POSITION* voiture,int i);

/**gere toutes les demandes de l'utilisateur (si il veut freiner, de combien il veut
accelerer, tourner ...) faites grâce a une manette*/
void deroulement_controle_joystick(CONTEXT C,int *precedent);



/*                              FONCTION DU FICHIER  obtenir_couleur.c                                  */

/**permet d'obtenir le pixel aux coordonnees (x,y) de la surface*/
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);

/**permet de remplacee le pixel de coordonnees (x,y) de la surface par celui qu'on veut*/
void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);






/*                              FONCTION DU FICHIER modelisation.c                                  */

/**calcul la contribution de la pente sur la voiture pour le premier modele*/
double force_pente_joystick(CONTEXT C,POSITION *voiture,SDL_Rect positionV);

/**calcul la contribution de la pente sur la voiture pour le premier modele et entre les roues de la voiture*/
double force_pente_joystick_bis(CONTEXT C,POSITION *voiture, double *beta);

/**empeche la position de depasser la resolution de l'ecran en X**/
void securite_overflowX(CONTEXT C,int* position);

/**empeche la position de depasser la resolution de l'ecran en Y**/
void securite_overflowY(CONTEXT C,int* position);

/**calcul la force liee au frottement solide*/
double force_frottement_solide(POSITION voiture);

/**calcul la contribution de la pente sur la voiture pour le deuxieme modele*/
void force_pente_joystick2(CONTEXT C,Information *voiture,SDL_Rect positionV);






/*                              FONCTION DU FICHIER collision.c                                  */

/**verifie si 2 cercles se touchent, renvoi 1 si oui, 0 sinon*/
int CollisionCercles(Cercle C1,Cercle C2);

/**calcul les nouvelles coordonnees d'un point qui a ete tourne d'un certain angle (en degre)*/
void PointApresRotation(Point *point,Point centre,double angle);

/**determine si un point est dans un cercle*/
int CollisionPointCercle(Point point,Cercle C);

/**determine si il y a collision entre un cercle et une droite*/
int CollisionDroiteCercle(Point A,Point B,Cercle C);

/**determine si il y a collision entre un cercle et un segment*/
int CollisionSegmentCercle(Point A,Point B,Cercle C);

/**determine si il y a collision entre un cercle et un rectangle*/
int CollisionRectangleCercle(POSITION rectangle,Cercle cercle);

/**determine si il y a collision entre un segment et une droite*/
int CollisionDroiteSeg(Point A,Point B,Point O,Point P);

/**determine si il y a collision entre un segment et un segment*/
int CollisionSegSeg(Point A,Point B,Point O,Point P);

/**determine si deux rectangles se croisent*/
int CollisionRectangles(POSITION rectangle_av,POSITION rectangle_ap,POSITION rectangle_im);

/**permet de definir les sommets et le centre d'un rectangle*/
void DefinitionRectangle(Point *HG,Point *HD, Point *BD, Point *BG,Point* centre,POSITION rectangle);

/**determine si il y a intersection entre un rectangle et un segment*/
int CollisionSegmentRectangle(Point O, Point P, Point HGim, Point HDim, Point BDim, Point BGim);

/**determine si deux segments se croisent*/
int IntersectionSegments(Point A,Point B,Point I,Point P);

/**determine si un segment et un rectangle se croisent*/
int IntersectionSegmentRectangle(Point A, Point B, Point HG, Point HD, Point BD, Point BG);

/**determine si deux rectangles se croisent*/
int IntersectionRectangles(POSITION rectangle1,POSITION rectangle2);

/**permet de definir les sommets et le centre d'un rectangle*/
void DefinitionRectangle(Point *HG,Point *HD, Point *BD, Point *BG,Point* centre,POSITION rectangle);

/**permet de definir un cercle*/
void DefinitionCercle(Cercle *C, POSITION cercle);



/*                              FONCTION DU FICHIER JeuCerise.c                                  */

/**initialise cettaines variables utiles pour la suite du programme*/
void init_position_cerise(SDL_Rect* positionV,POSITION* voiture,SDL_Rect *cerise,int i);

/**gestion du deroulement du jeu de la cerise*/
void deroulement_cerise_joystick(CONTEXT C,int* precedent);




/*                              FONCTION DU FICHIER JeuFlag.c                                  */

/**gestion du deroulement du jeu du flag*/
void deroulement_flag_joystick(CONTEXT C,int *precedent);

/**initialise la position des flags utiles pour la suite du programme*/
void InitFlag(Infosflag *Flag);

/**permet d'affecter une position aleatoire a un flag*/
void affectation_aleatoire_flag(CONTEXT C, SDL_Rect* positionFlag, SDL_Rect* initialFlag, SDL_Rect* positionBalise);

/**permet de positionner la voiture a côte du flag lui correspondant*/
void affectation_voiture(CONTEXT C, POSITION* voiture, SDL_Rect *positionFlag, POSITION *initial, SDL_Rect *positionV);

/*                              FONCTION DU FICHIER JeuCourse.c                                  */

/**initialise cettaines variables utiles pour la suite du programme*/
void init_position_course(SDL_Rect* positionV,POSITION* voiture,int i);


void deroulement_course_joystick(CONTEXT C,int* precedent);

#endif // _FONCTIONS

