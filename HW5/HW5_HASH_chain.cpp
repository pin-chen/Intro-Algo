#include <iostream>
#include <fstream>
#define MAX 10000001
#define HASH_MASK 0x0000FFFF
using namespace std;
struct NODE{
	int node;
	int edge;
	NODE *next;
};
NODE edge_chain[20000002];
NODE edge[20000002];
NODE* now;
int node[100000], cur;
int n, I, i, j, t, a, b, k, e;
int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> t;
	while(t--){
		in >> n >> I;
		e=0;
		//cout << "\n\n*******\n" <<  t << " " << n << " " << I << '\n'; 
		n--;
		//cout << "input" << '\n'; cout << a << " " << b << '\n';
		for(i = 0, j = 0; i < n; i++){
			in >> a >> b;
			//cout <<"Before: " <<  a << " " << b << '\n';
			a += MAX;
			b += MAX;
			//cout << "After: " << a << " " << b << '\n';
			now = &edge[a&HASH_MASK];
			if(now->node!=0){
				while(now->node!=a&&now->next!=nullptr){
					now=now->next;
				}
			}else{
				node[j++]=a;
				now->node = a;
			}
			if(now->node!=a){
				now->next=&edge_chain[e++];
				now=now->next;
				node[j++]=a;
				now->node=a;
			}
			now->edge ^= (b^-1);
			//cout << now << '\n';
			now = &edge[b&HASH_MASK];
			if(now->node!=0){
				while(now->node!=b&&now->next!=nullptr){
					now=now->next;
				}
			}else{
				node[j++]=b;
				now->node = b;
			}
			if(now->node!=b){
				now->next=&edge_chain[e++];
				now=now->next;
				node[j++]=b;
				now->node=b;
			}
			
			now->edge ^= (a^-1);
			//cout << now << '\n';
			//cout << "xxxxxxxx " <<  j << '\n';
		}
		//cout << "j " << j << '\n';
		cur = 0;
		//cout << "Find" <<'\n'; 
		for(i = 0; i < j; i++){
			now = &edge[node[i]&HASH_MASK];
			//cout << "e" << '\n';
			//cout << node[i] << '\n';
			//cout << now->node << '\n';
			//cout << now->node << '\n';
			while(now->node!=node[i]){
				//cout << now << " "<< now->node << '\n';
				now = now->next;
			}
			//cout << now->node << " " << node[i] << '\n';
			if(now->edge < 0){
				if(node[i] > cur) cur = node[i];
				now->edge ^= -1;
				if(b == 0) break;
				b = 0;
			}
		}
		//cout << "Chain" << '\n';
		for(i = I; i > 0; i--){
			//cout << "a";
			a = cur;
			now = &edge[cur&HASH_MASK];
			while(now->node!=cur){
				now = now->next;
			}
			cur = now->edge ^ b;
			b = a;
		}
		//cout << "Ans" << '\n';
		//cout << cur - MAX << '\n';
		out << cur - MAX << '\n';
		//cout << "Reset" << '\n';
		for(i = 0; i < j; i++){
			now = &edge[node[i]&HASH_MASK];
			now->edge =0;
			now->node =0;
			now->next =nullptr;
		}
		for(i = 0; i < e; i++){
			edge_chain[i].node = 0;
			edge_chain[i].edge = 0;
			edge_chain[i].next = nullptr;
		}
	}
	return 0;
}
