#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
using namespace std;
int n, m, i, t, x, y;
struct list{
	list* next;
	list* prev;
	int num;
};
int R[20];
list C[20];
list *head = &C[0];
bool chessR[50];
bool chessC[50];
bool chessD1[99];
bool chessD2[99];
void solve(int x){
	if(x == i){
		m++;
	    return;
	}
	int now_x = R[x];
	for(list *now = head; now != nullptr; now = now->next){
	    if(!(chessD1[now_x + now->num] || chessD2[n - now->num + now_x - 1])){
	        chessD1[now_x + now->num] = true;
	        chessD2[n - now->num + now_x - 1] = true;
	        if(now->prev != nullptr){
	        	if(now->next != nullptr){
	        		now->prev->next = now->next;
	        		now->next->prev = now->prev;
	        		solve(x + 1);
	        		now->next->prev = now;
	        		now->prev->next = now;
				}else{
					now->prev->next = now->next;
	        		solve(x + 1);
	        		now->prev->next = now;
				}
			}else{
				if(now->next != nullptr){
					head = now->next;
	        		now->next->prev = now->prev;
	        		solve(x + 1);
	        		now->next->prev = now;
	        		head = now;
				}else{
					head = now->next;
	        		solve(x + 1);
	        		head = now;
				}
			}
			chessD1[now_x + now->num] = false;
	        chessD2[n - now->num + now_x - 1] = false;
	    }
	}
}
int main(){
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	in >> t;
	while(t--){
		in >> n >> m;
		for(i = 0; i < n; i++){
			chessR[i] = false;
			chessC[i] = false;
		}
		for(i = 0; i < 2 * n - 1; i++){
			chessD1[i] = false;
			chessD2[i] = false;
		}
		for(i = 0; i < m; i++){
			in >> x >> y;
			chessR[x] = true;
			chessC[y] = true;
			chessD1[x + y] = true;
			chessD2[n - y + x - 1] = true;
		}
		for(i = 0, x = 0, y = 0; i < n; i++){
			if(!chessR[i]) R[x++] = i;
			if(!chessC[i]){
				if(y != 0)C[y].prev = &C[y - 1];
				else C[y].prev = nullptr;
				if(y != n - m - 1) C[y].next = &C[y + 1];
				else C[y].next = nullptr;
				C[y++].num = i;
			}
		}
		i = n - m;
		m = 0;
		solve(0);
		out << m << '\n';
	}
	return 0;
}
