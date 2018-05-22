#include "Fonctions.h"

int main (){
    int choix=0,quitter=0,start=0,precedent=1, erreur_init;
    CONTEXT C;

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
	SDL_DisplayMode resolution;
	SDL_GetDesktopDisplayMode(0,&resolution);
	printf("%d %d\n",resolution.h,resolution.w); 

    

    C.relief=initialisation_manuel_relief(resolution.h,resolution.w);


	InitAll(&C,&erreur_init); //Initialise tout
	if(gestion_erreur(C,erreur_init)==1){ //si on a une erreur
		Release(&C); //on arrete tout
		return -1;
	}
    //CreationTextureRelief(&C,C.relief,resolution.h,resolution.w, 0, 0); //Creation de la texture du relief

    Mix_PlayMusic(C.musique[0], -1);
    MenuAide(C,0);
    do{
        if(precedent==1){ //quand precedent vaut 1 cela se refere au menu Start
            Mix_ResumeMusic();
            MenuStart(&C,&quitter,&start,&precedent); //gestion du menu start
        }
        if(start==1){ //si l'utilisateur veut commencer
            if(precedent==2){ //quanf precedent vaut 2 cela se refere au menu joueur
                Mix_ResumeMusic();
                MenuJoueur(&C,&precedent); //gestion du menu joueur
            }
            if(precedent==3){ //quand precedent vaut 3 cela se refere au menu jeu
                Mix_ResumeMusic();
                MenuJeu(&C,&precedent,&choix); //gestion du menu jeu

                Mix_RewindMusic();
                Mix_PauseMusic();
                if(choix==1){  //gestion de tout les choix possibles
                    deroulement_cerise_joystick(C,&precedent);
                }
                else if(choix==2){
                    deroulement_flag_joystick(C,&precedent);
                }
                else if(choix==3){
                    deroulement_course_joystick(C,&precedent);
                }
                else{}
                Mix_Pause(-1); //met en pause tous les canaux
            }
        }
    }while(quitter==0); //on continue tant que l'utilisateur ne veut pas quitter

    Release(&C);
    return 0;
}


/* different dialogue possiblement utiles
if(choix==1&&quitter==0){
    contour_test(C);
    //deroulement_controle2(C);
}
if(choix==2&&quitter==0){
    deroulement_cerise_joystick(C);
    printf("Il y a %d joysticks.\n",SDL_NumJoysticks()); // on ecrit combien il y a de joysticks
    for(int i=0;i<SDL_NumJoysticks();i++)
        printf("Nom du joystick numero %d : %s\n",i,SDL_JoystickName(i)); // on ecrit les noms des joysticks

    printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(C.joystick[0])); // nombre de boutons
    printf("Nombre d'axes : %d\n",SDL_JoystickNumAxes(C.joystick[0])); // nombre d'axes
    printf("Nombre de chapeaux : %d\n",SDL_JoystickNumHats(C.joystick[0])); // nombre de chapeaux
    printf("Nombre de trackballs : %d\n",SDL_JoystickNumBalls(C.joystick[0])); // nombre de trackballs
}
if(choix==3&&quitter==0){
    //circuit_test_track3(C); //permet de tester le remplissage du circuit
    deroulement_slot3(C);
}
*/

//Le 09/04/2018, il y a 2968 lignes de codes dans le projet
