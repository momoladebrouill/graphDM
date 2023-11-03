#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "tasMin.h"
tasMin * creerTas(int tailleMax){
  tasMin * tas = malloc(sizeof(tasMin));
  tas->contenu = malloc(tailleMax * sizeof(sommet));
  tas->positions = malloc(tailleMax * sizeof(int));
  tas->capacite = tailleMax;
  tas->taille = 0;
  return tas;
}

bool estVideTas(tasMin * tas){
  return !tas->taille;
}

void ech(sommet * a, sommet *b){
  sommet * temp = malloc(sizeof(sommet));
  memcpy(temp,a,sizeof(sommet));
  memcpy(a,b,sizeof(sommet));
  memcpy(b,temp,sizeof(sommet));
  free(temp);
}

// fonction qui echange deux sommets dans le tas
void echange(tasMin * t, int posa, int  posb) {
    ech(t->contenu + posa,t->contenu + posb);
    t->positions[t->contenu[posb].id] = posb;
    t->positions[t->contenu[posa].id] = posa;
}

// l'arbre est un tas min, donc complet à gauche, on peut donc utiliser un tableau pour
// le représenter, et accéder aux fils et au parent d'un noeud i par les formules suivantes :
int parent (int i) {
    return (i-1) / 2;
}
int filsGauche (int i) {
    return 2* i + 1;
}
int filsDroit (int i) {
    return 2 * i + 2;
}

int indiceMinfils(tasMin * t, int pos){
  return t->contenu[filsGauche(pos)].dist < t->contenu[filsDroit(pos)].dist ? 
    filsGauche(pos) : filsDroit(pos);
}

sommet * extraction(tasMin * tas){
  if(!estVideTas(tas)){
    echange(tas,tas->taille-1,0);
    int pos = 0;
    int mini = 0;
    while(filsDroit(pos) < tas->taille && 
    tas->contenu[(mini = indiceMinfils(tas,pos))].dist < tas->contenu[pos].dist){
      echange(tas,mini,pos);
      pos = mini;
    }
  }
  tas->taille--;
  return tas->contenu + tas->taille;
}

void printTas(tasMin * tas){
  printf("Tas : ");
  for(int i=0;i<tas->taille;i++){
    printf("%d ",tas->contenu[i].id);
  }
  printf("\n");
}

void pushUp(tasMin * tas, int pos){
  while(pos > 0 && tas->contenu[parent(pos)].dist > tas->contenu[pos].dist){
    echange(tas,parent(pos),pos);
    pos = parent(pos);
  }
}

void insertion(tasMin * tas,sommet *a){
  if(tas->taille == tas->capacite){
    printf("il n'y a plus de place ! :'(");
    return;
  }
  int pos = tas->taille;
  tas->taille++;
  tas->contenu[pos].id = a->id;
  tas->contenu[pos].dist = a->dist;
  tas->contenu[pos].preced = a->preced;
  tas->positions[a->id] = pos;
  pushUp(tas,pos);
}

void changerPoids(tasMin * tas,int som, int poids){
  // on suppose que le nouveau poids fait forcément remonter dans l'arbre
  tas->contenu[tas->positions[som]].dist = poids;
  pushUp(tas,tas->positions[som]);
}

void changerPreced(tasMin * tas,int som, int preced){
  tas->contenu[tas->positions[som]].preced = preced;
}

int getPreced(tasMin * tas,int som){
  return tas->contenu[tas->positions[som]].preced;  
}

int getPoids(tasMin * tas,int som){
  return tas->contenu[tas->positions[som]].dist;
}

void freeTas(tasMin * tas){
  free(tas->contenu);
  free(tas->positions);
  free(tas);
}

int TasMin(void){
  tasMin * tas = creerTas(20);
  srand(time(NULL));
  for(int i=0;i<15;i++){
    sommet a;
    a.id = i;
    a.dist = rand()%100;
    a.preced = -1;
    printf("%d ",a.id);
    printf("Insertion %d\n",a.dist);
    insertion(tas,&a);
  }
  printTas(tas);
  for(int i=0;i<15;i++){
    int v = extraction(tas)->dist;
    printf("Extraction %d\n",v);
  }
  freeTas(tas);
  return 0;
}
/*int main(void){
  return TasMin();
}*/
