#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph * creerGraph(int n){
  graph * g = malloc(sizeof(graph));
  g->s = n;
  g->aretes = calloc(n,sizeof(arete)); // car NULL = 0
  return g;
}

void ajouterArete(graph * g, int src, int dst, int poids){
  arete * a = malloc(sizeof(arete));
  a->src = src;
  a->dst = dst;
  a->poids = poids;
  a->suivant = g->aretes[src];
  g->aretes[src] = a;
}

int main(void){
  graph * exemple = creerGraph(11);
  int src[]= {0,1,1,2,2,2,3,3,4,4 ,5,6,6,7,7 ,8,9,9};
  int dst[] = {3,3,5,0,1,4,2,7,2,10,6,5,8,8,10,9,7,10};
  for(int i=0;i<18;i++)
      ajouterArete(exemple,src[i],dst[i],1);
  return 0;
}
