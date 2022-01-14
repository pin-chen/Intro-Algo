#include <iostream>
#include <fstream>
#include "data.hpp"
#define MAX_NUM 5001
#define MAX_CHAR 96000
using namespace std;
void solve(tTestData* test_data){
	fstream output("output.txt",ios::out);
	int table[MAX_NUM] = {}, i, j, num, now, t;
	char array[MAX_CHAR], temp;
	bool zero;
	for(i = 0; i < test_data->cnt; i++){
		now = 0;
		for(j = 0; j < test_data->seq_size[i]; j++){
			table[test_data->data[i][j]]++;
		}
		for(j = 1; j < MAX_NUM; j++){
			while(table[j] > 0){
				table[j]--;
				zero = true;
				num = j;
				for(t = 1000; t >= 10; t /= 10){
					temp = '0' + num / t;
					num %= t;
					if(zero && temp == '0') continue;
					zero = false;
					array[now++] = temp;
				}
				array[now++] = '0' + num;
				array[now++] = ' ';
			}
		}
		array[now++] = '\n';
		array[now] = '\0';
		output << array;
	}
}
