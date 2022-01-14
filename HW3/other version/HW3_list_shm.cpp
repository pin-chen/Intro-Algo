#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
#include "data.hpp"
using namespace std;
int n, m, i, k, x, y;
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
void X(int x){
	if(x == i){
		m++;
	    return;
	}
	int now_x = R[x];
	for(list *now = head; now != nullptr; now = now->next){
	    if(!(chessD1[now_x + now->num] || chessD2[n - now->num + now_x - 1])){
	    	chessD2[n - now->num + now_x - 1] = true;
	        chessD1[now_x + now->num] = true;
	        if(now != head){
	        	if(now->next != nullptr){
	        		now->prev->next = now->next;
	        		now->next->prev = now->prev;
	        		X(x + 1);
	        		now->next->prev = now;
	        		now->prev->next = now;
				}else{
					now->prev->next = now->next;
	        		X(x + 1);
	        		now->prev->next = now;
				}
			}else{
				head = now->next;
        		X(x + 1);
        		head = now;
			}
			chessD1[now_x + now->num] = false;
	        chessD2[n - now->num + now_x - 1] = false;
	    }
	}
}
void solve(tTestData* test_data){
	C[0].next = &C[1];
	for(i = 1; i < 19; i++){
		C[i].next = &C[i + 1];
		C[i].prev = &C[i - 1];
	}
	C[19].prev = &C[18];
	ofstream out("output.txt", ios::out);
	for(k = 0; k < test_data->t; k++){
		n = test_data->testcase[k].n;
		m = test_data->testcase[k].m;
		for(i = 0; i < n; i++) chessR[i] = false;
		for(i = 0; i < n; i++) chessC[i] = false;
		for(i = 0; i < 2 * n - 1; i++) chessD1[i] = false;
		for(i = 0; i < 2 * n - 1; i++) chessD2[i] = false;
		for(i = 0; i < m; i++){
			x = test_data->testcase[k].preplace[i][0];
			y = test_data->testcase[k].preplace[i][1];
			chessR[x] = true;
			chessC[y] = true;
			chessD1[x + y] = true;
			chessD2[n - y + x - 1] = true;
		}
		for(i = 0, x = 0, y = 0; i < n; i++){
			if(!chessR[i]) R[x++] = i;
			if(!chessC[i]) C[y++].num = i;
		}
		i = n - m;
		m = 0;
		C[i - 1].next = nullptr;
		X(0);
		out << m << '\n';
		C[i - 1].next = &C[i];
	}
}
