#include <iostream>
#include <vector>
//#include <queue>
//#include <list>
//#include <cstdlib>
//#include <ctime>
//#include <bits/stdc++.h>
using namespace std;


class less_cost{
public:	
	bool operator() (const Edge_tuple& a, const Edge_tuple& b) const {
		return a.cost > b.cost;
	}

	// typedef Vertex_cost_pair first_argument_type;
	// typedef Verte_cost_pair second_argument_type;
	// typedef bool result_type;
};