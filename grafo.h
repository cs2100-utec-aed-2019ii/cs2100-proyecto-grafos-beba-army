#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <cstdlib>
#include <math.h>

#include "Node.h"

template<typename T, bool V>
class Grafo
{
private:
    typedef vector<Node<T>*> NodeList;

    NodeList nodes;

public:
    Grafo() = default;//Default
    Grafo(Grafo* miGrafo);//Copia
    Grafo(int opcion);//Parametro

    ~Grafo();
};


template<bool V>
class Grafo<pair<int,int>,V>
{
private:
    typedef vector<Node<pair<int,int>>*> NodeList;

    typedef Node<pair<int,int>>* node_t;

    NodeList nodes;

public:
    Grafo() = default;//Default
    Grafo(Grafo* miGrafo);//Copia
    Grafo(int opcion);//Parametro

    void addNode(pair<int,int> val);
    void addEdge(node_t start, node_t end);
    void addEdge(node_t start, node_t end, float weight);
        


    NodeList getNodes(){
        return nodes;
    }

    ~Grafo();
};



template< bool V>
Grafo<pair<int,int>,V>::Grafo(Grafo* miGrafo){

}//Copia

template<bool V>
Grafo<pair<int,int>,V>::Grafo(int opcion){

}//Parametro

template<bool V>
void Grafo<pair<int,int>,V>::addNode(pair<int,int> val){
    nodes.emplace_back(new Node<pair<int,int>>(val));
}

template<bool V>
void Grafo<pair<int,int>,V>::addEdge(node_t start, node_t end, float weight){
    if(start == end){
        cout<<"Loops not allowed\n";
        return;
    }
    start->edges.emplace_back(new Edge<pair<int,int>,float>(start, end, weight));
    end->edges.emplace_back(new Edge<pair<int,int>, float>(start, end, weight));
}

template<>
void Grafo<pair<int,int>,true>::addEdge(node_t start, node_t end, float weight){
    if(start == end){
        cout<<"Loops not allowed\n";
        return;
    }
    start->edges.emplace_back(new Edge<pair<int,int>,float>(start, end, weight));
}



#endif
