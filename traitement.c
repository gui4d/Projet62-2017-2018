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
  //Cree une nouvelle matrice correspondant a une matrice d'altitude
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

