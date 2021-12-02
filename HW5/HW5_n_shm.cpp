#include <fstream>
#include "data.hpp"
#define MAX 10000001
using namespace std;
int edge[2][20000002]={};
int node[100000]={};
void solve(tTestData* test_data){
	ofstream out("output.txt");
	for(int t = 0; t < test_data->t; t++){
		int n, I, cur, prev=0, i, j;
		n = test_data->testcase[t].n;
		I = test_data->testcase[t].i;
		for(i = 0, j = 0; i < n-1; i++){
			int a, b;
			a=test_data->testcase[t].edges[i][0]+MAX;
			b=test_data->testcase[t].edges[i][1]+MAX;
			if(edge[0][a]==0)	edge[0][a]=b;
			else				edge[1][a]=b;
			if(edge[0][b]==0)	edge[0][b]=a;
			else				edge[1][b]=a;
			node[j++] = a;
			node[j++] = b;
		}
		for(i = 0; i < j; i++){
			if(edge[1][node[i]]==0) prev = max(prev, node[i]);
		}
		if(I==0){
			out << prev - MAX<< '\n';
			for(i = 0; i < j; i++){
				edge[0][node[i]]=0;
				edge[1][node[i]]=0;
			}
			continue; 
		}
		cur = edge[0][prev];
		for(i = 1; i < I; i++){
			if(edge[0][cur]==prev){
				prev = cur;
				cur = edge[1][prev];
			}else{
				prev = cur;
				cur = edge[0][prev];
			}
		}
		for(i = 0; i < j; i++){
			edge[0][node[i]]=0;
			edge[1][node[i]]=0;
		}
		out << cur - MAX << '\n';
	}
}
