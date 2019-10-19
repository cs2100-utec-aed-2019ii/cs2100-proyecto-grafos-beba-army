#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cstdlib>
#include <math.h>

using namespace std;

template<typename T, typename P>
struct Edge;

template<typename T>
struct Node 
{

    T value;


    Node(T val);
    ~Node();
};


template<>
struct Node<pair<int,int>>{

    typedef pair<int,int> node_t;
    typedef vector<Edge<node_t,float>*> EdgeList;

    EdgeList edges;
    node_t value;

    Node(node_t val);
    ~Node();

};

template<typename T>
Node<T>::Node(T val){
    value = val;
}


Node<pair<int,int>>::Node(pair<int,int> val){
    value = val;
}


//-------------------------------------------EDGE----------------------------
template<typename T, typename P>
struct Edge
{
    
};



template<>
struct Edge<pair<int,int>, float>
{
    typedef pair<int,int> node_t;

    Node<node_t>* start;
    float weight;
    Node<node_t>* end;

    Edge(Node<node_t>* start, Node<node_t>* end); //Euclidean distance
    Edge(Node<node_t>* start, Node<node_t>* end, float _weight); //Parameter
    ~Edge();

    void getWeight();
};


void Edge<pair<int,int>, float>::getWeight(){
    weight =  pow(pow(start->value.first - end->value.first,2) + pow(start->value.second - end->value.second,2),0.5);
    
}


Edge<pair<int,int>, float>::Edge(Node<pair<int,int>>* start, Node<pair<int,int>>* end){
    this->start = start;

    this->end = end;

    getWeight();

}

Edge<pair<int,int>, float>::Edge(Node<pair<int,int>>* start, Node<pair<int,int>>* end, float weight){
    this->start = start;

    this->end = end;

}










#endif