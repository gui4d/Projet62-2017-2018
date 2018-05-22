#include "Fonctions.h"


double force_pente_joystick(CONTEXT C,POSITION *voiture,SDL_Rect positionV){
    int xf,yf,xi,yi;
    double Force,vitesse,signeV=1;
    vitesse=(DELTA/MASSE)*(voiture->force_moteur)+(1-FROTTEMENT_FLUIDE*DELTA/MASSE)*voiture->vitesse; //principe fondamental de la dynamique
    xi=(int)(voiture->x+positionV.w/2);
    yi=(int)(voiture->y+positionV.h/2);
    xf=(int)(xi+vitesse*sin(M_PI*voiture->rotation/180)); //un peu de trigonométrie
    yf=(int)(yi-vitesse*cos(M_PI*voiture->rotation/180));
    if((xf==xi)&&(yf==yi)){
        xf=(int)(xf+5*sin(M_PI*voiture->rotation/180));
        yf=(int)(yf-5*cos(M_PI*voiture->rotation/180));
	}

    if(xf>C.Xres||xf<0||yf>C.Yres||yf<0){
        return 0;
    }


    voiture->alpha= atan2((C.relief[yf][xf]-C.relief[yi][xi]),sqrt((xf-xi)*(xf-xi)+(yf-yi)*(yf-yi))); //Calcul de alpha
    Force=MASSE*G*-sin(voiture->alpha);
    if(vitesse!=0){
        signeV=abs(vitesse)/vitesse;
    }
    return (Force*signeV)*cos(voiture->alpha);
}

double force_pente_joystick_bis(CONTEXT C,POSITION *voiture, double *beta){
    int xf,xi,yf,yi;
    Point Avant, Arriere, Centre; //position de la partie avant et arrière de la voiture
    double Force;
    Avant.x=voiture->x+voiture->w/2;
    Avant.y=voiture->y;
    Arriere.x=voiture->x+voiture->w/2;
    Arriere.y=voiture->y+voiture->h;
    Centre.x=voiture->x+voiture->w/2;
    Centre.y=voiture->y+voiture->h/2;

    PointApresRotation(&Avant,Centre,voiture->rotation);
    PointApresRotation(&Arriere,Centre,voiture->rotation);

    xf=(int)Avant.x;   yf=(int)Avant.y;
    xi=(int)Arriere.x; yi=(int)Arriere.y;
    securite_overflowX(C,&xi); securite_overflowY(C,&yi);
    securite_overflowX(C,&xf); securite_overflowY(C,&yf);

    //Calcul de beta angle de ma pente juste devant la voiture
    *beta= atan2((C.relief[yf][xf]-C.relief[yi][xi]),sqrt((xf-xi)*(xf-xi)+(yf-yi)*(yf-yi)));

    if(*beta-voiture->alpha>M_PI/3){
        voiture->rebondi=1;
    }

    Force=-MASSE*G*sin(*beta)*cos(*beta);
    return Force*3; //le coef 3 est là pour rendre la force non negligeable
}

void securite_overflowX(CONTEXT C,int* position){
    if(*position<0) *position=0;
    else if(*position>C.Xres-1) *position=C.Xres-1;
    else{}
}

void securite_overflowY(CONTEXT C,int* position){
    if(*position<0) *position=0;
    else if(*position>C.Yres-1) *position=C.Yres-1;
    else{}
}

double force_frottement_solide(POSITION voiture){
    if(abs(voiture.vitesse)>0.01){
        double Cos=cos(voiture.alpha);
        return signe(voiture.vitesse)*FROTTEMENT_SOLIDE*MASSE*G*Cos*Cos;
    }
    return 0;
}

void force_pente_joystick2(CONTEXT C,Information *voiture,SDL_Rect positionV){
    int xf,yf,xi,yi;
    double alpha;
    xi=(int)(positionV.x+positionV.w/2);
    yi=(int)(positionV.y+positionV.h/2);
    xf=(int)(xi+DELTA*voiture->v_x); //un peu de trigonométrie
    yf=(int)(yi+DELTA*voiture->v_y);
    if((xf==xi)&&(yf==yi)){
        xf=(int)(xf+5*sin(M_PI*voiture->rotation/180));
        yf=(int)(yf-5*cos(M_PI*voiture->rotation/180));
	}

    if(xf>C.Xres||xf<0||yf>C.Yres||yf<0){
        voiture->F_pentex=0;
        voiture->F_pentey=0;
        return;
    }


    alpha= atan2((C.relief[yf][xf]-C.relief[yi][xi]),sqrt((xf-xi)*(xf-xi)+(yf-yi)*(yf-yi))); //Calcul de alpha
    voiture->F_pentex=-MASSE*G*sin(alpha);//*voiture->v_x/norme(*voiture);
    voiture->F_pentey=-MASSE*G*sin(alpha);//*voiture->v_y/norme(*voiture);
}
