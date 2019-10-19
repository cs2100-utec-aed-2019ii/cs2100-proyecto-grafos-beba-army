#include <iostream>
#include "grafo.h"

using namespace std;

int main(){


    Grafo<pair<int,int>,true>* testGrafo = new Grafo<pair<int,int>,true>();

    testGrafo->addNode(pair<int,int>(1,1));
    testGrafo->addNode(pair<int,int>(2,2));
    testGrafo->addEdge(testGrafo->getNodes()[0],testGrafo->getNodes()[1]);

    cout<<testGrafo->getNodes()[0]->value.first<<endl;
    cout<<testGrafo->getNodes()[1]->value.first<<endl;



    return 0;
}   