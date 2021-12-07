#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
//#include <iostream>
#include <fstream>
#include <cstdint>
//using namespace std;
#define HASH_MASK 0x00007FFF
#define SIZE HASH_MASK+61755
struct NODE{
	int node;
	intptr_t edge;
	NODE *next;
};
NODE mem[510000];
NODE *edge_chain = &mem[SIZE+HASH_MASK+1];
NODE *edge = &mem[SIZE];
NODE *now;
NODE *nowA;
NODE *nowB;
NODE *now1;
NODE *now2;
NODE *now3;
int_fast32_t n, I, i, j, t, a, b, k, cur;
void solve(tTestData* test_data){
//int main(){
//	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
//	in >> t;
	for(t = 0; t < test_data->t; t++){
//	while(t--){
//		in >> n >> I;
//		n--;
		n = test_data->testcase[t].n - 1;
		I = test_data->testcase[t].i;
		k = 0;
		for(i = 0, j = 0; i < n; i++){
//			in >> a >> b;
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
		for(nowA = &edge[a&HASH_MASK]; nowA->node != a; nowA = nowA->next);
		for(nowB = &edge[b&HASH_MASK]; nowB->node != b; nowB = nowB->next);
		now1 = nowA;
		now2 = nowB;
		while((NODE*)(nowA->edge ^ (intptr_t)nowB) != nullptr){
			j++;
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
			nowB = now;
		}
		now3 = nowA;
		nowA = now2;
		nowB = now1;
		while((NODE*)(nowA->edge ^ (intptr_t)nowB) != nullptr){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
			nowB = now;
		}
		if(now3->node > nowA->node) nowA = now3;
		nowB = nullptr;
		for(i = I; i > 0; i--){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
			nowB = now;
//			cout << nowB->node << " ";
			nowB->node = 0;
			nowB->edge = 0;
			nowB->next = nullptr;
		}
		out << nowA->node << '\n';
		for(i = n-I; i >= 0; i--){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (intptr_t)nowB);
			nowB = now;
//			cout << nowB->node << " ";
			nowB->node = 0;
			nowB->edge = 0;
			nowB->next = nullptr;
		}
		//cout << '\n';
		//for(i = 0; i <= HASH_MASK; i++) edge[i] = {};
		//for(i = 0; i < k; i++) edge_chain[i] = {};
	}
//	return 0;
}
