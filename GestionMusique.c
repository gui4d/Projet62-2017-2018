#include "Fonctions.h"

void gestion_bruit_crash(CONTEXT C, POSITION *voiture, int joueur){
    Mix_Pause(joueur+CANAL_MOTEUR);
    Mix_Pause(joueur+CANAL_DERAPAGE);
    Mix_VolumeChunk(C.sons[SON_CRASH],MIX_MAX_VOLUME); //definie le volume sonore pour le son
    Mix_PlayChannel(joueur+CANAL_CRASH, C.sons[SON_CRASH], 0);
    voiture->son.compteur_crash=1;
}

void gestion_bruit_moteur(CONTEXT C, POSITION *voiture, int joueur){
    int volume_son;
    int vitesse_max=(int)(VITESSE_MAX+1);
    volume_son=(int)(MIX_MAX_VOLUME*voiture->vitesse/vitesse_max);

    //le son du moteur doit-il reprendre ? Pas reprendre ? On s'en fout ? (a cause du rebond)
    if(Mix_Paused(joueur+CANAL_MOTEUR)&&voiture->son.compteur_rebond==DUREE_REBOND){
        Mix_Resume(joueur+CANAL_MOTEUR);
        voiture->son.compteur_moteur=0;
        return;
    }
    else if(voiture->son.compteur_rebond!=DUREE_REBOND&&voiture->son.compteur_rebond!=0){
        voiture->son.compteur_rebond++;
        return;
    }
    else{}

    //le son du moteur doit-il reprendre ? Pas reprendre ? On s'en fout ? (a cause du crash)
    if(Mix_Paused(joueur+CANAL_MOTEUR)&&voiture->son.compteur_crash==DUREE_CRASH){
        Mix_Resume(joueur+CANAL_MOTEUR);
        voiture->son.compteur_crash=0;
        return;
    }
    else if(voiture->son.compteur_crash!=DUREE_CRASH&&voiture->son.compteur_crash!=0){
        voiture->son.compteur_crash++;
        return;
    }
    else{}


    if(voiture->son.compteur_moteur==0){
        Mix_VolumeChunk(C.sons[SON_MOTEUR], volume_son); //definie le volume sonore pour le son
        voiture->son.compteur_moteur++;
        Mix_PlayChannel(CANAL_MOTEUR+joueur, C.sons[SON_MOTEUR], 0); //joue le son sur le canal 0, le fait 0+1 fois
    }
    else if(voiture->son.compteur_moteur!=DUREE_MOTEUR){
        Mix_VolumeChunk(C.sons[SON_MOTEUR], volume_son); //definie le volume sonore pour le son
        voiture->son.compteur_moteur++;
    }
    else if(voiture->son.compteur_moteur==DUREE_MOTEUR){
        Mix_VolumeChunk(C.sons[SON_MOTEUR], volume_son); //definie le volume sonore pour le son
        voiture->son.compteur_moteur=0;
    }
}

void gestion_bruit_derapage(CONTEXT C, POSITION *voiture, int joueur){
    Mix_Pause(CANAL_MOTEUR+joueur);
    Mix_Resume(joueur+CANAL_DERAPAGE);
    if(voiture->son.compteur_derapage==0){
        Mix_VolumeChunk(C.sons[SON_DERAPAGE],MIX_MAX_VOLUME); //definie le volume sonore pour le son
        voiture->son.compteur_derapage++;
        Mix_PlayChannel(joueur+CANAL_DERAPAGE, C.sons[SON_DERAPAGE], 0); //joue le son sur le canal 0, le fait 0+1 fois
    }
    else if(voiture->son.compteur_derapage!=DUREE_DERAPAGE){
        Mix_VolumeChunk(C.sons[SON_DERAPAGE], MIX_MAX_VOLUME); //definie le volume sonore pour le son
        voiture->son.compteur_derapage++;
    }
    else if(voiture->son.compteur_derapage==DUREE_DERAPAGE){
        Mix_VolumeChunk(C.sons[SON_DERAPAGE], MIX_MAX_VOLUME); //definie le volume sonore pour le son
        voiture->son.compteur_derapage=0;
    }
}

void gestion_bruit_rebond(CONTEXT C, POSITION *voiture, int joueur){
    Mix_Pause(joueur+CANAL_MOTEUR);
    Mix_Pause(joueur+CANAL_DERAPAGE);
    Mix_VolumeChunk(C.sons[SON_REBOND],MIX_MAX_VOLUME); //definie le volume sonore pour le son
    Mix_PlayChannel(joueur+CANAL_REBOND, C.sons[SON_REBOND], 0);
    voiture->son.compteur_rebond=1;
}
