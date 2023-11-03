typedef struct {
  sommet * contenu;
  int taille;
  int * positions; // position[indice du sommet] = position dans l'arbre
  int capacite;
} tasMin;
