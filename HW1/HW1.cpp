#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
int main(){
	fstream input;
	fstream ans;
	input.open("input.txt",ios::in);
	ans.open("output.txt",ios::out);
	int n;
	input >> n;
	input.ignore();
	int table[20001] = {};
	while(n--){
		string s;
		getline(input,s);
		stringstream ss;
		ss << s;
		int x;
		while(ss >> x){
			table[x]++;
		}
		for(int j = 1; j < 20001; j++){
			while(table[j] > 0){
				ans << j << " ";
				table[j]--;
			}
		}
		ans << '\n';
	}
	return 0;
}
