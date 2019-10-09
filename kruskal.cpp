#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "kruskal.h"
#include "disjoint_sets.h"
using namespace std;

int main(int argc, char const *argv[]){
	
	int size =6;
	Graph g = create_graph(size, 0.7, 10, 1234);

	Graph mst = create_graph(size, 0.0, 1, 1234);

	Disjoint_sets partition(size);

	//auto edge_list = *(g.list_edges());
	vector<Edge_tuple> edge_list = *(g.list_edges());

	priority_queue<Edge_tuple, vector<Edge_tuple>, less_cost> edge_qu;

	for (auto edge: edge_list){
		edge_qu.push(edge);
	}

	int mst_cost=0;

	while (not edge_qu.empty()){
		
		auto new_edge = edge_qu.top();
		int v1 = new_edge.v1;
		int v2 = new_edge.v2;
		int c = new_edge.cost;

		if ( partition.find(v1) != partition.find(v2) ){
			mst.add_edge(v1, v2, c);
			partition.join(v1, v2);
			mst_cost += c;
		}

		edge_qu.pop();
	}

	g.print();
	mst.print();
	cout << mst_cost << endl;

	//cout << g.num_edges << endl;
	//cout << edge_list.capacity() << endl;
	//cout << edge_list.size() << endl;

	//cout << edge_list[30].cost << endl;

	//priority_queue<Edge_tuple, vector<Edge_tuple>, less_cost> edge_pq;

	// partition.join(2, 5);
	// partition.join(5, 7);
	// partition.join(2, 3);
	// partition.join(1, 6);
	// partition.join(6, 2);
	// for (int i = 0; i < 10; ++i){
	// 	cout << partition.parent[i];
	// }



	return 0;
}