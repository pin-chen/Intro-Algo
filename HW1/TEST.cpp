#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "data.hpp"
using namespace std;
void solve(tTestData* test_data){
	fstream ans;
	ans.open("output.txt",ios::out);
	int table[20001] = {};
	for(int i = 0; i < test_data->cnt; i++){
		for(int j = 0; j < test_data->seq_size[i]; j++){
			table[test_data->data[i][j]]++;
		}
		for(int j = 1; j < 20001; j++){
			while(table[j] > 0){
				ans << j << " ";
				table[j]--;
			}
		}
		ans << '\n';
	}
}
