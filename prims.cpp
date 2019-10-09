#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "prims.h"
using namespace std;


int main(int argc, char const *argv[])
{
	int size=6, src=1;

	Graph g = create_graph(size, 0.7, 10, 1234);

	Graph mst = create_graph(size, 0.0, 1, 1234);


	vector<Visited_dist_pair> vertex(g.num_verticies);
	vector<bool> visited(g.num_verticies);

	priority_queue<Edge_tuple, vector<Edge_tuple>, less_cost> fringe_qu;
	vector<bool> fringe_set(g.num_verticies);


	fringe_qu.push(Edge_tuple(src, src, 0));

	if (not g.is_connected()){
		cout << "graph is not connected" << endl;
		return 1;
	}

	int num_visited=0, v, mst_cost=0;
	Edge_tuple next_edge;
	vector<Vertex_pair>* v_successors;
	
	while (num_visited < size){
		
		next_edge = (fringe_qu.top());
		
		v = next_edge.v2;
		
		if (vertex[v].visited){
			fringe_qu.pop();
			continue;
		}

		//cout << v << "\t" << c << endl;

		vertex[v].visited = true;
		mst.add_edge(next_edge.v1, next_edge.v2, next_edge.cost);
		mst_cost += next_edge.cost;
		num_visited++;

		for (const auto &s: g.get_successors(v)){
			
			if ( not vertex[s.vertex].visited ){
				
				fringe_qu.push(Edge_tuple(v, s.vertex, s.cost));
				fringe_set[s.vertex] = true;

			}
			
		}

	}

	g.print();
	mst.print();
	cout << mst_cost << endl;

	return 0;
}