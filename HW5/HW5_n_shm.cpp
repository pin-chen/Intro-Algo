#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include "data.hpp"
#define MAX 10000001
using namespace std;
struct Edge{
	int next1;
	int next2;
};
Edge edge[20000002];
int node[100000];
int_fast32_t n, I, i, j, t, a, b;
void solve(tTestData* test_data){
	int prev, cur;
	ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n;
		I = test_data->testcase[t].i;
		for(i = 0, j = 0; i < n-1; i++){
			a=test_data->testcase[t].edges[i][0]+MAX;
			b=test_data->testcase[t].edges[i][1]+MAX;
			if(edge[a].next1==0)	edge[a].next1=b;
			else					edge[a].next2=b;
			if(edge[b].next1==0)	edge[b].next1=a;
			else					edge[b].next2=a;
			node[j++] = a;
			node[j++] = b;
		}
		if(I < n / 2){
			prev = 0;
			for(i = 0; i < j; i++){
				if(edge[node[i]].next2==0) prev = max(prev, node[i]);
			}
			if(I==0){
				out << prev - MAX<< '\n';
				for(i = 0; i < j; i++){
					edge[node[i]].next1=0;
					edge[node[i]].next2=0;
				}
				continue; 
			}
			cur = edge[prev].next1;
			for(i = 1; i < I; i++){
				if(edge[cur].next1==prev){
					prev = cur;
					cur = edge[prev].next2;
				}else{
					prev = cur;
					cur = edge[prev].next1;
				}
			}
		}else{
			prev = 20000002;
			for(i = 0; i < j; i++){
				if(edge[node[i]].next2==0) prev = min(prev, node[i]);
			}
			if(I==n-1){
				out << prev - MAX<< '\n';
				for(i = 0; i < j; i++){
					edge[node[i]].next1=0;
					edge[node[i]].next2=0;
				}
				continue;
			}
			cur = edge[prev].next1;
			for(i = 2; i < n-I; i++){
				if(edge[cur].next1==prev){
					prev = cur;
					cur = edge[prev].next2;
				}else{
					prev = cur;
					cur = edge[prev].next1;
				}
			}
		}
		for(i = 0; i < j; i++){
			edge[node[i]].next1=0;
			edge[node[i]].next2=0;
		}
		out << cur - MAX << '\n';
	}
}
