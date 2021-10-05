#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUM 5001
using namespace std;
int main(){
	fstream input("input.txt", ios::in);;
	fstream output("output.txt", ios::out);
	int n;
	int table[MAX_NUM] = {};
	input >> n;
	input.ignore();
	string array;
	while(n--){
		getline(input, array);
		int x = 0;
		for(int i = 0; i < array.size(); i++){
			while(array[i] >= '0' && array[i] <= '9'){
				x = x * 10 + (array[i] - '0');
				i++;
			}
			table[x]++;
			x = 0;
		}
		for(int i = 1; i < MAX_NUM; i++){
			while(table[i] > 0){
				output << i << " ";
				table[i]--;
			}
		}
		output << '\n';
	}
	return 0;
}
