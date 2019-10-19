#include <iostream>
#include "grafo.h"

using namespace std;

int main(){


    Grafo<pair<float,float>,false>* nodGrafo = new Grafo<pair<float,float>,false>();
    Grafo<pair<float,float>,true>* dGrafo = new Grafo<pair<float,float>,true>();

    nodGrafo->addNode(pair<float,float>(1,1));
    nodGrafo->addNode(pair<float,float>(2,2));
    nodGrafo->addEdge(0,1,3);

    //Grafo<pair<int,int>,false>* _nodGrafo = new Grafo<pair<int,int>,false>(nodGrafo);

    cout<<nodGrafo->getNodes()[0]->value.first<<endl;
    cout<<nodGrafo->getNodes()[1]->value.first<<endl;
    cout<<nodGrafo->getNodes()[0]->edges[0]->weight<<endl;




    return 0;
}   