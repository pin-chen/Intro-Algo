#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
void intToS(string& OUT, int x){
	if(x == 0){
		OUT.push_back('0');
		return;
	}
	if(x < 0){
		OUT.push_back('-');
		x = -x;
	}
	int begin = OUT.size();
	while(x > 0){
		OUT.push_back('0' + (x % 10) );
		x /= 10;
	}
	int end = OUT.size() - 1;
	for(int i = begin; i <= begin + (end - begin) / 2; i++){
		char temp = OUT[i];
		OUT[i] = OUT[end - i + begin];
		OUT[end - i + begin] = temp;
	}
}
int main(){
	ifstream input("input.txt",ios::in);
	ofstream output("output.txt",ios::out);
	map< pair<int,int>, int > H[3];
	string s;
	pair<int, int> point, S, E;
	bool negtive, start;
	int count, x;
	while(getline(input, s)){
		switch(s[1]){
			case 's':{//"Assign"
				negtive = false;
				start = true;
				count = 0;
				for(int i = 10; i < s.size(); i++){
					if(start){
						if(s[i] < '0' || s[i] > '9' ){
							continue;
						}
					}	
					start = false;
					if(s[i] == '-'){
						i++;
						negtive = true;
					}
					x = 0;
					while(s[i] >= '0' && s[i] <= '9' && i < s.size()){
						x = x * 10 + (s[i] - '0');
						i++;
					}
					switch(count){
						case 0:{
							point.first = x;
							break;
						}
						case 1:{
							point.second = x;
							break;
						}
						case 2:{
							H[s[7] - 'a'][point] = negtive ? -x : x;
							break;
						}
					}
					count++;
				}
			}break;
			case 'e'://"Delete"
			case 'n'://"Init"
			case 'a':{//"Matrix"
				break;
			}
			case 'r':{//"Print"
				string OUT;
				for(auto out: H[2]){
					OUT.push_back('(');  
					intToS(OUT, out.first.first);
					OUT.push_back(' ');
					intToS(OUT, out.first.second);
					OUT.push_back(' ');
					intToS(OUT, out.second);
					OUT.push_back(')');
					OUT.push_back(' ');
				}
				OUT.push_back('\n');
				output << OUT;
				H[0].clear();
				H[1].clear();
				H[2].clear();
			}break;
			case 'u':{//"Mult"
				for(auto mA: H[0]){
					S = make_pair(mA.first.second,0);
					E = make_pair(mA.first.second + 1,0);
					H[1][S];
					H[1][E];
					for(auto mB = H[1].find(S); mB != H[1].find(E); mB++){
						point = make_pair(mA.first.first, mB->first.second);
						if(H[0][mA.first] == 0 || H[1][mB->first] == 0) continue;
						H[2][point] += H[0][mA.first] * H[1][mB->first];
						if( H[2][point] == 0) H[2].erase( H[2].find(point) );
					}
				}
			}break;	
			case 'd':{//"Add"
				int temp;
				for(auto m: H[0]){
					temp = H[0][m.first] + H[1][m.first];
					if(temp) H[2][m.first] = temp;
				}
				for(auto m: H[1]){
					temp = H[0][m.first] + H[1][m.first];
					if(temp) H[2][m.first] = temp;
				}
			}break;
		}
	}
	return 0;
}
