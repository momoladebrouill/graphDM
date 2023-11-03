#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"

#include "pile.c"
#include "file.c"
#include "tasMin.c"

graph * creerGraph(int n){
  graph * g = malloc(sizeof(graph));
  g->s = n;
  g->aretes = calloc(n,sizeof(arete)); // car NULL = 0
  return g;
}

void freeGraph(graph * g){
  for(int i=0;i<g->s;i++){
    arete * current = g->aretes[i];
    while(current){
      arete * tmp = current;
      current = current->suivant;
      free(tmp);
    }
  }
  free(g->aretes);
  free(g);
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
 freePile(to_visit);
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
 freeFile(to_visit);
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
       freeFile(f);
    }
  }
  free(visite);
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
      freeFile(f);
    }
  }
  freeGraph(rg);
  freePile(ordre);
  free(rvisite);
  return comp;
}

int min(int a, int b, bool * chg){
  *chg = a < b;
  return &chg ? a : b;
}

pile * djikstra(graph *g, int src, int dst){
  tasMin * tas = creerTas(g->s);
  bool * parcouru = calloc(g->s, sizeof(bool));
  sommet a;
  a.dist = INT_MAX;
  a.preced = -1;
  for(int i=0;i<g->s;i++){
    a.id = i;
    insertion(tas,&a);
  }
  changerPoids(tas,src,0);
  int current = src;
  printTas(tas);
  while(current != dst){
    printf("current : %d\n",current);
    arete * arr = g->aretes[current];
    while(arr){
      bool chang;
      changerPoids(tas,arr->dst,
      min(getPoids(tas,arr->dst),arr->poids + getPoids(tas,arr->src),&chang));
      changerPreced(tas,arr->dst,arr->src);
      arr = arr->suivant;
    }
    parcouru[current] = true;
    while(parcouru[current]) current = extraction(tas)->id;
  }
  int prec;
  for(int i=0;i<g->s;i++)
    printf("%d:%d\n",i,getPreced(tas,i));
  pile * p = creerPile();
  current = dst;
  if(getPreced(tas,current) == -1){
    freeTas(tas);
    free(parcouru);
    printf("Pas de chemin :'(\n");
    return p;
  }
  while(current!=src){
    prec = getPreced(tas,current);
    empile(p,prec);
    current = prec;
  }
  freeTas(tas);
  free(parcouru);
  return p;
}


int main(void){
  graph * exemple = creerGraph(11);

  // matrice d'arete pour simplifier l'ajout dans le graphe
  int src[]= {0,1,1,2,2,2,3,3,4,4 ,5,6,6,7,7 ,8,9,9};
  int dst[] = {3,3,5,0,1,4,2,7,2,10,6,5,8,8,10,9,7,10};
  for(int i=0;i<18;i++)ajouterArete(exemple,src[i],dst[i],1);
  
  bool * visited = calloc(exemple->s,sizeof(int));
  
  file * d = dfs(exemple,0,visited);
  printFile(d);
  freeFile(d);
  free(visited);

  file * f = bfs(exemple,0);
  printFile(f);
  freeFile(f);

  pile * p = djikstra(exemple,0,10);
  printPile(p); 
  freePile(p);
  
  int * comp = kosaraju(exemple);
  printf("Kosaraju : ");
  for(int i=0;i<exemple->s;i++)
    printf("%d:%d%c",i,comp[i],i==exemple->s-1 ? '\n' : ',' );
  free(comp);
  freeGraph(exemple);
  return 0;
}
