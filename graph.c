#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#include "pile.c"
#include "file.c"

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


file * dfs(graph *g, int src,bool* visited){
  pile * to_visit = creerPile();
  empile(to_visit,src);
  file * f = creerFile();
  while(!estVidePile(to_visit) && !visited[src = depile(to_visit)]){
    arete * current = g->aretes[src];
    while(current){
      if(!visited[current->dst])
        empile(to_visit,current->dst);
      current = current->suivant;
    }
    visited[src] = true;
    enfile(f, src);
 }
 return f;
}

file * bfs(graph *g, int src){
  int * visited = calloc(g->s,sizeof(int));
  file * to_visit = creerFile();
  enfile(to_visit,src);
  file * f = creerFile();
  while(!estVideFile(to_visit) && !visited[src = defile(to_visit)]){
    arete * current = g->aretes[src];
    while(current){
      if(!visited[current->dst])
        enfile(to_visit,current->dst);
      current = current->suivant;
    }
    visited[src] = true;
    enfile(f, src);
 }
 free(visited);
 return f;
}

graph * grapheMirroir(graph * g){
  graph * gr = creerGraph(g->s);
  for(int i=0;i<g->s;i++){
    arete * current = g->aretes[i];
    while(current){
      ajouterArete(gr,current->dst,current->src,current->poids);
      current = current->suivant;
    }
  }
  return gr;
}

int * kosaraju(graph *g){
  // renvoie les composantes fortement connexes maximales
  pile * ordre = creerPile();
  bool * visite = calloc(g->s,sizeof(bool));
  for(int i=0;i<g->s;i++){
    if(!visite[i]){
       file * f = dfs(g,i,visite);
       while(!estVideFile(f))
          empile(ordre,defile(f));
    }
  }
  graph * rg = grapheMirroir(g);
  bool * rvisite = calloc(rg->s,sizeof(bool));
  int ncomp = 0;
  int * comp = calloc(g->s,sizeof(int));
  while(!estVidePile(ordre)){
    int ia = depile(ordre);
    if(!rvisite[ia]){
      ncomp++;
      file * f = dfs(rg,ia,rvisite);
      while(!estVideFile(f))
        comp[defile(f)] = ncomp;
    }
  }
  return comp;
}


int main(void){
  graph * exemple = creerGraph(11);

  // matrice d'arete pour simplifier l'ajout dans le graphe
  int src[]= {0,1,1,2,2,2,3,3,4,4 ,5,6,6,7,7 ,8,9,9};
  int dst[] = {3,3,5,0,1,4,2,7,2,10,6,5,8,8,10,9,7,10};
  for(int i=0;i<18;i++)ajouterArete(exemple,src[i],dst[i],1);

  printFile(dfs(exemple,0,calloc(exemple->s,sizeof(int))));
  printFile(bfs(exemple,0));
  
  int * comp = kosaraju(exemple);
  printf("Kosaraju : ");
  for(int i=0;i<exemple->s;i++)
    printf("%d:%d%c",i,comp[i],i==exemple->s-1 ? '\n' : ',' );
  return 0;
}
