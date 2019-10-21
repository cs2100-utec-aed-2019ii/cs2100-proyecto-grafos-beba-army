#include <iostream>
#include "grafo.h"

using namespace std;

int main(){

    Grafo<pair<float,float>,false>* nodGrafo = new Grafo<pair<float,float>,false>();
    Grafo<pair<float,float>,true>* dGrafo = new Grafo<pair<float,float>,true>();

    nodGrafo->addNode(pair<float,float>(0,0));
    nodGrafo->addNode(pair<float,float>(1,1));
    nodGrafo->addNode(pair<float,float>(2,2));
    nodGrafo->addNode(pair<float,float>(3,3));
    nodGrafo->addNode(pair<float,float>(4,4));


    nodGrafo->addEdge(0,1,1);    
    nodGrafo->addEdge(1,2,2);
    nodGrafo->addEdge(2,3,3);

    cout<<"Trying to add loop: \n";
    nodGrafo->addEdge(4,4,0.3);

		cout << "SHOW ALL EDGES" << endl;
		auto sorted_edges = nodGrafo->non_decreasing_edges();
		for (auto i : sorted_edges)
			cout << i->weight << " ";

    //Grafo<pair<int,int>,false>* _nodGrafo = new Grafo<pair<int,int>,false>(nodGrafo);

    cout<<"First value of node 0: "<<nodGrafo->getNodes()[0]->value.first<<endl;
    cout<<"First value of node 1: "<<nodGrafo->getNodes()[1]->value.first<<endl;

    cout<<"Node 1 grade: "<<nodGrafo->nodeGrade(0)<<endl;
    
    cout<<"BFS and DFS tests:\n";

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(0,3)<<endl;
    cout<<"BFS for 0 to 4: "<<nodGrafo->bfs(0,4)<<endl;

    cout<<"DFS for 0 to 3: "<<nodGrafo->dfs(0,3)<<endl;
    cout<<"DFS for 0 to 4: "<<nodGrafo->dfs(0,4)<<endl;

		cout << "LISTADO DE PUNTOS "<<endl;
		cout << "SALE =====>" << nodGrafo->dfs_connected(0) << endl;

    cout<<"DeleteNode test: \n";
    nodGrafo->deleteNode(1);

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(0,3)<<endl;
    cout<<"DFS for 0 to 3: "<<nodGrafo->dfs(0,3)<<endl;

    nodGrafo->addEdge(0,4,0.3);
    nodGrafo->addEdge(4,2,0.3);

    cout<<"DeleteEdge test: \n";
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(0,3)<<endl;
    nodGrafo->deleteEdge(0,4);
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(0,3)<<endl;



    return 0;
}   
