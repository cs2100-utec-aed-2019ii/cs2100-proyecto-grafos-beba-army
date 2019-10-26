#include "grafo.h"
#include <iostream>
#include <fstream>
using namespace std;	

void create_graph(string file_path){
	ifstream myfile;
	myfile.open(file_path);
	string word;
	Grafo<pair<float,float>,false>* graph = new Grafo<pair<float,float>,false>();

	while(myfile >> word){
		if (word == "POINTS"){
			myfile >> word;
			int node_q  = stoi(word);

			myfile >> word;
			myfile >> word;

			for (int i=0; i < node_q; ++i){
				int x = stoi(word);
				myfile >> word;
				int y = stoi(word);

				graph->addNode({x,y});

				myfile >> word;
				myfile >> word;
			}
		}
		if (word == "EDGE"){
			myfile >> word;
			int node_q  = stoi(word);

			myfile >> word;
			myfile >> word;

			for (int i=0; i < node_q; ++i){
				int x = stoi(word);
				myfile >> word;
				int y = stoi(word);
				myfile >> word;
				int p = stoi(word);
				myfile >> word;
				int q = stoi(word);
				myfile >> word;
				int w = stoi(word);

				graph->addEdge({x,y}, {p,q},w);

				myfile >> word;
				myfile >> word;
			}
		}
	}
};
