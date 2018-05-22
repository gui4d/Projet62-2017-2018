#include "Fonctions.h"


#define SCORE_MAX 5

void init_position(SDL_Rect* positionV,POSITION* voiture,int i){
    //initialise tout ce qui doit l'etre pour cette trame
    positionV->x=200+100*i;positionV->y=400;
    voiture->x=200+100*i;voiture->y=400;
}

void deroulement_joystick(CONTEXT C,int* precedent){
    SDL_Rect positionV[C.nbjoueur],positionCoupe; //les positions des differents objets dont la SDL a besoin pour l'affichage
    POSITION voiture[C.nbjoueur]; //contient toutes les donnees utiles sur les voitures

    int i,pause=0,option=0,collision=0;
    int temps_actuel=0,temps_precedent=0; //tous les differents temps dont on a besoin
    int score[C.nbjoueur]; for(i=0;i<C.nbjoueur;i++) score[i]=0; //tableau des scores des joueurs initialise a 0
    double angle_voulu=0,rot_graphique[C.nbjoueur]; //les differents angles dont on a besoin

    for(i=0;i<C.nbjoueur;i++){ //initialisation
        InitVoiture(voiture+i);
        init_position(positionV+i,voiture+i,i);
    }

    for(i=0;i<C.nbjoueur;i++){ //recuperation de la taille des textures de voitures
        SDL_QueryTexture(C.T_voiture[i], NULL, NULL, &(positionV[i].w), &(positionV[i].h));
        voiture[i].h=positionV[i].h;
        voiture[i].w=positionV[i].w;
    }

    //recuperation des textures des autres objets
    positionCoupe.x=(C.Xres-positionCoupe.w)/2;   positionCoupe.y=(C.Yres-positionCoupe.h)/2;

    Input in; //tableau contenant tous les evenements utiles
    mise_a_zero_input(&in); //mise a 0 de tous ces evenements

    while(!in.key[SDL_SCANCODE_ESCAPE]){ //tant qu'on a pas appuye sur la touche echap
        for(i=0;i<C.nbjoueur;i++){ //regarde si un joueur a atteint le score max
            if(score[i]>=SCORE_MAX){//si oui,affiche la coupe et retourne au menu jeu
                SDL_RenderCopy(C.sdlRenderer,C.T_element[ELEMENT_TROPHEE],NULL,&positionCoupe);
                SDL_RenderPresent(C.sdlRenderer); //rafraichit l'ecran
                SDL_Delay(3000); //attente de 3s
                *precedent=3;
                return;
            }
        }
        temps_actuel=SDL_GetTicks(); //on recupere le temps actuel
        if(temps_actuel-temps_precedent>TEMPS){ //si on a attendu suffisamment, on fait bouger la voiture

            //on recupere tous les evenements qui ont ete crees
            UpdateEventsP(&in);

            //gestion de toutes les voitures une par une
            for(i=0;i<C.nbjoueur;i++){

                //gestion des instructions
                gestion_instruction_joystick(&C,&in,voiture+i,&angle_voulu,i,&pause); //on gere les demandes de l'utilisateur de la voiture
                if(pause==1){ //si il a appuye sur start.
                    pause=0;
                    MenuPause(C,precedent,&option,i); //gestion du menu pause
                    if(*precedent!=0){ //il a demande a quitter le jeu
                        return;
                    }
                }

                //gestion de la physique liee a une voiture
                gestion_globale_voiture(C,voiture+i,positionV+i,rot_graphique+i,angle_voulu,i);

                //gestion de toutes les collisions
                percute_bord_joystick(C,voiture+i);
                if(voiture[i].saut.etat==0){ //si on ne saute pas, on peut percuter des objets
                    for(int j=0;j<C.nbjoueur;j++){
                        if(j!=i){
                            percute_voiture_joystick(voiture+i,voiture+j,&collision);
                        }
                    }
                }


                //nouvelle position de la voiture
                if(collision==0){ //si il ne va pas y avoir collision
                    calcul_position_joystick(voiture+i);
                }
                positionV[i].x=(int)voiture[i].x; positionV[i].y=(int)voiture[i].y; //nouvelle position de la voiture
            }
            //rafraichissement du temps ecoule
            temps_precedent=temps_actuel;

            //affichage a l'ecran de toutes les images et tous les textes
            SDL_UpdateTexture(C.sdlTexture, NULL, C.ecran->pixels, C.ecran->pitch);
            SDL_RenderClear(C.sdlRenderer); //destruction de l'ancienne ecran

            SDL_AffichageScore(C,score); //fonction creee permettant d'afficher les scores grâces a des images BMP
            SDL_RenderCopy(C.sdlRenderer, C.T_circuit[0], NULL, NULL); //copie du relief
            for(i=0;i<C.nbjoueur;i++){ //affichage de toutes les voitures
                SDL_RenderCopyEx(C.sdlRenderer,C.T_voiture[i],NULL,&positionV[i],rot_graphique[i],NULL,SDL_FLIP_NONE); //fait tourner la texture dans le sens horaire.
            }
            SDL_RenderPresent(C.sdlRenderer); //rafraichit l'ecran
        }

        else{ //si on a pas attendu suffisament, on endort le programme pour eviter qu'il ne consomme 100% du CPU
            SDL_Delay(TEMPS-(temps_actuel-temps_precedent));
        }
    }
}




