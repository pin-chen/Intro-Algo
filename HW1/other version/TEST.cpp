#include<iostream>
#include<fstream>
#include "data.hpp"
#define MAX_NUM 5001
using namespace std;
void solve(tTestData* test_data){
	fstream ans("output.txt",ios::out);
	int table[MAX_NUM] = {};
	for(int i = 0; i < test_data->cnt; i++){
		for(int j = 0; j < test_data->seq_size[i]; j++){
			table[test_data->data[i][j]]++;
		}
		for(int j = 1; j < MAX_NUM; j++){
			while(table[j] > 0){
				ans << j << " ";
				table[j]--;
			}
		}
		ans << '\n';
	}
}
