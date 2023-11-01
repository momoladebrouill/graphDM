#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"

file * creerFile(void){
  file * f = calloc(1, sizeof(file));
  return f;
}

bool estVide(file * f){
  return !f->debut;
}

void enfile(file * f, int donnee){
  element * e = calloc(1, sizeof(element));
  e->donnee = donnee;
  if(estVide(f)){
    f->debut = e;
    f->fin = e;
  }else{
    f->fin->suivant = e;
    f->fin = e;
  }
}

int defile(file * f){
  int donnee = f->debut->donnee;
  element * e = f->debut;
  f->debut = f->debut->suivant;
  free(e);
  return donnee;
}

int main(void){
  file * exemple = creerFile();
  for(int i = 0; i < 10; i++){
    int donnee = rand() % 100;
    enfile(exemple, donnee);
    printf("Enfile %d\n", donnee);
  }
  for(int i = 0; i < 10; i++){
    printf("Defile %d\n", defile(exemple));
  }
  return 0;
}
