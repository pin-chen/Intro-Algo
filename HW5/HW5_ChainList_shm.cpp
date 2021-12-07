#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
#include <fstream>
#define HASH_MASK 0x00007FFF
#define SIZE 140755
struct NODE{
	int node;
	unsigned int edge;
	NODE *next;
};
NODE mem[270000];
NODE *edge_chain = &mem[SIZE+HASH_MASK+1];
NODE *edge = &mem[SIZE];
NODE *MEM[5];
NODE *now = MEM[0];
NODE *nowA = MEM[1];
NODE *nowB = MEM[2];
NODE *now1 = MEM[3];
NODE *now2 = MEM[4];
unsigned int n, I, i, t, k;
int a, b;
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n;
		I = test_data->testcase[t].i;
		k = 0;
		for(i = 0; i < n - 1; i++){
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
				nowB->node = b;
			}
			nowA->edge ^= (intptr_t) nowB;
			nowB->edge ^= (intptr_t) nowA;
		}
		for(now1 = &edge[a&HASH_MASK]; now1->node != a; now1 = now1->next);
		for(now2 = &edge[b&HASH_MASK]; now2->node != b; now2 = now2->next);
		for(nowA = now1, nowB = now2; (NODE*)(nowA->edge ^ (unsigned long long)nowB) != nullptr; ){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
			nowB = now;
		}
		nowB = now1;
		now1 = nowA;
		nowA = now2;
		for( ; (NODE*)(nowA->edge ^ (unsigned long long)nowB) != nullptr; ){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
			nowB = now;
		}
		if(now1->node > nowA->node) nowA = now1;
		nowB = nullptr;
		for(i = I; i > 0; i--){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
			nowB = now;
			nowB->node = 0;
			nowB->edge = 0;
			nowB->next = nullptr;
		}
		out << nowA->node << '\n';
		for(i = n - I; i > 0; i--){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
			nowB = now;
			nowB->node = 0;
			nowB->edge = 0;
			nowB->next = nullptr;
		}
	}
}
