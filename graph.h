// header file for graph class
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <cstdlib>
#include <ctime>
//#include <bits/stdc++.h>
using namespace std;

// using std::vector;
// using std::queue;
// using std::list;
// using std::priority_queue;

// template spesialization didn't work (maybe because it doesn't return void)
template <typename T> 
T uniform (T start, T stop){
	if(is_same<T, double>::value){
		T rand_num = static_cast<T>(rand()) / RAND_MAX;
		rand_num = rand_num * (stop - start) + start;
		return rand_num;
	}
	else if(is_same<T, int>::value){
		
		if (stop == start) return start;
		T rand_num = rand() % static_cast<int>(stop - start) + start;
		return rand_num;
	}	 
}

// adjacency matrix pair elements
class Edge_pair{
public:
	Edge_pair(): edge(false), cost(1) {};
	Edge_pair(bool edge, int cost): edge(edge), cost(cost){};

	bool edge;
	int cost;
};

// adjacency list pair elements
class Vertex_pair{
public:
	Vertex_pair(){};
	Vertex_pair(int vertex, int cost): vertex(vertex), cost(cost){};

	int vertex;
	int cost;
};

class Edge_tuple{
public:
	Edge_tuple(){};
	Edge_tuple(int v1, int v2, int cost=1): v1(v1), v2(v2), cost(cost) {};

	int v1;
	int v2;
	int cost;
};

// for future graph class with object vertices
class Vertex{
public:
	vector<int> neighbors;
	vector<Vertex_pair> successors;
};


class Graph{
public:
	Graph();
	Graph(int size);

	int num_edges, num_verticies;
	
	int cost( int v1, int v2);
	bool is_edge( int v1, int v2);
	bool is_connected();
	bool add_edge(int v1, int v2, int cost);
	vector<Edge_tuple>* list_edges();
	//list<Vertex_pair> neighbors(int v);
	vector<int> get_neighbors(int v);
	const vector<Vertex_pair>& get_successors(int v);
	// get_childes();
	void print() const;
	
private:
	vector<vector<Edge_pair>> mat;

	// do to its contigues use of memory, 
	// vector has better cash performace than list. 
	// but, vector reservs more capacity than it's size and
	// it's construction is more time consuming, because of
	// memory reallocation.
	vector<vector<Vertex_pair>> lst;
 	//vector<list<Vertex_pair>> adj_list;

 friend Graph create_graph(int size, double edge_prob, double max_cost, int seed);
};

Graph::Graph(): mat(), lst(), num_edges(0), num_verticies(0) {}

Graph::Graph(int size): mat(size), 
						lst(size), 
						num_verticies(size), 
						num_edges(0) {

	for (auto &v: mat){
		v.reserve(size);
		//v.resize(size);
	}
}

bool Graph::is_edge( int v1, int v2){
	return mat[v1][v2].edge;

	// algorithem for list representation.
	// for (auto &neighbor: mat[v1]){
	//  	if(neighbor.vertex == v2){
	//  		return true;
	//  	}
	//  }
	//  return false;
}

int Graph::cost( int v1, int v2){
	if (mat[v1][v2].edge){
		return mat[v1][v2].cost;
	}
	else{
		cout << " no edge between " << v1 << "and" << v2 << endl;
		return 999999;
	}
}

bool Graph::add_edge(int v1, int v2, int cost=1){
	if (v1 == v2) return false;

	if (not mat[v1][v2].edge){
		
		lst[v1].push_back(Vertex_pair(v2, cost));
		lst[v2].push_back(Vertex_pair(v1, cost));

		mat[v1][v2].edge = true;
		mat[v1][v2].cost = cost;
		mat[v2][v1].edge = true;
		mat[v2][v1].cost = cost;

		num_edges++;
	}
	else{

		for (auto &s: lst[v1]){
			s.cost = cost;
		}

		for (auto &s: lst[v2]){
			s.cost = cost;
		}

		mat[v1][v2].cost = cost;
		mat[v2][v1].cost = cost;
	}
	return true;
}

vector<int> Graph::get_neighbors(int v){
	
	vector<int> neighbors;
	for (auto &neighbor: lst[v]){
		neighbors.push_back(neighbor.vertex);
	}
	return neighbors;
}

const vector<Vertex_pair>& Graph::get_successors(int v){
	return lst[v];
}


vector<Edge_tuple>* Graph::list_edges(){

	//auto lst = new vector<Edge_tuple>(num_edges);
	auto lst = new vector<Edge_tuple>();
	lst->reserve(num_edges);

	for (int i = 0; i < num_verticies; ++i){
		for (int j = 0; j < i; ++j){
			if (mat[i][j].edge){
				
				lst->push_back(Edge_tuple(i, j, mat[i][j].cost));

			}
		}	
	}
	
	return lst;
}


bool Graph::is_connected(){
	int old_size=0, c_size=0, size=num_verticies;
	bool* close = new bool[size];
	bool* open = new bool[size];
	for (int i = 0; i < size; ++i){
		close[i] = open[i] = false;
	open[0] = true;
	}

	while(c_size < size){
		// add each node i in the open set to the close set
		// and add all nodes connected to i to the open set.
		for (int i = 0; i < size; ++i){
			old_size = c_size;
			if (open[i] && (close[i]==false)){
				close[i] = true;c_size++;
				// add all nodes connected to i to the open set.
				for (int j = 0; j < size; ++j){
					open[j] = open[j] || mat[i][j].edge; 
				}
			}
		}

		// if all the nodes are in the close set then the graph is connected.
		if(c_size == size) return true;
		// if close set is not full but the open set empty then the graph is dis-connected.
		if(old_size == c_size) return false;
	}
}


void Graph::print() const{

	cout << "verticies";
	cout.width(4);
	cout << "\t" << right << "cost" << endl;

	for (int i = 0; i < num_verticies; ++i){
		for (int j = 0; j < i; ++j){
			if (mat[i][j].edge){
				
				cout << "(" << i << ", " << j << ")";
				cout.width(4);
				cout << "\t" << right << mat[i][j].cost << endl;

			}
		
		}	
	}
	cout << "--------------------" << endl;
	cout << "number of verticies: " << num_verticies << endl;
	cout << "number of edges: " << num_edges << endl;
}

Graph create_graph(int size, double edge_prob=0.2, double max_cost=10, int seed=time(0)){
	
	// if (seed == -1){
	// 	srand(time());
	// }
	srand(seed);

	Graph g = Graph(size);
	//g.num_edges = 0;
	//g.num_verticies = size;

	// vector< vector<Edge_pair> > mat(size);
	// vector< vector<Vertex_pair>> lst(size);
	// int num_edges = 0;

	for (int i = 0; i < size; ++i){
		//cout << "capacity before:" << mat[i].capacity() << endl;
		
		// reserving capacity, to prevent memory reallocation.
		//mat[i].reserve(size);
		
		//cout << "capacity after:" << mat[i].capacity() << endl;
		//cout << "size before:" << mat[i].size() << endl;

		// for element assignments to work uncumment this!
		// if you prefer adding ellements to the mat by push,comment this! 
		//mat[i].resize(size);

		for (int j = 0; j <= i; ++j){
			if(i==j){
				//mat[i][j] = Vertex_pair(false, 0);
				//mat[i][j].edge = false;
				//mat[i][j].cost = 0;
				
				g.mat[i][j] = Edge_pair(false, 0);

				//g.mat[i].push_back(Edge_pair(false, 0));
			}
			else {
				bool e = (uniform<double>(0.0, 1.0) < edge_prob);
				double c = uniform<int>(1, max_cost);
				
				//mat[i][j] = Vertex_pair(e, c);
				//mat[i][j].edge = mat[j][i].edge = e;
				//mat[i][j].cost = mat[j][i].cost = c;
				
				g.mat[i][j] = Edge_pair(e, c);
				g.mat[j][i] = Edge_pair(e, c);
				//g.mat[i].push_back(Edge_pair(e, c));
				
				// if there is an edge between i and j, add it to the adjacency list.
				if (e){
					//lst[i].push_back(Vertex_pair(j, c));
					g.lst[i].push_back(Vertex_pair(j, c));
					g.lst[j].push_back(Vertex_pair(i, c));

					g.num_edges++;

					// cout << "(" << i << ", " << j << ")";
					// cout.width(4);
					// cout << "\t" << right << c << endl;
				}
			}
		}
		//cout << "size after:" << mat[i].size() << endl;
	}

	return g;
}
