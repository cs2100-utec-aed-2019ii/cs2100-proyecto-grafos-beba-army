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

		if (word == "CELL"){
			myfile >> word;
			int node_q = stoi(word);

			myfile >> word;
			myfile >> word;

			for (int i=0; i < node_q; ++i){
				int q = stoi(word);
				int temp;
				myfile >> word;
				
				temp = stoi(word);
				std::vector<int> node_x;
				std::vector<int> node_y;

				for (int j=0; j < q-1; ++j){
					node_x.push_back(stoi(word));
					myfile >> word;
					node_y.push_back(stoi(word));
				}
				node_x.push_back(stoi(word));
				node_y.push_back(temp);

				for (int j=0; j < q; ++i){
					int x = node_x[i];
					int y = node_y[i];
					int p,q;
					if (q == q-1){
						p = node_x[i+1];
						q = node_y[i+1];
					} else {
						p = node_x[0];
						q = node_y[0];
					}
					graph->addEdge({x,y}, {p,q});
				}

			}

		}
	}
};
