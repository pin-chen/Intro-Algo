#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	int m, a, b;
	while(in >> m){
		vector<vector<int>> adj;
		vector<int> color;
		adj.resize(6);
		color.resize(6);
		while(m--){
			in >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		for(int i = 0; i < color.size(); i++){
			if(color[i] != 0) continue;
			queue<int> q;
			color[i] = 1;
			q.push(i);
			while(q.size() != 0){
				for(int i = 0; i < adj[q.front()].size(); i++){
					if(color[adj[q.front()][i]] == 0){
						q.push(adj[q.front()][i]);
						if(color[q.front()] == 1){
							color[adj[q.front()][i]] = 2;
						}else{
							color[adj[q.front()][i]] = 1;
						}
					}else{
						if(color[q.front()] == color[adj[q.front()][i]]){
							return false;
						}
					}
				}
				q.pop();
			}
		}
		if(BFS(adj, color)){
			out << "0";
			for(int i = 1; i < 6; i++){
				if(color[i] == 1) out << "," << i;
			}
			out << '\n';
		}else{
			out << "-1\n"; 
		} 
	}
		
	return 0;
}
