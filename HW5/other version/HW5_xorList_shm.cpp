#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
#include <fstream>
#include <cstdint>
#define HASH_MASK 0x00007FFF
#define SIZE HASH_MASK+61755
struct NODE{
	bool one;
	int node;
	intptr_t edge;
	NODE *next;
};
NODE mem[810000];
NODE *edge_chain = &mem[SIZE+HASH_MASK+1];
NODE *edge = &mem[SIZE];
NODE *now;
NODE *nowA;
NODE *nowB;
int MEM[350000];
int *node = &MEM[50000];
int_fast32_t n, I, i, j, t, a, b, k, cur;
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n - 1;
		I = test_data->testcase[t].i;
		k = 0;
		for(i = 0, j = 0; i < n; i++){
			a = test_data->testcase[t].edges[i][0];
			b = test_data->testcase[t].edges[i][1];
			nowA = &edge[a&HASH_MASK];
			nowB = &edge[b&HASH_MASK];
			if(nowA->node!=0){
				for(;nowA->node != a && nowA->next != nullptr; nowA = nowA->next);
				if(nowA->node != a){
					nowA->next = &edge_chain[k++];
					nowA = nowA->next;
					nowA->node = a;
				}
			}else{
				node[j++] = a&HASH_MASK;
				nowA->node = a;
			}
			if(nowB->node!=0){
				for(;nowB->node != b && nowB->next != nullptr;nowB=nowB->next);
				if(nowB->node != b){
					nowB->next = &edge_chain[k++];
					nowB = nowB->next;
					nowB->node = b;
				}
			}else{
				node[j++] = b&HASH_MASK;
				nowB->node = b;
			}
			nowA->edge ^= (intptr_t) nowB;
			nowB->edge ^= (intptr_t) nowA;
			nowA->one = !nowA->one;
			nowB->one = !nowB->one;
		}
		b = 2;
		nowB = nullptr;
		if(I + I < n){
			cur = -10000001;
			for(i = 0; i < k; i++){
				if(edge_chain[i].one == true){
					now = &edge_chain[i];
					if(now->node > cur){
						nowA = now;
						cur = now->node;
					}
					b--;
					if(b == 0) break;
				}
			}
			if(b != 0){
				for(i = 0; i < j; i++){
					if(edge[node[i]].one == true){
						now = &edge[node[i]];
						if(now->node > cur){
							nowA = now;
							cur = now->node;
						}
						b--;
						if(b == 0) break;
					}
				}
			}
			for(i = I; i > 0; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
				nowB = now;
			}
		}else{
			cur = 10000001;
			for(i = 0; i < k; i++){
				if(edge_chain[i].one == true){
					now = &edge_chain[i];
					if(now->node < cur){
						nowA = now;
						cur = now->node;
					}
					b--;
					if(b == 0) break;
				}
			}
			if(b != 0){
				for(i = 0; i < j; i++){
					if(edge[node[i]].one == true){
						now = &edge[node[i]];
						if(now->node < cur){
							nowA = now;
							cur = now->node;
						}
						b--;
						if(b == 0) break;
					}
				}
			}
			for(i = n - I; i > 0; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
				nowB = now;
			}
		}
		out << nowA->node << '\n';
		for(i = 0; i < j; i++) edge[node[i]] = {};
		for(i = 0; i < k; i++) edge_chain[i] = {};
	}
}
