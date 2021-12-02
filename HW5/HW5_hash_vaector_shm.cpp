#include <fstream>
#include <unordered_map>
#include <vector>
#include "data.hpp"
using namespace std;
unordered_map<int, vector<int>> edge;
void solve(tTestData* test_data){
	ofstream out("output.txt");
	for(int t = 0; t < test_data->t; t++){
		edge.clear();
		int n, I, cur, prev=-10000001, i, j;
		n = test_data->testcase[t].n;
		I = test_data->testcase[t].i;
		for(i = 0; i < n-1; i++){
			int a, b;
			a=test_data->testcase[t].edges[i][0];
			b=test_data->testcase[t].edges[i][1];
			edge[a].push_back(b);
			edge[b].push_back(a);
		}
		for(auto x : edge){
			if(x.second.size()==1) prev = max(prev, x.first);
		}
		if(I==0){
			out << prev << '\n';
			edge.clear();
			continue; 
		}
		cur = edge[prev][0];
		for(i = 1; i < I; i++){
			if(edge[cur][0]==prev){
				prev = cur;
				cur = edge[prev][0];
			}else{
				prev = cur;
				cur = edge[prev][1];
			}
		}
		out << cur << '\n';
	}
}
