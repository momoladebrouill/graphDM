typedef struct arete {
    int src;
    int dst;
    int poids;
    struct arete * suivant;
} arete;

typedef struct {
    int s;
    arete **aretes;
} graph;

typedef struct {
    int dist;
    int preced;
} sommet;


