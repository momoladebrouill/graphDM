#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file.h"

file * creerFile(void){
  file * f = calloc(1, sizeof(file));
  return f;
}

bool estVideFile(file * f){
  return !f->debut;
}

void enfile(file * f, int donnee){
  element * e = calloc(1, sizeof(element));
  e->donnee = donnee;
  if(estVideFile(f)){
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

void printFile(file * f){
  element * e = f->debut;
  printf("File: ");
  while(e){
    printf("%d ", e->donnee);
    e = e->suivant;
  }
  printf("\n");
}

void freeFile(file * f){
    while(!estVideFile(f)){
      defile(f);
    }
    free(f);
}

int File(void){
  printf("\033[1;34mFile\033[0m\n");
  file * exemple = creerFile();
  for(int i = 0; i < 10; i++){
    int donnee = rand() % 100;
    enfile(exemple, donnee);
    printf("Enfile %d\n", donnee);
  }
  printFile(exemple);
  for(int i = 0; i < 10; i++){
    printf("Defile %d\n", defile(exemple));
  }
  freeFile(exemple);
  return 0;
}
