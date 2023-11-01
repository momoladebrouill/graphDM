typedef struct element {
    int donnee;
    struct element *suivant;
} element;

typedef struct{
    element *sommet;
} pile;
