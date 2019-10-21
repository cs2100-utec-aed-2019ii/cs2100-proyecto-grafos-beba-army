#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cstdlib>
#include <math.h>

using namespace std;

template<typename T>
struct Edge;

template<typename T>
struct Node 
{

    T value;


    Node(T val);
    ~Node();
};


template<>
struct Node<pair<float,float>>{

    typedef pair<float,float> node_t;
    typedef vector<Edge<float>*> EdgeList;

    EdgeList edges;
    node_t value;

    Node(node_t val);
    ~Node();

};

template<typename T>
Node<T>::Node(T val){
    value = val;
}


Node<pair<float,float>>::Node(pair<float,float> val){
    value = val;
}

Node<pair<float,float>>::~Node(){

}


//-------------------------------------------EDGE----------------------------
template<typename T>
struct Edge
{
    
};



template<>
struct Edge<float>
{

    int start;
    float weight;
    int end;

    Edge(int start, int end); //Euclidean distance
    Edge(int start, int end, float _weight); //Parameter
		bool operator< (const Edge &other) const{
			return weight < other.weight;
		}
    ~Edge();

};




Edge<float>::Edge(int start, int end){
    this->start = start;

    this->end = end;


}

Edge<float>::Edge(int start, int end, float weight){
    this->start = start;
    this->weight = weight;
    this->end = end;

}


Edge< float>::~Edge(){

}







#endif
