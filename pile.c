#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"

pile * creerPile(void){
  pile * p = calloc(1,sizeof(pile)); //automatiquement sommet mis à 0
  return p;
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

int Pile(void){
  pile * exemple = creerPile();
  for(int i=0;i<10;i++){
    int donnee = rand()%100;
    empile(exemple,donnee);
    printf("Empile %d\n",donnee);
  }
  for(int i=0;i<10;i++){
    printf("Depile %d\n",depile(exemple));
  }
  return 0;
}
  
