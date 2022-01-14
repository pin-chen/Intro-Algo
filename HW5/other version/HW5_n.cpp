#include <iostream>
#include <fstream>
#define MAX 10000001
using namespace std;
int edge[20000002][2]={};
int node[100000]={};
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int T;
	in >> T;
	while(T--){
		int n, I, cur, prev=0, i, j;
		in >> n >> I;
		for(i = 0, j = 0; i < n-1; i++){
			int a, b;
			in >> a >> b;
			a+=MAX;
			b+=MAX;
			if(edge[a][0]==0)	edge[a][0]=b;
			else				edge[a][1]=b;
			if(edge[b][0]==0)	edge[b][0]=a;
			else				edge[b][1]=a;
			node[j++] = a;
			node[j++] = b;
		}
		
		for(i = 0; i < j; i++){
			if(edge[node[i]][1]==0) prev = max(prev, node[i]);
		}
		if(I==0){
			out << prev - MAX << '\n';
			continue; 
		}
	 
		cur = edge[prev][0];
		cout << prev << " " <<cur<<'\n'; 
		for(i = 1; i < I; i++){
			if(edge[cur][0]==prev){
				prev = cur;
				cur = edge[prev][1];
			}else{
				prev = cur;
				cur = edge[prev][0];
			}
		}
		for(i = 0; i < j; i++){
			edge[node[i]][0]=0;
			edge[node[i]][1]=0;
			node[i] = 0;
		}
		out << cur - MAX << '\n';
	}
	return 0;
}
