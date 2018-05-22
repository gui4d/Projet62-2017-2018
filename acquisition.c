#include<libfreenect_sync.h>
#include"matrice.h"
#include"traitement.h"


unsigned int ** get_depth(){
//Cette fonction crée une matrice 2D contenant la distance entre le kinect et son environnement
  short* depth = 0;
  uint32_t ts;
  int ret;
  int i;

  ret = freenect_sync_get_depth((void**)&depth, &ts, 0, FREENECT_DEPTH_MM);
  if (ret < 0){ fprintf(stderr,"No kinect connected\n") ; return NULL ; }
  unsigned int** matrice = alloueMatriceInt(480,640);
  for(i=0;i<640*480;i++) (*matrice)[i]=depth[i];

  return matrice;
}


unsigned int *** get_n_depth(int n){
//Cree un tableau contenant n matrices prises a la suite par le kinect
  unsigned int*** tab= calloc(n,sizeof(*tab));
  int i;
  for(i=0;i<n;i++){
    tab[i]=get_depth();
  }
  return tab;
}
  

unsigned int ** get_moy_depth(int n){
//Retourne une matrice moyenne de n images prises a la suite
  int i;
  unsigned int *** tab_matrice=get_n_depth(n);
  unsigned int** matrice_moy=moyenne_matrice(tab_matrice,n);
  for(i=0;i<n;i++){
    libereMatrice(tab_matrice[i]);
  }
  free(tab_matrice);
  return matrice_moy;
}
