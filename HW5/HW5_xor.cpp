#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include <iostream> 
#define MAX 10000001
using namespace std;
int edge[20000002];
int node[100000];
int_fast32_t n, I, i, j, T, a, b;
int main(){
	int prev, cur;
	ofstream out("output.txt");
	ifstream in("input.txt");
	in >> T; 
	while(T--){
		in >> n >> I;
		for(i = 0, j = 0; i < n-1; i++){
			in >> a >> b;
			a+=MAX;
			b+=MAX;
			edge[a] ^= b ^ -1;
			edge[b] ^= a ^ -1;
			node[j++] = a;
			node[j++] = b;
		}
		prev = 0;
		for(i = 0; i < j; i++){
			if(edge[node[i]] < 0){
				prev = max(prev, node[i]);
				edge[node[i]]^=-1;
			}
		}
		if(I==0){
			out << prev - MAX<< '\n';
			for(i = 0; i < j; i++){
				edge[node[i]]=0;
			}
			continue;
		}
		cur = edge[prev];
		for(i = 1; i < I; i++){
			int temp = cur;
			cur = edge[cur]^prev;
			prev = temp;
		}
		
		for(i = 0; i < j; i++){
			edge[node[i]]=0;
		}
		out << cur - MAX << '\n';
	}
}
