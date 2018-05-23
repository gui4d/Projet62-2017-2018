#include<stdlib.h>
#include"matrice.h"
#include"traitement.h"
#include "math.h"

int nb_erreurs_image(unsigned int** matrice){
  //Compte le nombre de pixels aberants dans l'image
  int i,j,compteur;
  compteur=0;
  for(i=0;i<480;i++){
    for(j=0;j<640;j++){
      if (matrice[i][j]==0 || matrice[i][j]>3000) compteur+=1;
    }
  }
  return compteur;
}

unsigned int ** moyenne_matrice(unsigned int *** tab_matrice, int nb_matrice){
  //Cree une matrice correspondant a la moyenne des matrices du tableau. Lesvaleurs aberantes ne sont pas prises en compte
  int i,j,k,compteur;
  unsigned int** matrice_moy = alloueMatriceInt(480,640);
  unsigned int pixel;
  for(i=0;i<480;i++){
    for(j=0;j<640;j++){
      compteur=0;
      for(k=0;k<nb_matrice;k++){
	pixel=tab_matrice[k][i][j];
	if(pixel>0 && pixel<2000){
	    matrice_moy[i][j]+=pixel;
	    compteur+=1;
	  }
      }
      if(compteur!=0) matrice_moy[i][j]=matrice_moy[i][j]/compteur;
    }
  }
  return matrice_moy;
}
      
unsigned int** profondeur_to_altitude(unsigned int** matrice_profondeur,int nl,int nc){
  //Cree une matrice et realise la transformation pour passer de mesures de profondeur a celle d'altitude
  int i,j;
  unsigned int** matrice_alt=alloueMatriceInt(nl,nc);
  int max = trouveMaximunI(matrice_profondeur,nl,nc);
  for(i=0;i<nl;i++){
    for(j=0;j<nc;j++){
      matrice_alt[i][j]=max - matrice_profondeur[i][j];
    }
  }
  return matrice_alt;
}


COUPLE  calcul_gradient_point(unsigned int **matrice,int i,int j){
  /*Calcule le gradient en 1 point.
    Ne peut pas etre utilisée sur les dernieres couples de cases du tableau*/
  COUPLE C;
  /* if(matrice[i+1][j]==0 || matrice[i][j]==0) C.c = 0;//Pas de calcul pour les pixels aberants
  else*/ C.c=matrice[i+1][j]-matrice[i][j];
  
  /*if(matrice[i][j+1]==0 || matrice[i][j]==0) C.l = 0;//Pas de calcul pour les pixels aberants 
    else*/ C.l=matrice[i][j+1]-matrice[i][j];
  
  return C;
}

COUPLE** cree_matrice_gradient(unsigned int** matrice){
  //Cree une matrice ou chaque element correspond au gradient en ce point
  COUPLE** matrice_gradient;
  int i,j;
  matrice_gradient = calloc(480,sizeof(*matrice_gradient));
  *matrice_gradient = calloc(480*640,sizeof(**matrice_gradient));
  for(i=1;i<480;i++){
    matrice_gradient[i]=matrice_gradient[i-1]+640;
  }

  for(i=0;i<480-1;i++){
    for(j=0;j<640-1;j++){
      matrice_gradient[i][j]=calcul_gradient_point(matrice,i,j);
    }
  }
  return matrice_gradient;
}

int calcul_gradient_ligne(COUPLE** matrice_gradient,int numero,char mode){
  //Somme le gradient d'une ligne ou d'une colonne dans la direction opposee
  int total=0,k;
  if(mode=='l'|| mode== 'L'){
    for(k=0;k<640;k++){
      total+=matrice_gradient[numero][k].c;
    }
    return total;
  }
  if(mode=='c' || mode=='C'){
    for(k=0;k<480;k++){
      total+=matrice_gradient[k][numero].l;
      // printf("gradient:%d total:%d\n",matrice_gradient[k][numero].l,total);
    }
    return total;
  }
  else{
    fprintf(stderr,"Mode invalide : 'l' pour la ligne ou 'c' pour les colonnes\n");
    return 0;
  }
}

int calcul_gradient_droite(COUPLE** matrice_gradient,COUPLE p1,COUPLE p2){
//Somme le gradient d'un droite quelconque
  int total=0,k1,k2;
  int delta_c=p1.c -p2.c;
  int delta_l =p1.l - p2.l;
  if(p1.c < 0 || p1.l <0 || p2.c <0 || p2.l <0 ) return -1;
  if(p1.c > 639 || p1.l > 439 || p2.c > 639 || p2.l > 439) return -2;
  if(abs(delta_c)<abs(delta_l)){ //Cas ou on etudie les bords horizontaux
    for(k1=p1.l;k1<p2.l;k1++){
      k2=(int) ( p1.c + (float)k1 * ((float) (p2.c - p1.c))  / (float) delta_l );
      total+=matrice_gradient[k1][k2].c;
    }
    return total;
  }
  else{ // Cas ou on etudie les bords verticaux
    for(k2=p1.c;k2<p2.c;k2++){
      k1=(int) (p1.l +(float)k1 *((float) (p2.l-p1.l)) / (float) delta_c  );
      total+=matrice_gradient[k1][k2].l;
    }
    return total;
  }
    
}
  
  

int trouve_bord_haut(COUPLE** matrice_gradient){
  //Trouve la ligne ou le gradient est minimal dans la moitie haute
  int i,m;
  int tab_gradient[240];
  for(i=0;i<240;i++){
    tab_gradient[i]=calcul_gradient_ligne(matrice_gradient,i,'l');
  }
  m=indice_min(tab_gradient,0,240);
  return m;
}
  
int trouve_bord_bas(COUPLE** matrice_gradient){
  //Trouve la ligne ou le gradient est minimal dans la moitie basse
  int i,m;
  int tab_gradient[239];
  for(i=0;i<239;i++){
    tab_gradient[i]=calcul_gradient_ligne(matrice_gradient,i+240,'l');
  }
  m=indice_min(tab_gradient,0,239);
  return m+240;
}
    
int trouve_bord_gauche(COUPLE** matrice_gradient){
  //Trouve la colonne ou le gradient est minimal dans la partie gauche
  int i,m;
  int tab_gradient[320];
  for(i=0;i<320;i++){
    tab_gradient[i]=calcul_gradient_ligne(matrice_gradient,i,'c');
  }
  m=indice_min(tab_gradient,0,240);
  return m;
}

int trouve_bord_droit(COUPLE** matrice_gradient){
  //Trouve la colonne ou le gradient est maximal dans la partie droite
  int i,m;
  int tab_gradient[319];
  for(i=0;i<319;i++){
    tab_gradient[i]=calcul_gradient_ligne(matrice_gradient,i+320,'c');
  }
  m=indice_max(tab_gradient,0,319);
  return m+320;
}
