#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <fstream>
using namespace std;
int_fast16_t n, m, i, t, x, y;
struct list{
	list* next;
	list* prev;
	int_fast16_t num;
};
int_fast16_t R[20];
list C[20];
list *head = &C[0];
int_fast32_t chessR1, chessR2, chessC1, chessC2;
int_fast8_t chessD1[99];
int_fast8_t chessD2[99];
void solve(int_fast16_t x){
	if(x == i){
		m++;
	    return;
	}
	int_fast16_t now_x = R[x];
	for(list *now = head; now != nullptr; now = now->next){
	    if(!(chessD1[now_x + now->num] || chessD2[n - now->num + now_x - 1])){
	    	chessD2[n - now->num + now_x - 1] = true;
	        chessD1[now_x + now->num] = true;
	        if(now != head){
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
				head = now->next;
        		solve(x + 1);
        		head = now;
			}
			chessD1[now_x + now->num] = false;
	        chessD2[n - now->num + now_x - 1] = false;
	    }
	}
}
int main(){
	C[0].next = &C[1];
	for(i = 1; i < 19; i++){
		C[i].next = &C[i + 1];
		C[i].prev = &C[i - 1];
	}
	C[19].prev = &C[18];
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	in >> t;
	while(t--){
		in >> n >> m;
		chessR1 = 0;
		chessR2 = 0;
		chessC1 = 0;
		chessC2 = 0;
		for(i = 0; i < 2 * n - 1; i++) chessD1[i] = false;
		for(i = 0; i < 2 * n - 1; i++) chessD2[i] = false;
		for(i = 0; i < m; i++){
			in >> x >> y;
			if(x < 33)	chessR1 = chessR1 | (1 << x);
			else 		chessR2 = chessR2 | (1 << x);
			if(y < 33)	chessC1 = chessC1 | (1 << y);
			else 		chessC2 = chessC2 | (1 << y);
			chessD1[x + y] = true;
			chessD2[n - y + x - 1] = true;
		}
		for(i = 0, x = 0, y = 0; i < n && i < 33; i++){
			if(!(chessR1 & (1 << i))) R[x++] = i;
			if(!(chessC1 & (1 << i))) C[y++].num = i;
		}
		for(; i < n; i++){
			if(!(chessR2 & (1 << i))) R[x++] = i;
			if(!(chessC2 & (1 << i))) C[y++].num = i;
		}
		i = n - m;
		m = 0;
		C[i - 1].next = nullptr;
		solve(0);
		out << m << '\n';
		C[i - 1].next = &C[i];
	}
	return 0;
}
