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

#include "disjoint_set.h"

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
		bool density(); 
		
		bool bfs(pair<float,float> starf, pair<float,float> find); 
		bool dfs(pair<float,float> starf, pair<float,float> find); 
		
		vector<Edge<float>*> non_decreasing_edges();
		vector<Edge<float>*> mst_kruskal();
		vector<Edge<float>*> mst_prim();

		void save();
		vector<pair<float,float>> getNeighbors(pair<float,float> index);
		bool inNeighborhood(pair<float,float> start, pair<float,float> neighbor);

		bool bipartite();
		bool connected();

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


			for(auto edge: edges){
				if(edge->start == val1 && edge->end == val2 || val1 == val2){
					duplicate = true;
				}
			}

			weight = pow(pow(val1.first-val2.first,2)+pow(val1.second-val2.second,2),0.5);


			if(!duplicate){
				edges.emplace_back(new Edge<float>(val1, val2,weight));
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

	bool missing_S = true;
	bool missing_E = true;


	for(auto node: nodes){
		if(node->value == start){
			missing_S = false;
		}
		if(node->value == end){
			missing_E = false;
		}
		if(!missing_E && !missing_S){
			break;
		}
	}

	if(missing_S || missing_E){
		cout<<"Nodos invalidos.\n";
		return;
	}

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge: ("<<edge->start.first<<","<<edge->start.second<<") -> ("<<edge->end.first<<","<<edge->end.second<<")\n";
			return;
		}
	}

	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;
	Edge<float>* edge1 = new Edge<float>(start, end, weight);
	edges.emplace_back(edge1);
	for (auto i : nodes)
		if (i->value == start)
			i->edges.push_back(edge1);

	Edge<float>* edge2 = new Edge<float>(end, start, weight);
	cout << "New edge: (" << end.first<<","<<end.second << ") -> (" << start.first<<","<<start.second << ") - weight: " << weight << endl;	
	edges.emplace_back(edge2);
	for (auto i : nodes)
		if (i->value == end)
			i->edges.push_back(edge2);
}

template<>
void Grafo<pair<float,float>,true>::addEdge(pair<float,float> start, pair<float,float> end, float weight){
	if (start == end){
		cout << "Loops not allowed\n";
		return;
	}
	Edge<float>* edge1 = new Edge<float>(start, end, weight);
	edges.emplace_back(edge1);
	for (auto i : nodes)
		if (i->value == start)
			i->edges.push_back(edge1);

	bool missing_S = true;
	bool missing_E = true;


	for(auto node: nodes){
		if(node->value == start){
			missing_S = false;
		}
		if(node->value == end){
			missing_E = false;
		}
		if(!missing_E && !missing_S){
			break;
		}
	}

	if(missing_S || missing_E){
		cout<<"Nodos invalidos.\n";
		return;
	}

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge.\n";
			return;
		}
	}

	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;
}

template<bool V>
void Grafo<pair<float,float>,V>::addEdge(pair<float,float> start, pair<float,float> end){
	if (start == end){
		cout << "Loops not allowed\n";
		return;
	}

	bool missing_S = true;
	bool missing_E = true;


	for(auto node: nodes){
		if(node->value == start){
			missing_S = false;
		}
		if(node->value == end){
			missing_E = false;
		}
		if(!missing_E && !missing_S){
			break;
		}
	}

	if(missing_S || missing_E){
		cout<<"Nodos invalidos.\n";
		return;
	}

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge.\n";
			return;
		}
	}
	

	float weight = pow(pow(start.first-end.first,2)+pow(start.second-end.second,2),0.5);

	Edge<float>* edge1 = new Edge<float>(start, end, weight);
	Edge<float>* edge2 = new Edge<float>(end, start, weight);


	edges.emplace_back(edge1);
	for (auto i : nodes)
		if (i->value == start)
			i->edges.push_back(edge1);

	edges.emplace_back(edge2);
	for (auto i : nodes)
		if (i->value == end)
			i->edges.push_back(edge2);

	cout << "New edge: (" << start.first<<","<<start.second << ") -> (" << end.first<<","<<end.second << ") - weight: " << weight << endl;

}

template<>
void Grafo<pair<float,float>,true>::addEdge(pair<float,float> start, pair<float,float> end){
	if(start == end){
		cout<<"Loops not allowed\n";
		return;
	}

	bool missing_S = true;
	bool missing_E = true;


	for(auto node: nodes){
		if(node->value == start){
			missing_S = false;
		}
		if(node->value == end){
			missing_E = false;
		}
		if(!missing_E && !missing_S){
			break;
		}
	}

	if(missing_S || missing_E){
		cout<<"Nodos invalidos.\n";
		return;
	}

	for(auto edge : edges){
		if(edge->start== start && edge->end == end){
			cout<<"Duplicate edge.\n";
			return;
		}
	}

	float weight = pow(pow(start.first-end.first,2)+pow(start.second-end.second,2),0.5);
	edges.emplace_back(new Edge<float>(start, end, weight));

	Edge<float>* edge1 = new Edge<float>(start, end, weight);
	edges.emplace_back(edge1);
	for (auto i : nodes)
		if (i->value == start)
			i->edges.push_back(edge1);


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
bool Grafo<pair<float,float>,V>::connected(){
	auto start = nodes[0]->value;
	
	stack<pair<float,float>> nodes_stack;
	vector<pair<float,float>> visited;

	pair<float,float> curr;

	nodes_stack.push(start);
	visited.push_back(start);

	cout<<"\n";

	while (!nodes_stack.empty()){
		curr = nodes_stack.top();
		cout << "Current node: (" << curr.first << "," << curr.second << ")\n";	
		nodes_stack.pop();

		for (auto edge : edges){
			if (edge->start == curr && !findEdgePair(visited, edge->end)){
				cout << "Inserting from edge: (" << curr.first << "," << curr.second << ") -> (" << edge->end.first << "," << edge->end.second << ")\n";
				nodes_stack.push(edge->end);
				visited.push_back(edge->end);
			}
		}
	}

	if (visited.size() == nodes.size()){
		return true;
	}else{
		return false;
	}
};

bool compare_edge_weight(Edge<float>* x, Edge<float>* y) {return (x->weight < y->weight);}; // works as an operator overload
template<bool V>
vector<Edge<float>*> Grafo<pair<float,float>,V>::non_decreasing_edges(){
	edge_list sorted_edges = edges;
	std::sort (sorted_edges.begin(), sorted_edges.end(), compare_edge_weight);
	return sorted_edges;
};

template<>
vector<Edge<float>*> Grafo<pair<float,float>, false>::mst_kruskal(){
	vector<Edge<float>*> result;
	auto sorted_edges = non_decreasing_edges();
	disjointed_sets<pair<float,float>> sets {nodes};
	int i=0;
	while (result.size() < nodes.size()-1){
		auto parent1 = sets.find(sorted_edges[i]->start)->place;
		auto parent2 = sets.find(sorted_edges[i]->end)->place;
		
		if (parent1 != parent2){
			result.push_back(sorted_edges[i]);
			sets.Union(parent1, parent2);
		}
		
		if (i <= edges.size()-1)
			i += 2;
	}
	return result;
};

template<>
bool Grafo<pair<float,float>, true>::density(){
	float density = edges.size()/(nodes.size()-(nodes.size()-1));
	if (density < 0.6)
		return false;
	else
		return true;
};

template<>
bool Grafo<pair<float,float>, false>::density(){
	float density = (edges.size()*2)/(nodes.size()-(nodes.size()-1));
	if (density < 0.6)
		return false;
	else
		return true;
};

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
		cout<<"Weight: "<<connection->weight<<" smaller than "<<meanWeight<<"\n";
		return true;
	}
	return false;
}


template<bool V>
bool Grafo<pair<float,float>,V>::bipartite(){
	//cout<<"Bipartite start\n";
	map<pair<float,float>,int> color;
	pair<float,float> current;
	queue<pair<float,float>> nodos;
	vector<pair<float,float>> visited;

	for(auto nodo: nodes){


		if(color[nodo->value] == 0){

			current = nodo->value;

			color[current] = 1;

			nodos.push(current);

			while(!nodos.empty()){

				current = nodos.front();

				nodos.pop();

				for(auto edge: edges){
					if(edge->start == current){
						if(color[current] == color[edge->end]){
							return false;
						}
						else{
							color[edge->end] = color[current]*-1;
						}
						if(!findEdgePair(visited, edge->end)){
							nodos.push(edge->end);
							visited.push_back(edge->end);
						}
					}
					
				}

			}
		}
	}

	return true;

}

bool already_visited(pair<float,float> value, std::vector<pair<float,float>> list){
	for (auto i : list)
		if (value == i) 
			return true;
	return false;
};

Node<pair<float,float>>* pointer_home(pair<float,float> value, vector<Node<pair<float,float>>*> nodes){
	for (auto i : nodes)
		if (i->value == value)
			return i;
	return nullptr;
	std::cout << "NO SE ENCONTRO EL NODO <-- funcion: pointer_home\n";
};
/*
class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};

template<>
std::vector<Edge<float>*> Grafo<pair<float,float>, false>::mst_prim(){ 
	std::vector<Edge<float>*> result;
	priority_queue<Edge<float>*, std::vector<Edge<float>*>, mycomparison> p_queue;
	std::vector<pair<float,float>> visited;

	visited.emplace_back(nodes[1]->value);
	for (auto i : nodes[1]->edges)
		p_queue.push(i);

	while(!p_queue.empty()){
		Edge<float>* front_edge = p_queue.top();
		auto e_value = front_edge->end;
		auto pointer = pointer_home(e_value, nodes);
		if (!already_visited(e_value, visited)){
			result.emplace_back(front_edge);
			visited.emplace_back(e_value);		
			for (auto i : pointer->edges)
				p_queue.push(i);
		}
		p_queue.pop();
	}
		
	return result;
};
*/
#endif

