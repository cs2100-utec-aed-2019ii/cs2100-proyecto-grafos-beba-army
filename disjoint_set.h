#include "Node.h"
#include <iostream>

template<typename T>
class subset{
	public:
		T place;
		T parent;
		int weight;
		subset(T place){
			this->place = place;
			parent = place;
			weight = 1;
		}
};

template<typename T>
class disjointed_sets{
	typedef vector<Node<T>*> node_list;
	private:
		subset<T>* find(subset<T>* curr){
			if (curr->parent == curr->place){
				return curr;
			}else{
				for (auto i : sets){
					if (i->place == curr->parent)
						return find(i);
				}
			}
			std::cout << "===============\n  NO SE ENCONTRO\n ===============" << std::endl;
			return nullptr;
		};
	public:
		std::vector<subset<T>*> sets;
		disjointed_sets(node_list input){
			for (auto i : input){
				auto value = i->value;
				subset<T>* set = new subset<T>(value);
				sets.push_back(set);
			}
		}
		
		subset<T>* find(T node){
			for (auto i : sets){
				if (i->place == node){
					//std::cout << "found: " << node.first << " in " << i << " " << i->place.first << "\n";
					return find(i);
				}
			}
		}

		void Union(T set1, T set2){
			auto parent1 = find(set1);
			auto parent2 = find(set2);
			
			if (parent1->weight > parent2->weight){
				parent2->parent = parent1->parent;
			}else if (parent1->weight < parent2->weight){
				parent1->parent = parent2->parent;
			}else{
				parent2->parent = parent1->parent;
				parent1->weight++;
			}
		}
};
