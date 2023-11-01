#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "tasMin.h"

tasMin * creerTas(int tailleMax){
  tasMin * tas = malloc(sizeof(tasMin));
  tas->contenu = malloc(tailleMax * sizeof(arete));
  tas->capacite = tailleMax;
  tas->taille = 0;
  return tas;
}

bool estVide(tasMin * tas){
  return !tas->taille;
}

// fonction qui echange deux aretes dans le tas
void echange (arete* a, arete* b) {
    arete temp = *a;
    *a = *b;
    *b = temp;
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

void insertion(tasMin * tas,arete *a){
  if(tas->taille == tas->capacite){
    printf("il n'y a plus de place ! :'(");
    return;
  }
  int pos = tas->taille;
  tas->taille++;
  memcpy(&(tas->contenu[pos]),a,sizeof(a));
  while(pos > 0 && tas->contenu[parent(pos)]->poids > tas->contenu[pos]->poids){
    echange(tas->contenu[parent(pos)],tas->contenu[pos]);
    pos = parent(pos);
  }
}

int indiceMinfils(tasMin * t, int pos){
  return t->contenu[filsGauche(pos)]->poids < t->contenu[filsDroit(pos)]->poids ? 
    filsGauche(pos) : filsDroit(pos);
}

arete * extraction(tasMin * tas){
  if(!estVide(tas)){
    echange(tas->contenu[tas->taille],tas->contenu[0]);
    int pos = 0;
    int mini;
    while(tas->contenu[(mini = indiceMinfils(tas,pos))]->poids < tas->contenu[pos]->poids){
      echange(tas->contenu[mini],tas->contenu[pos]);
      pos = mini;
    }
  }
  tas->taille--;
  return tas->contenu[tas->taille+1];
}

int main(void){
  tasMin * tas = creerTas(100);
  srand(time(NULL));
  for(int i=0;i<100;i++){
    arete a;
    a.poids = rand()%100;
    printf("Insertion %d\n",a.poids);
    insertion(tas,&a);
  }
  for(int i=0;i<100;i++){
    printf("Extraction %d\n",extraction(tas)->poids);
  }
}
