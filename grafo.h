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

		bool findEdgePair(vector<pair<float,float>> visited, pair<float,float> find);

		void addNode(pair<float,float> val);
		void addEdge(pair<float,float> start, pair<float,float> end); 
		void addEdge(pair<float,float> start, pair<float,float> end, float weight); 

		void deleteNode(pair<float,float> index); 
		void deleteEdge(pair<float,float> start, pair<float,float> end);  

		int nodeGrade(pair<float,float> index);
		bool bfs(pair<float,float> starf, pair<float,float> find); 
		bool dfs(pair<float,float> starf, pair<float,float> find); 
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
	}
	for(auto edge: miGrafo->edges){
		edges.emplace_back(new Edge<float>(edge->start, edge->end, edge->weight));
	}
}

template<bool V>
Grafo<pair<float,float>,V>::Grafo(int opcion){

}//Parametro

template<bool V>
Grafo<pair<float,float>,V>::~Grafo(){
	for(auto node: nodes){
		
		delete node;
	}
	for(auto edge: edges){
		delete edge;
	}
}

template<bool V>
bool Grafo<pair<float,float>,V>::findEdgePair(vector<pair<float,float>> visited, pair<float,float> find){
	for(auto item: visited){
		if(item == find){
			return true;
		}
	}
	return false;
}

template<bool V>
void Grafo<pair<float,float>,V>::addNode(pair<float,float> val){
	nodes.emplace_back(new Node<pair<float,float>>(val));
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(pair<float,float> start, pair<float,float> end, float weight){
	if(start == end){
		cout << "Loops not allowed\n";
		return;
	}
	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;
	edges.emplace_back(new Edge<float>(start, end, weight));

	cout << "New edge: (" << end.first<<","<<end.second << ") -> (" << start.first<<","<<start.second << ") - weight: " << weight << endl;	
	edges.emplace_back(new Edge<float>(end, start, weight));
}

template<>
void Grafo<pair<float,float>,true>::addEdge(pair<float,float> start, pair<float,float> end, float weight){
	if (start == end){
		cout << "Loops not allowed\n";
		return;
	}

	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;
	edges.emplace_back(new Edge<float>(start, end, weight));
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(pair<float,float> start, pair<float,float> end){
	if (start == end){
		cout << "Loops not allowed\n";
		return;
	}
	
	float weight = pow(pow(start.first-end.first,2)-pow(start.second-end.second,2),2);

	edges.emplace_back(new Edge<float>(start, end, weight));
	edges.emplace_back(new Edge<float>(end, start, weight));

	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;


}

template<>
void Grafo<pair<float,float>,true>::addEdge(pair<float,float> start, pair<float,float> end){
	if(start == end){
		cout<<"Loops not allowed\n";
		return;
	}

	float weight = pow(pow(start.first-start.first,2)-pow(start.second-end.second,2),2);
	edges.emplace_back(new Edge<float>(start, end, weight));

	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;

}


template<bool V>
void Grafo<pair<float,float>,V>::deleteNode(pair<float,float> index){

	for(auto it = nodes.begin(); it != nodes.end(); it++){
		if((*it)->value == index){
			cout<<"Deleting node: ("<<(*it)->value.first<<","<<(*it)->value.second<<")\n";
			delete (*it);
			nodes.erase(it);
			break;
		}
	}

	for(auto it = edges.begin(); it != edges.end(); it++){
		if((*it)->end == index || (*it)->start == index){
			cout<<"Deleting edge: ("<<(*it)->start.first<<","<<(*it)->start.second<<") -> ("<<(*it)->end.first<<","<<(*it)->end.second<<")\n";
			delete (*it);
			edges.erase(it--);
			
		}
	}
	
	cout<<"Node ("<<index.first<<","<<index.second<<") deleted.\n";
}

template<bool V>
void Grafo<pair<float,float>,V>::deleteEdge(pair<float,float> start, pair<float,float> end){

	for(auto it = edges.begin(); it != edges.end(); it++){
		if((*it)->start == start && (*it)->end == end){
			delete (*it);
			edges.erase(it--);
			if(V){
				break;
			}
		}
		else if((*it)->start == end && (*it)->end == start && !V){
			delete (*it);
			edges.erase(it--);
		}
	}

	cout<<"Edge (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") deleted.\n";

}

template<bool V>
int Grafo<pair<float,float>,V>::nodeGrade(pair<float,float> index){
	int grade = 0;

	for(auto edge: edges){
		if(edge->start.first == index.first && edge->start.second == index.second){
			grade++;
		}
	}
	return grade;
}

template<bool V>
bool Grafo<pair<float,float>,V>::bfs(pair<float,float> start, pair<float,float> find){

	queue<pair<float,float>> nodos;

	vector<pair<float,float>> visited;

	pair<float,float> current;

	nodos.push(start);
	visited.push_back(start);

	cout<<"\n";

	while(!nodos.empty()){

		current = nodos.front();

		cout<<"Current node: ("<<current.first<<","<<current.second<<")\n";	


		
		nodos.pop();

		if(current == find){
				return true;
			}

		for(auto edge: edges){
			if(edge->start == current && !findEdgePair(visited, edge->end)){
				cout<<"Inserting from edge: ("<<current.first<<","<<current.second<<") -> ("<<edge->end.first<<","<<edge->end.second<<")\n";
					nodos.push(edge->end);
					visited.push_back(edge->end);

			}
		}

		
	}

	return false;

}

template<bool V>
bool Grafo<pair<float,float>,V>::dfs(pair<float,float> start, pair<float,float> find){

	stack<pair<float,float>> nodos;

	vector<pair<float,float>> visited;

	pair<float,float> current;

	nodos.push(start);
	visited.push_back(start);

	cout<<"\n";

	while(!nodos.empty()){

		current = nodos.top();

		cout<<"Current node: ("<<current.first<<","<<current.second<<")\n";	


		
		nodos.pop();

		if(current == find){
				return true;
			}

		for(auto edge: edges){
			if(edge->start == current && !findEdgePair(visited, edge->end)){
					cout<<"Inserting from edge: ("<<current.first<<","<<current.second<<") -> ("<<edge->end.first<<","<<edge->end.second<<")\n";
					nodos.push(edge->end);
					visited.push_back(edge->end);

			}
		}

		
	}

	return false;

}
/*
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
*/

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

