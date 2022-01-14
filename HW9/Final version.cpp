#include <fstream>
#define NUM_OF_NODE 20

bool adj[NUM_OF_NODE][NUM_OF_NODE];
int color[NUM_OF_NODE];
bool fail;

void dfs(int node){
	for(int i = 1; i < NUM_OF_NODE; i++){
		if(adj[node][i]){
			if(color[i] == 0){
				if(color[node] == 1){
					color[i] = 2;
				}else{
					color[i] = 1;
				}
				dfs(i);
			}else{
				if(color[node] == color[i]){
					fail = true;
					return;
				}
			}
		}
	}
}

int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	int m, i, j, a, b;
	while(in >> m){
		fail = false;
		for(i = 0; i < NUM_OF_NODE; i++) color[i] = 0;
		for(i = 0; i < NUM_OF_NODE; i++){
			for(j = 0; j < NUM_OF_NODE; j++){
				adj[i][j] = 0;
			}
		}
		for(i = 0; i < m; i++){
			in >> a >> b;
			adj[a][b] = 1;
			adj[b][a] = 1;
		}
		color[0] = 1;
		dfs(0);
		if(fail){
			out << "-1\n";
		}else{
			out << "0";
			for(int i = 1; i < NUM_OF_NODE; i++){
				if(color[i] == 1) out << "," << i;
			}
			out << '\n';
		}
	}
	return 0;
}
