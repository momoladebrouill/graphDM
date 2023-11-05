#include <time.h>
#include "graph.c"

int main()
{
    srand(time(NULL));
    Pile();
    File();
    TasMin();
    Graph();
    return 0;
}
