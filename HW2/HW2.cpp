#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
using namespace std;

typedef unordered_multiset< vector<int> > matrix;
typedef unordered_map<string,  matrix> HASH;

int main(){
	fstream input("input.txt",ios::in);
	fstream output("output.txt",ios::in);
	HASH H;
	sting s;
	stringstream ss;
	while(getline(input, s)){
		ss << s;
		ss >> s;
		switch(s){
			case "Matrix":
				ss >> s;
				M.insert(s);
			break;
			case "Assign":
			break;
			case "Mult":
			break;
			case "Print":
			break;
			case "Delete":
			break;
			case "Add":
			break;		
		}
	}
	return 0;
} 
