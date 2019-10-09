#include <iostream>
#include <vector>
using namespace std;


class Disjoint_sets{
public:
	Disjoint_sets(int size);
	//~Disjoint_set();
	
	int find(int i);
	void join(int i, int j);
	int size;
	vector<int> parent;
	vector<int> rank;

};

Disjoint_sets::Disjoint_sets(int size): size(size),
										rank(size, 0),
										parent(size){
	
	for (int i = 0; i < size; ++i)
		parent[i] = i;

};

int Disjoint_sets::find(int i){
	int elem = i;
	while (elem != parent[elem]){
		elem = parent[elem];
	}
	return elem;
}

void Disjoint_sets::join(int elem1, int elem2){
	int elem1_rt = find(elem1);
	int elem2_rt = find(elem2); 

	if (elem1_rt != elem2_rt){
		if (rank[elem1_rt] < rank[elem2_rt]){
			
			parent[elem1_rt] = elem2_rt;

		}
		else{
		
			parent[elem2_rt] = elem1_rt;

			if (rank[elem1_rt] == rank[elem2_rt]){
				rank[elem1_rt] += 1;
			}

		}

	}
	//cout << parent[elem1_rt] << " " << parent[elem2_rt] << endl;

}