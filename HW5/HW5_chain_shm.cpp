#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
#include <fstream>
#define MAX 10000001
#define SIZE 200000
#define HASH_MASK 0x0000FFFF
struct NODE{
	int node;
	int edge;
	NODE *next;
};
NODE mem[1000000];
NODE *edge_chain = &mem[SIZE+0x10000];
NODE *edge = &mem[SIZE];
NODE *now;
int node[250000];
int cur;
int_fast32_t n, I, i, j, t, a, b, k;
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n - 1;
		I = test_data->testcase[t].i;
		k = 0;
		for(i = 0, j = 0; i < n; i++){
			a = test_data->testcase[t].edges[i][0] + MAX;
			b = test_data->testcase[t].edges[i][1] + MAX;
			now = &edge[a&HASH_MASK];
			if(now->node!=0){
				for(;now->node != a && now->next != nullptr; now = now->next);
				if(now->node != a){
					now->next = &edge_chain[k++];
					now = now->next;
					now->node = a;
				}
			}else{
				node[j++] = a&HASH_MASK;
				now->node = a;
			}
			now->edge ^= (b^-1);
			now = &edge[b&HASH_MASK];
			if(now->node!=0){
				for(;now->node != b && now->next != nullptr;now=now->next);
				if(now->node != b){
					now->next = &edge_chain[k++];
					now = now->next;
					now->node = b;
				}
			}else{
				node[j++] = b&HASH_MASK;
				now->node = b;
			}
			now->edge ^= (a^-1);
		}
		b = 2;
		if( I+I < n){
			cur = 0;
			for(i = 0; i < k; i++){
				now = &edge_chain[i];
				if(now->edge < 0){
					if(now->node > cur) cur = now->node;
					now->edge ^= -1;
					b--;
					if(b == 0) break;
				}
			}
			if(b != 0){
				for(i = 0; i < j; i++){
					now = &edge[node[i]];
					if(now->edge < 0){
						if(now->node > cur) cur = now->node;
						now->edge ^= -1;
						b--;
						if(b == 0) break;
					}
				}
			}
			for(i = I; i > 0; i--){
				a = cur;
				for(now = &edge[cur&HASH_MASK]; now->node != cur; now = now->next);
				cur = now->edge ^ b;
				b = a;
			}
		}else{
			cur = 20000002;
			for(i = 0; i < k; i++){
				now = &edge_chain[i];
				if(now->edge < 0){
					if(now->node < cur) cur = now->node;
					now->edge ^= -1;
					b--;
					if(b == 0) break;
				}
			}
			if(b != 0){
				for(i = 0; i < j; i++){
					now = &edge[node[i]];
					if(now->edge < 0){
						if(now->node < cur) cur = now->node;
						now->edge ^= -1;
						b--;
						if(b == 0) break;
					}
				}
			}
			for(i = n - I; i > 0; i--){
				a = cur;
				for(now = &edge[cur&HASH_MASK]; now->node != cur; now = now->next);
				cur = now->edge ^ b;
				b = a;
			}
		}
		out << cur - MAX << '\n';
		for(i = 0; i < j; i++) edge[node[i]] = {};
		for(i = 0; i < k; i++) edge_chain[i] = {};
	}
}
