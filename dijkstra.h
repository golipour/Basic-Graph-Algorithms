#include <iostream>
#include <vector>
//#include <queue>
//#include <list>
//#include <cstdlib>
//#include <ctime>
//#include <bits/stdc++.h>
using namespace std;



class Vertex_cost_pair {
public:
	Vertex_cost_pair(){};
	Vertex_cost_pair(int vertex, int cost);

	int vertex;
	int cost;
};

Vertex_cost_pair::Vertex_cost_pair(int vertex, int cost): 	vertex(vertex), 
																cost(cost) {};

class Visited_dist_pair {
public:
	Visited_dist_pair(): visited(false) {};

	bool visited;
	int cost;
};

// class Path {
// public:
// 	Path(){};

// 	int src;
// 	int dst;
// 	int min_dist;
// 	bool visited;
// };


class less_cost{
public:	
	bool operator() (const Vertex_cost_pair& a, const Vertex_cost_pair& b) const {
		return a.cost > b.cost;
	}

	// typedef Vertex_cost_pair first_argument_type;
	// typedef Vertex_cost_pair second_argument_type;
	// typedef bool result_type;
};