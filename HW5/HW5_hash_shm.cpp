#include <fstream>
#include <unordered_map>
#include "data.hpp"
#define MAX 10000001
using namespace std;
unordered_map<int, pair<int, int>> edge;
int node[100000]={};
void solve(tTestData* test_data){
	ofstream out("output.txt");
	for(int t = 0; t < test_data->t; t++){
		edge.clear();
		int n, I, cur, prev=0, i, j;
		n = test_data->testcase[t].n;
		I = test_data->testcase[t].i;
		for(i = 0, j = 0; i < n-1; i++){
			int a, b;
			a=test_data->testcase[t].edges[i][0]+MAX;
			b=test_data->testcase[t].edges[i][1]+MAX;
			edge[a];
			edge[b];
			if(edge[a].first==0)	edge[a].first=b;
			else					edge[a].second=b;
			if(edge[b].first==0)	edge[b].first=a;
			else					edge[b].second=a;
			node[j++] = a;
			node[j++] = b;
		}
		for(i = 0; i < j; i++){
			if(edge[node[i]].second==0) prev = max(prev, node[i]);
		}
		if(I==0){
			out << prev - MAX<< '\n';
			continue; 
		}
		cur = edge[prev].first;
		for(i = 1; i < I; i++){
			if(edge[cur].first==prev){
				prev = cur;
				cur = edge[prev].first;
			}else{
				prev = cur;
				cur = edge[prev].second;
			}
		}
		out << cur - MAX << '\n';
	}
}
