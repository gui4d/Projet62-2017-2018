#include "Fonctions.h"

int Blit(SDL_Surface* ecran,SDL_Surface *image,int x,int y){
    SDL_Rect position;
    position.x=x;
    position.y=y;
    return SDL_BlitSurface(image,NULL,ecran,&position);
}

int rand_a_b(int a,int b){
    return rand()%(b-a)+a; //renvoi une valeur aleatoire entre a inclus et b exclus
}

double norme(Information voiture){
    //renvoi la norme d'un vecteur vitesse
    return sqrt(voiture.v_x*voiture.v_x+voiture.v_y*voiture.v_y);
}

int signe(double vitesse){
    //renvoi le signe d'un double
    if(vitesse!=0){
        return (int)(abs(vitesse)/vitesse);
    }
    return 1;
}

int PGCD(int a,int b){
    int r=a%b;
    if(r==0) return b;
    else return PGCD(b,r);
}

void InitVoiture(POSITION *voiture){
    voiture->position_joueur=DERRIERE;
    voiture->x=0;
    voiture->y=0;
    voiture->h=0;
    voiture->w=0;
    voiture->vitesse=0;
    voiture->freinage=0;
    voiture->derapage_av=0;
    voiture->derapage=0;
    voiture->rotation=0;
    voiture->saut.etat=0;
    voiture->saut.debut_saut=0;
    voiture->saut.fin_saut=0;
    voiture->saut.vo=0;
    voiture->saut.zo=0;
    voiture->alpha=0;
    voiture->force_moteur=0;
    voiture->virage=0;
    voiture->rebondi=0;
    voiture->compteur_rebond=0;
    voiture->son.compteur_moteur=0;
    voiture->son.compteur_derapage=0;
    voiture->son.compteur_rebond=0;
    voiture->son.compteur_crash=0;
}

void PassagePositionRect(POSITION voiture, SDL_Rect* position){
    position->x=(int)(voiture.x);
    position->y=(int)(voiture.y);
}

void SDL_AffichageCaractere(SDL_Renderer *Renderer, SDL_Texture *Lettre, int x, int y){
    SDL_Rect position;
    position.x=x; position.y=y;
    SDL_QueryTexture(Lettre, NULL, NULL, &(position.w), &(position.h));

    SDL_RenderCopy(Renderer, Lettre, NULL, &position);
}

void SDL_AffichageScore(CONTEXT C, int *score){
    int i;
    for(i=0;i<C.nbjoueur;i++){
        SDL_AffichageCaractere(C.sdlRenderer,C.T_score[LETTRE_J],10,H_SCORE*i+10); //affichage du J de joueur
        SDL_AffichageCaractere(C.sdlRenderer,C.T_score[DEBUT_NOMBRE+i],W_SCORE+8,H_SCORE*i+10); //affichage du numero du joueur

        SDL_AffichageCaractere(C.sdlRenderer,C.T_score[DEBUT_NOMBRE+score[i]],2*W_SCORE+16,H_SCORE*i+10); //affichage du score
    }
}

void AttributionCentre(SDL_Rect position, SDL_Point *centre){
        centre->x=position.w/2;
        centre->y=position.h/2;
        return;
}

double abs_double(double x){
    if(x<0) return -x;
    return x;
}

double modulo(double a, double b){
    int c=(int)a%(int)b;
    return c+a-(int)a;
}

void AffichageCommande(COMMANDE manette){
}
