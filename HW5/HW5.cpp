#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#define MAX 214748364
using namespace std;

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int T;
	in >> T;
	while(T--){
		int n, I, cur, prev = -MAX;
		in >> n >> I;
		map<int,vector<int>> edge;
		for(int i = 0; i < n - 1; i++){
			int a, b;
			in >> a >> b;
			edge[a].push_back(b);
			edge[b].push_back(a);
		}
		for(auto x : edge){
			if(x.second.size()==1) prev = max(prev, x.first);
		}
		cur = edge[prev][0];
		for(int i = 0; i < I - 1; i++){
			if(edge[cur][0] == prev){
				prev = cur;
				cur = edge[cur][1];
			}else{
				prev = cur;
				cur = edge[cur][0];
			}
		}
		out << cur << '\n';
	}
	return 0;
}
