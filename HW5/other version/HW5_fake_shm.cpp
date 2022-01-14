#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include "data.hpp"
#define MAX 10000001
#define PRIME 1000007
int edge[PRIME], node[100000], hash[100000], cur;
int_fast32_t n, I, i, j, t, a, b;
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n;
		I = test_data->testcase[t].i;
		for(i = 0, j = 0; i < n-1; i++){
			a = test_data->testcase[t].edges[i][0] + MAX;
			b = test_data->testcase[t].edges[i][1] + MAX;
			hash[j] = a % PRIME;
			edge[hash[j]] ^= (b^-1);
			node[j++] = a;
			hash[j] = b % PRIME;
			edge[hash[j]] ^= (a^-1);
			node[j++] = b;
		}
		b = 0;
		if( I+I < n){
			cur = 0;
			for(i = 0; ; i++){
				if(edge[hash[i]] < 0){
					cur = std::max(cur, node[i]);
					edge[hash[i]] ^= -1;
					if(a == 0) break;
					a = 0;
				}
			}
			for(i = I; i > 0; i--){
				a = cur;
				cur = edge[cur%PRIME] ^ b;
				b = a;
			}
		}else{
			cur = 20000002;
			for(i = j-1; i >= 0; i--){
				if(edge[hash[i]] < 0){
					cur = std::min(cur, node[i]);
					edge[hash[i]] ^= -1;
					if(a == 0) break;
					a = 0;
				}
			}
			for(i = n - I; i > 1; i--){
				a = cur;
				cur = edge[cur%PRIME] ^ b;
				b = a;
			}
		}
		out << cur - MAX << '\n';
		for(i = 0; i < j; i++) edge[hash[i]] = 0;
	}
}
