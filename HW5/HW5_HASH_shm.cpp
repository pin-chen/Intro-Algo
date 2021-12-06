#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
#include <fstream>
#define MAX 10000001
#define HASH_MASK 0x0001FFFF
using namespace std;
int edge[20000002][2], node[100000], cur;
int_fast32_t n, I, i, j, t, a, b, k;
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n - 1;
		I = test_data->testcase[t].i;
		for(i = 0, j = 0; i < n; i++){
			a = test_data->testcase[t].edges[i][0] + MAX;
			b = test_data->testcase[t].edges[i][1] + MAX;
			for(k = 0; ; k++){
				if(edge[(a+k)&HASH_MASK][0]==a){
					edge[(a+k)&HASH_MASK][1] ^= (b^-1);
					break;
				}else if(edge[(a+k)&HASH_MASK][0]==0){
					edge[(a+k)&HASH_MASK][0] = a;
					edge[(a+k)&HASH_MASK][1] ^= (b^-1);
					node[j++] = a;
					break;
				}
			}
			for(k = 0; ; k++){
				if(edge[(b+k)&HASH_MASK][0]==b){
					edge[(b+k)&HASH_MASK][1] ^= (a^-1);
					break;
				}else if(edge[(b+k)&HASH_MASK][0]==0){
					edge[(b+k)&HASH_MASK][0] = b;
					edge[(b+k)&HASH_MASK][1] ^= (a^-1);
					node[j++] = b;
					break;
				}
			}
		}
		
		cur = 0;
		//cout << "Find" <<'\n'; 
		for(i = 0; ; i++){
			for(k = 0; ;k++){
				//cout << node[i] << " " << edge[node[i]&HASH_MASK+k][0] << '\n';
				if(edge[(node[i]+k)&HASH_MASK][0]==node[i]) break; 
			}
			if(edge[(node[i]+k)&HASH_MASK][1] < 0){
				//cout << node[i] << '\n';
				if(node[i] > cur) cur = node[i];
				edge[(node[i]+k)&HASH_MASK][1] ^= -1;
				if(b == 0) break;
				b = 0;
			}
			//cout << "a";
		}
		//cout << "Chain" << '\n';
		for(i = I; i > 0; i--){
			//cout << "a";
			a = cur;
			for(k = 0; k < 9;k++){
				//cout << cur << " " << edge[cur&HASH_MASK+k][0] << '\n';
				if(edge[(cur+k)&HASH_MASK][0]==cur) break; 
				
			}
			cur = edge[(cur+k)&HASH_MASK][1] ^ b;
			b = a;
		}
		//cout << "Ans" << '\n';
		//cout << cur - MAX << '\n';
		out << cur - MAX << '\n';
		//cout << "Reset" << '\n';
		/*
		for(i = 0; i < j; i++){
			//cout << "R";
			for(k = 0; ;k++){
				if(edge[(node[i]+k)&HASH_MASK][0]==node[i]){
					edge[(node[i]+k)&HASH_MASK][0] = 0;
					edge[(node[i]+k)&HASH_MASK][1] = 0;
					break;
				}
			}
		}*/
		for(int i = 0; i < 20000002; i++){
			edge[i][0] = 0;
			edge[i][1] = 0;
		} 
	}
}
