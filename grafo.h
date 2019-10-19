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
class Grafo<pair<float,float>,V>
{
private:
    typedef vector<Node<pair<float,float>>*> NodeList;

    typedef Node<pair<float,float>>* node_t;

    NodeList nodes;

public:
    Grafo() = default;//Default
    Grafo(Grafo* miGrafo);//Copia
    Grafo(int opcion);//Parametro

    void addNode(pair<float,float> val);
    void addEdge(int start, int end);
    void addEdge(int start, int end, float weight);
        
    NodeList getNodes(){
        return nodes;
    }

    ~Grafo();
};


template< bool V>
Grafo<pair<float,float>,V>::Grafo(Grafo* miGrafo){
    for(auto node: miGrafo->nodes){
        nodes.emplace_back(new Node<pair<float,float>>(node->value));
        for(auto edge: node->edges){
            nodes[nodes.size()-1]->edges.emplace_back(new Edge<float>(edge->start,edge->end,edge->weight));
        }
        
    }
}//Copia

template<bool V>
Grafo<pair<float,float>,V>::Grafo(int opcion){

}//Parametro

template<bool V>
Grafo<pair<float,float>,V>::~Grafo(){
    for(auto node: nodes){
        for(auto edge: node->edges){
            delete edge;
        }
        delete node;
    }
}

template<bool V>
void Grafo<pair<float,float>,V>::addNode(pair<float,float> val){
    nodes.emplace_back(new Node<pair<float,float>>(val));
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(int start, int end, float weight){
    if(start == end){
        cout<<"Loops not allowed\n";
        return;
    }
    nodes[start]->edges.emplace_back(new Edge<float>(start, end, weight));
    nodes[end]->edges.emplace_back(new Edge<float>(start, end, weight));
}

template<>
void Grafo<pair<float,float>,true>::addEdge(int start, int end, float weight){
    if(start == end){
        cout<<"Loops not allowed\n";
        return;
    }
    nodes[start]->edges.emplace_back(new Edge<float>(start, end, weight));
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(int start, int end){
    if(start == end){
        cout<<"Loops not allowed\n";
        return;
    }
    float weight = pow(pow(nodes[start]->value.first-nodes[end]->value.first,2)-pow(nodes[start]->value.second-nodes[end]->value.second,2),2);
    nodes[start]->edges.emplace_back(new Edge<float>(start, end, weight));
    nodes[end]->edges.emplace_back(new Edge<float>(start, end, weight));
}

template<>
void Grafo<pair<float,float>,true>::addEdge(int start, int end){
    if(start == end){
        cout<<"Loops not allowed\n";
        return;
    }
    float weight = pow(pow(nodes[start]->value.first-nodes[end]->value.first,2)-pow(nodes[start]->value.second-nodes[end]->value.second,2),2);
    nodes[start]->edges.emplace_back(new Edge<float>(start, end, weight));
}



#endif
