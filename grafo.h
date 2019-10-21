#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <cstdlib>
#include <math.h>
#include <stack>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

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
		typedef vector<Node<pair<float,float>>*> node_list;
		typedef vector<Edge<float>*> edge_list;
		typedef Node<pair<float,float>>* node_t;

		node_list nodes;
		edge_list edges;

	public:
		Grafo() = default;//Default
		Grafo(Grafo* miGrafo);//Copia
		Grafo(int opcion);//Parametro

		void addNode(pair<float,float> val);
		void addEdge(int start, int end);
		void addEdge(int start, int end, float weight);

		void deleteNode(int index);
		void deleteEdge(int start, int end);

		int nodeGrade(int index);
		bool bfs(int starf, int find);
		bool dfs(int starf, int find);
		bool dfs_connected(int sartf);
		void dfs_connected(stack<int>& pila, vector<int>& visited, Node<pair<float,float>>* curr);
		vector<Edge<float>*> non_decreasing_edges();


		node_list getNodes(){
			return nodes;
		}

		~Grafo();
};

//Falta editar Copia para pasarle los edges
template< bool V>
Grafo<pair<float,float>,V>::Grafo(Grafo* miGrafo){
	for(auto node: miGrafo->nodes){
		nodes.emplace_back(new Node<pair<float,float>>(node->value));
		for(auto edge: node->edges){
			nodes[nodes.size()-1]->edges.emplace_back(new Edge<float>(edge->start,edge->end,edge->weight));
		}

	}
}

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
		cout << "Loops not allowed: " << start <<" -> "<< end << endl;
		return;
	}
	Edge<float>* nedge = new Edge<float>(start, end, weight);
	cout << "New edge: " << start << " -> " << end << " - weight: " << weight << endl;
	nodes[start]->edges.emplace_back(nedge);

	cout << "New edge: " << end << " -> " << start << " - weight: " << weight << endl;
	nodes[end]->edges.emplace_back(nedge);
	edges.emplace_back(nedge);
}

template<>
void Grafo<pair<float,float>,true>::addEdge(int start, int end, float weight){
	if (start == end){
		cout << "Loops not allowed\n" << start << " -> " << end << endl;
		return;
	}
	Edge<float>* nedge = new Edge<float>(start, end, weight);
	nodes[start]->edges.emplace_back(nedge);
	edges.emplace_back(nedge);
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(int start, int end){
	if (start == end){
		cout << "Loops not allowed\n" << start << " -> " << end << endl;
		return;
	}
	float weight = pow(pow(nodes[start]->value.first-nodes[end]->value.first,2)-pow(nodes[start]->value.second-nodes[end]->value.second,2),2);
	Edge<float>* nedge = new Edge<float>(start, end, weight);

	nodes[start]->edges.emplace_back(nedge);
	nodes[end]->edges.emplace_back(nedge);
	edges.emplace_back(nedge);
}

template<>
void Grafo<pair<float,float>,true>::addEdge(int start, int end){
	if(start == end){
		cout<<"Loops not allowed\n"<<start<<" -> "<<end<<endl;
		return;
	}
	float weight = pow(pow(nodes[start]->value.first-nodes[end]->value.first,2)-pow(nodes[start]->value.second-nodes[end]->value.second,2),2);
	Edge<float>* nedge = new Edge<float>(start, end, weight);
	nodes[start]->edges.emplace_back(new Edge<float>(start, end, weight));
	edges.emplace_back(nedge);
}


template<bool V>
void Grafo<pair<float,float>,V>::deleteNode(int index){

	Node<pair<float,float>>* temp = nullptr;

	temp = nodes[index];

	nodes[index] = nullptr;

	vector<int> connections;


	for(auto edge : temp->edges){
		cout<<edge->start<<" -> "<<edge->end<<" deleted."<<endl;
		if(!V){
			connections.push_back(edge->end);
		}
		delete edge;
	}

	delete temp;

	if(!V){
		for(int i = 0; i < connections.size(); i++){
			temp = nodes[connections[i]];
			cout<<"Checking node: "<<connections[i]<<endl;
			for(auto it = temp->edges.begin(); it != temp->edges.end(); it++){
				if((*it)->end == index){
					cout<<(*it)->start<<" -> "<<(*it)->end<<" deleted from node: "<<connections[i]<<endl;
					delete (*it);
					temp->edges.erase(it);
					break;
				}
			}
		}
	}
	
	cout<<"Node "<<index<<" deleted.\n";
}

//falta editar para que funcione con el nuevo vector implementado
template<bool V>
void Grafo<pair<float,float>,V>::deleteEdge(int start, int end){
	Node<pair<float,float>>* temp = nodes[start];

	for(auto it = temp->edges.begin(); it != temp->edges.end(); it++){
		if((*it)->start == start && (*it)->end == end){
			temp->edges.erase(it);
			break;
		}
	}

	if(!V){
		Node<pair<float,float>>* temp = nodes[end];

		for(auto it = temp->edges.begin(); it != temp->edges.end(); it++){
			if((*it)->start == start && (*it)->end == end){
				delete (*it);
				temp->edges.erase(it);
				break;
			}
		}
	}

	cout<<"Edge "<<start<<" -> "<<end<<" deleted.\n";

}

template<bool V>
int Grafo<pair<float,float>,V>::nodeGrade(int index){
	return nodes[index]->edges.size();
}

template<bool V>
bool Grafo<pair<float,float>,V>::bfs(int start, int find){

	queue<int> nodos;

	vector<int> visited(nodes.size(),0);

	nodos.push(start);

	Node<pair<float,float>>* current = nullptr;

	while(!nodos.empty()){

		current = nodes[nodos.front()];
		nodos.pop();

		for(auto edge: current->edges){
			if(edge->end == find){
				return true;
			}
			else if(!visited[edge->end]){
				nodos.push(edge->end);
				visited[edge->end] = 1;
			}
		}
	}
	return false;
}

template<bool V>
bool Grafo<pair<float,float>,V>::dfs(int start, int find){

	stack<int> nodos;

	vector<int> visited(nodes.size(),0);

	nodos.push(start);

	Node<pair<float,float>>* current = nullptr;

	while(!nodos.empty()){

		current = nodes[nodos.top()];
		nodos.pop();

		for(auto edge: current->edges){
			if(edge->end == find){
				return true;
			}
			else if(!visited[edge->end]){
				nodos.push(edge->end);
				visited[edge->end] = 1;
			}
		}
	}
	return false;

}
//=====================================================================================> DFS_CONNECTED 
template<bool V>
bool Grafo<pair<float,float>,V>::dfs_connected(int start){

	stack<int> pila;
	vector<int> visited(nodes.size(),0);
	pila.push(start);
	visited[start] = 1;
	Node<pair<float,float>>* curr = nullptr;

	while(!pila.empty()){
		curr = nodes[pila.top()];
		cout << "(" << curr->value.first << "," << curr->value.second << ")" << " ";

		for (auto edge : curr->edges){
			if (!visited[edge->end]){
				pila.push(edge->end);
				visited[edge->end] = 1;
				dfs_connected(pila,visited,nodes[edge->end]);
			}
		}

		for (auto valor : visited){
			if (!valor){
				return false;
			}
		}
		return true;
	}
}

template<bool V>
void Grafo<pair<float,float>,V>::dfs_connected(stack<int>& pila, vector<int>& visited, Node<pair<float,float>>* curr){
	cout << "(" << curr->value.first << "," << curr->value.second << ")" << " ";
	for (auto edge : curr->edges){
		if (!visited[edge->end]){
			pila.push(edge->end);
			visited[edge->end] = 1;
			dfs_connected(pila,visited,nodes[edge->end]);
		}
	}
	pila.pop();
}
//=====================================================================================|

template<bool V>
vector<Edge<float>*> Grafo<pair<float,float>,V>::non_decreasing_edges(){
	edge_list sorted_edges = edges;
	std::sort (sorted_edges.begin(), sorted_edges.end());
	return sorted_edges;
}

/*
=====================================================
  non_decreasing_edges no usando el vector de edges
=====================================================

template<bool V>
vector<Edge<float>*> Grafo<pair<float,float>,V>::non_decreasing_edges(){
	vector<Edge<float>*> orderedEdges;
	for (auto i : nodes)
		for (auto j : i->edges){
			cout << "(" << j->start << "," << j->end << ")" << " ";
			orderedEdges.emplace_back(j);
		}	
	std::sort (ordered_edges.begin(), orderedEdges.end());
	return orderedEdges;
}
*/


#endif
