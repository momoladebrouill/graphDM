#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"

pile * creerPile(void){
  pile * p = calloc(1,sizeof(pile)); //automatiquement sommet mis à 0
  return p;
}

int printPile(pile *p){
  element *e = p->sommet;
  printf("Pile : ");
  while(e){
    printf("%d ",e->donnee);
    e = e->suivant;
  }
  printf("\n");
  return 0;
}

bool estVidePile(pile * p){
  return !p->sommet;
}

void empile(pile * p,int donnee){
  element *e = malloc(sizeof(element));
  e->donnee = donnee;
  e->suivant = p->sommet;
  p->sommet = e;
}

int depile(pile *p){
    element *e = p->sommet;
    p->sommet = e->suivant;
    int donnee = e->donnee;
    free(e);
    return donnee;
}

void freePile(pile * p){
  while(!estVidePile(p)){
    depile(p);
  }
  free(p);
}

int Pile(void){
  printf("\033[1;34mPile\033[0m\n");
  pile * exemple = creerPile();
  for(int i=0;i<10;i++){
    int donnee = rand()%100;
    empile(exemple,donnee);
    printf("Empile %d\n",donnee);
  }
  printPile(exemple);
  for(int i=0;i<10;i++){
    printf("Depile %d\n",depile(exemple));
  }
  freePile(exemple);
  return 0;
}
  
