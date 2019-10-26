#include <iostream>
#include "grafo.h"

using namespace std;

int main(){

    Grafo<pair<float,float>,false>* nodGrafo = new Grafo<pair<float,float>,false>();
    Grafo<pair<float,float>,true>* dGrafo = new Grafo<pair<float,float>,true>();

    nodGrafo->addNode(pair<float,float>(0,0));
    nodGrafo->addNode(pair<float,float>(0,-10));
    nodGrafo->addNode(pair<float,float>(0,10));
    nodGrafo->addNode(pair<float,float>(5,-5));
    nodGrafo->addNode(pair<float,float>(5,0));
    nodGrafo->addNode(pair<float,float>(5,5));
    nodGrafo->addNode(pair<float,float>(-5,-5));
    nodGrafo->addNode(pair<float,float>(-5,0));
    nodGrafo->addNode(pair<float,float>(-5,5));

    nodGrafo->addEdge({0,0}  ,{5,0}  ,2);    
    nodGrafo->addEdge({0,0}  ,{-5,0} ,6);    
    nodGrafo->addEdge({0,0}  ,{-5,-5},7);    
    nodGrafo->addEdge({0,10} ,{5,5}  ,9);    
    nodGrafo->addEdge({0,10} ,{-5,5} ,10);    
    nodGrafo->addEdge({0,-10},{5,-5} ,4);    
    nodGrafo->addEdge({0,-10},{-5,-5},8);    
    nodGrafo->addEdge({5,-5} ,{5,0}  ,8);    
    nodGrafo->addEdge({5,-5} ,{-5,-5},11);    
    nodGrafo->addEdge({5,0}  ,{5,5}  ,7);    
    nodGrafo->addEdge({5,0}  ,{-5,5} ,4);    
    nodGrafo->addEdge({5,5}  ,{-5,5} ,14);    
    nodGrafo->addEdge({-5,-5},{-5,0} ,2);    
    nodGrafo->addEdge({-5,0} ,{-5,5} ,1);    

/*
    cout<<"Trying to add loop: \n";
    nodGrafo->addEdge(pair<int,int>(4,4),pair<int,int>(4,4),4);
*/
		 /*cout << "SHOW ALL EDGES" << endl;
		 auto sorted_edges = nodGrafo->non_decreasing_edges();
		 for (auto i : sorted_edges)
		 	cout << "(" << i->start.first << "," << i->start.second << ") -> " << i->end.first  << " || ";
		 cout << endl;
*/
		auto nodGrafoKruskal = nodGrafo->mst_kruskal();
		for (auto i : nodGrafoKruskal){
			cout << "(" << i->start.first << "," << i->start.second << ") -> " << "(" << i->end.first << "," << i->end.second << ") || ";
		}
		cout << endl;
		
		cout << nodGrafo->density() << " <---- denso ";
		 
    //Grafo<pair<int,int>,false>* _nodGrafo = new Grafo<pair<int,int>,false>(nodGrafo);

		/* 
    cout<<"First value of node 0: "<<nodGrafo->getNodes()[0]->value.first<<endl;
    cout<<"First value of node 1: "<<nodGrafo->getNodes()[1]->value.first<<endl;

    cout<<"Node 0 grade: "<<nodGrafo->nodeGrade(pair<int,int>(0,0))<<endl;

    cout<<"BFS and DFS tests:\n";

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;
    cout<<"BFS for 0 to 4: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(4,4))<<endl;

    cout<<"DFS for 0 to 3: "<<nodGrafo->dfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;
    cout<<"DFS for 0 to 4: "<<nodGrafo->dfs(pair<int,int>(0,0),pair<int,int>(4,4))<<endl;

		cout << "LISTADO DE PUNTOS "<<endl;
		cout << "SALE =====>" << nodGrafo->dfs_connected(pair<float,float>(0,0)) << endl;

    cout<<"DeleteNode test: \n";
    nodGrafo->deleteNode(pair<int,int>(1,1));

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;//false
    cout<<"DFS for 0 to 3: "<<nodGrafo->dfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;//false

    nodGrafo->addEdge(pair<int,int>(4,4),pair<int,int>(2,2),0.3);
    nodGrafo->addEdge(pair<int,int>(0,0),pair<int,int>(4,4),0.3);

    cout<<"DeleteEdge test: \n";
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;
    nodGrafo->deleteEdge(pair<int,int>(0,0),pair<int,int>(4,4));
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;
		*/


    return 0;
}   

