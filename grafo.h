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
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <GL/glut.h>

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

		void save();
		vector<pair<float,float>> getNeighbors(pair<float,float> index);
		bool inNeighborhood(pair<float,float> start, pair<float,float> neighbor);


		node_list getNodes(){
			return nodes;
		}
		edge_list getEdges(){
			return edges;
		}

		~Grafo();
};

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
	switch (opcion)
	{
	case 1://vtk
		/* code */
		break;


	case 2:{//From disk ================================= Asumimos que el grafo esta correcto??????????????

		string read;
		int numNodes;

		float val1, val2, val3, val4, weight;

		ifstream file;

		file.open("graph.txt");

		getline(file,read);
		stringstream stream(read);

		stream>>numNodes;


		if(file.is_open()){
			for(int i = 0; i < numNodes; i++){

				getline(file,read);
				stringstream stream(read);

				stream>>val1;
				stream>>val2;

				nodes.emplace_back(new Node<pair<float,float>>(pair<float,float>(val1,val2)));

			}

			while(getline(file,read)){
				stringstream stream(read);
				stream>>val1;
				stream>>val2;
				stream>>val3;
				stream>>val4;
				stream>>weight;

				edges.emplace_back(new Edge<float>(pair<float,float>(val1,val2),pair<float,float>(val3,val4),weight));

			}

		}

	// cout<<"\n\nGraph read result:\n";
	// for(auto node : nodes){
	// 	cout<<node->value.first<<" "<<node->value.second<<"\n";
	// }
	// for(auto edge : edges){
	// 	cout<<edge->start.first<<" "<<edge->start.second<<" "<<edge->end.first<<" "<<edge->end.second<<" "<<edge->weight<<"\n";
	// }


		file.close();
		break;
	}


	case 3:{//Random

		srand(time(NULL));

		int numNodes = rand() % 10 + 1;
		int numEdges = (numNodes == 1)?0: rand() % (numNodes*(numNodes-1));

		

		float node1, node2, weight;
		pair<float,float> val1, val2;

		for(int i = 0; i < numNodes; i++){
			val1 = pair<float,float>(pow(-1,rand() % 2)*(rand() % 585),pow(-1,rand() % 2)*(rand() % 585) );
			addNode(val1);
		}

		while(edges.size() < numEdges){

			node1 = rand() % numNodes;
			node2 = rand() % numNodes;

			val1 = getNodes()[node1]->value;
			val2 = getNodes()[node2]->value;

			weight = (rand() % 100) / pow(10,(rand() % 2 + 1));

			addEdge(val1, val2, weight);
		}

	cout<<"\n\nRandom graph result:\n";
	cout<<"Number of nodes: "<<numNodes<<"\n";
	for(auto node : nodes){
		cout<<node->value.first<<" "<<node->value.second<<"\n";
	}
	cout<<"\nNumber of edges: "<<numEdges<<"\n";
	for(auto edge : edges){
		cout<<edge->start.first<<","<<edge->start.second<<" -> "<<edge->end.first<<","<<edge->end.second<<" : "<<edge->weight<<"\n";
	}

	}
	
	default:
		break;
	}

}//Parametro

template<>
Grafo<pair<float,float>,true>::Grafo(int opcion){
	switch (opcion)
	{
	case 1://vtk
		/* code */
		break;


	case 2:{//From disk ================================= Asumimos que el grafo esta correcto??????????????

		string read;
		int numNodes;

		float val1, val2, val3, val4, weight;

		ifstream file;

		file.open("graph.txt");

		getline(file,read);
		stringstream stream(read);

		stream>>numNodes;


		if(file.is_open()){
			for(int i = 0; i < numNodes; i++){

				getline(file,read);
				stringstream stream(read);

				stream>>val1;
				stream>>val2;

				nodes.emplace_back(new Node<pair<float,float>>(pair<float,float>(val1,val2)));

			}

			while(getline(file,read)){
				stringstream stream(read);
				stream>>val1;
				stream>>val2;
				stream>>val3;
				stream>>val4;
				stream>>weight;

				edges.emplace_back(new Edge<float>(pair<float,float>(val1,val2),pair<float,float>(val3,val4),weight));

			}

		}

	// cout<<"\n\nGraph read result:\n";
	// for(auto node : nodes){
	// 	cout<<node->value.first<<" "<<node->value.second<<"\n";
	// }
	// for(auto edge : edges){
	// 	cout<<edge->start.first<<" "<<edge->start.second<<" "<<edge->end.first<<" "<<edge->end.second<<" "<<edge->weight<<"\n";
	// }


		file.close();
		break;
	}


	case 3:{//Random

		srand(time(NULL));

		int numNodes = rand() % 5 + 1;
		int numEdges = rand() % ((numNodes*(numNodes-1)) + 1);
		bool duplicate;

		float node1, node2, weight;
		pair<float,float> val1, val2;

		for(int i = 0; i < numNodes; i++){
			val1 = pair<float,float>((rand() % 100) / pow(10,(rand() % 2)),(rand() % 100) / pow(10,(rand() % 2)));
			addNode(val1);
		}

		while(edges.size() < numEdges){
			duplicate = false;

			node1 = rand() % numNodes;
			node2 = rand() % numNodes;

			val1 = getNodes()[node1]->value;
			val2 = getNodes()[node2]->value;

			weight = (rand() % 100) / pow(10,(rand() % 2 + 1));

			for(auto edge: edges){
				if(edge->start == val1 && edge->end == val2 || val1 == val2){
					duplicate = true;
				}
			}

			if(!duplicate){
				edges.emplace_back(new Edge<float>(val1, val2, weight));
			}
			
		}

	cout<<"\n\nRandom graph result:\n";
	cout<<"Number of nodes: "<<numNodes<<"\n";
	for(auto node : nodes){
		cout<<node->value.first<<" "<<node->value.second<<"\n";
	}
	cout<<"\nNumber of edges: "<<numEdges<<"\n";
	for(auto edge : edges){
		cout<<edge->start.first<<","<<edge->start.second<<" -> "<<edge->end.first<<","<<edge->end.second<<" : "<<edge->weight<<"\n";
	}

	}
	
	default:
		break;
	}

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
void Grafo<pair<float,float>,V>::save(){

	ofstream file;
	file.open("graph.txt");

	file<<nodes.size()<<"\n";
	for(auto node : nodes){
		file<<node->value.first<<" "<<node->value.second<<"\n";
	}
	for(auto edge : edges){
		file<<edge->start.first<<" "<<edge->start.second<<" "<<edge->end.first<<" "<<edge->end.second<<" "<<edge->weight<<"\n";
	}

	file.close();
	
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
	for(auto node : nodes){
		if(node->value == val){
			cout<<"Duplicate node.\n";
			return;
		}
	}
	nodes.emplace_back(new Node<pair<float,float>>(val));
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(pair<float,float> start, pair<float,float> end, float weight){
	if(start == end){
		cout << "Loops not allowed\n";
		return;
	}

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge: ("<<edge->start.first<<","<<edge->start.second<<") -> ("<<edge->end.first<<","<<edge->end.second<<")\n";
			return;
		}
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

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge.\n";
			return;
		}
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

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge.\n";
			return;
		}
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

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge.\n";
			return;
		}
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

template<bool V>
vector<pair<float,float>> Grafo<pair<float,float>,V>::getNeighbors(pair<float,float> index){

	vector<pair<float,float>> neighbors;

	for(auto edge: edges){
		if(edge->start == index){
			neighbors.push_back(edge->end);
		}
	}

	return neighbors;
}

template<bool V>
bool Grafo<pair<float,float>,V>::inNeighborhood(pair<float,float> start, pair<float,float> neighbor){

	float meanWeight = 0;
	int edgeCount = 0;
	Edge<float>* connection = nullptr;

	for (auto edge: edges){
		if(edge->start == start){
			//cout<<"Edge found with end: "<<edge->end.first<<","<<edge->end.second<<" and weight: "<<edge->weight<<"\n";
			meanWeight+=edge->weight;
			edgeCount++;
			if(edge->end == neighbor){
				connection = edge;
			}
		}
	}

	if(!connection){
		cout<<"Nodes are not connected.\n";
		return false;
	}

	meanWeight /= edgeCount;
	//cout<<"Mean weight: "<<meanWeight<<"\n";

	if(connection->weight <= meanWeight){
		return true;
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
