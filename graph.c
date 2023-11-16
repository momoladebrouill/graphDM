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
  int ncomp = 0; // numéro de la CFC
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

pile * djikstra(graph *g, int src, int dst){
  // initialisation du tas, on met la distance à INT_MAX pour tous les sommets et comme précédent -1
  tasMin * tas = creerTas(g->s);
  sommet a;
  a.dist = INT_MAX-1; // pour éviter de cycler quand on fait +1 lors de la comparaison
  a.preced = -1;
  for(int i = 0;i<g->s;i++){
    a.id = i;
    insertion(tas,&a);
  }

  // on met la distance à 0 pour le sommet de départ
  changerPoids(tas,src,0);
  
  // on marque chaque sommet avec sa distance minimale avec la source
  int position = src;
  bool * parcouru = calloc(g->s, sizeof(bool));
  while(!estVideTas(tas) && position != dst){
    // on prend le sommet avec la plus petite distance non déjà parcouru
    sommet * sautVers;
    while(!estVideTas(tas)){
      sautVers = extraction(tas);
      if(parcouru[sautVers->id]){ // si on l'a déjà parcouru, on le réinsère.
        insertion(tas,sautVers);
      }else
        break;
    }

    position = sautVers->id;
    arete * arr = g->aretes[position];
    while(arr){
      int nouveauPoids = arr->poids + getPoids(tas,position);
      if(getPoids(tas,arr->dst) > nouveauPoids){
        changerPoids(tas,arr->dst,nouveauPoids);
        changerPreced(tas,arr->dst,arr->src);
      }
      arr = arr->suivant;
    }
    parcouru[position] = true;
  }

  // on remonte depuis la destination à la source
  pile * p = creerPile();
  if(getPreced(tas,dst) == -1){
    freeTas(tas);
    free(parcouru);
    printf("Pas de chemin :'(\n");
    return p;
  }

  position = dst;
  while(position!=src){
    empile(p,position);
    position = getPreced(tas,position);
  }

  empile(p,src);
  freeTas(tas);
  free(parcouru);
  return p;
}

void printGraph(graph * g){
  printf("\033[1;34mGraphe\033[0m\n");
  for(int i=0;i<g->s;i++){
    printf("\033[0;3%dm%d\033[0m : ",i,i);
    arete * current = g->aretes[i];
    while(current){
      printf("\033[0;3%dm%d\033[0m(%d) ",current->dst,current->dst,current->poids);
      current = current->suivant;
    }
    printf("\n");
  }
}

bool estConnexe(graph * g){
  bool * visited = calloc(g->s,sizeof(bool));
  file * f = bfs(g,0);
  while(!estVideFile(f)){
    visited[defile(f)] = true;
  }
  freeFile(f);
  for(int i=0;i<g->s;i++)
    if(!visited[i]){
      free(visited);
      return false;
    }
  free(visited);
  return true;
}

  


int Graph(void){
  printf("\033[1;34mGraphe\033[0m\n");
  graph * exemple = creerGraph(11);

  // matrice d'arete pour simplifier l'ajout dans le graphe
  int src[]= {0,1,1,2,2,2,3,3,4,4 ,5,6,6,7,7 ,8,9,9};
  int dst[] = {3,3,5,0,1,4,2,7,2,10,6,5,8,8,10,9,7,10};
  for(int i=0;i<18;i++)ajouterArete(exemple,src[i],dst[i],1);
  
  bool * visited = calloc(exemple->s,sizeof(int));
  
  printf("\033[1;35mDFS\033[0m\n");
  file * d = dfs(exemple,0,visited);
  printFile(d);
  freeFile(d);
  free(visited);

  printf("\033[1;35mBFS\033[0m\n");
  file * f = bfs(exemple,0);
  printFile(f);
  freeFile(f);

  printf("\033[1;35mDjikstra\033[0m\n");
  pile * p = djikstra(exemple,0,10);
  printPile(p); 
  freePile(p);
  
  printf("\033[1;35mKosaraju\033[0m\n");
  int * comp = kosaraju(exemple);
  for(int i=0;i<exemple->s;i++)
    printf("\033[0;3%dm%d\033[0m%c",comp[i],i,i==exemple->s-1 ? '\n' : ',' );
  free(comp);

  printf("\033[1;35mGraphe\033[0m\n");
  printGraph(exemple);

  freeGraph(exemple);
  return 0;
}
