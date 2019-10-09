#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "dijkstra.h"
using namespace std;

typedef priority_queue<Vertex_cost_pair, vector<Vertex_cost_pair>, less_cost> min_dist_qu_type;

int main(int argc, char const *argv[])
{
	int size=6, src=0, dst=5;

	Graph g = create_graph(size, 0.7, 10, 1234);

	g.print();

	vector<Visited_dist_pair> vertex(g.num_verticies);
	//vector<bool> visited(g.num_verticies);
	//vector<int> min_cost(g.num_verticies);

	// cout << vertex.size() << endl;
	// cout << vertex.capacity() << endl;
	// cout << vertex.empty() << endl;
	// vertex[1].dist = 37;
	// cout << vertex[1].visited << endl;

	min_dist_qu_type fringe_qu;
	vector<bool> fringe_set(g.num_verticies);

	//cout << fringe_qu.size() << endl;
	//cout << fringe_qu.empty() << endl;

	fringe_qu.push(Vertex_cost_pair(src, 0));

	if (not g.is_connected()){
		cout << "graph is not connected" << endl;
		return 1;
	}

	cout << endl;
	cout << "vertex" << "\t" << "cost" << endl;
	
	int num_visited=0, v, c;
	Vertex_cost_pair shortest_path;
	vector<Vertex_pair>* v_successors;
	//while (vertex[dst].visited == false)
	while (num_visited < size){
		
		shortest_path = (fringe_qu.top());
		//&(fringe_qu.top());
		v = shortest_path.vertex;
		
		if (vertex[v].visited){
			fringe_qu.pop();
			continue;
		}

		c = shortest_path.cost;
		cout << v << "\t" << c << endl;

		vertex[v].visited = true;
		vertex[v].cost = c;

		num_visited++;

		// v_successors = g.get_successors(v);
		// for (const auto &s: v_successors)
		for (const auto &s: g.get_successors(v)){
			//if ( not vertex[s.vertex].visited and not fringe_set[s.vertex] ){
			if ( not vertex[s.vertex].visited ){
				fringe_qu.push(Vertex_cost_pair(s.vertex, s.cost + c));
				fringe_set[s.vertex] = true;
			}
			
		}

	}

	return 0;
}