#pragma GCC optimization ("Ofast")
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
	pair<int, int> S, E;
	bool negtive;
	int count, x, i;
	while(getline(input, s)){
		switch(s[1]){
			case 's':{//"Assign"
				negtive = false;
				count = 0;
				for(i = 10; s[i] < '0' || s[i] > '9'; i++);
				for(; i < s.size(); i++){
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
							S.first = x;
							break;
						}
						case 1:{
							S.second = x;
							break;
						}
						case 2:{
							H[s[7] - 'a'][S] = negtive ? -x : x;
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
				s.clear();
				for(auto out: H[2]){
					s.push_back('(');  
					intToS(s, out.first.first);
					s.push_back(' ');
					intToS(s, out.first.second);
					s.push_back(' ');
					intToS(s, out.second);
					s.push_back(')');
					s.push_back(' ');
				}
				s.push_back('\n');
				output << s;
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
						if(H[0][mA.first] == 0 || H[1][mB->first] == 0) continue;
						H[2][make_pair(mA.first.first, mB->first.second)] += H[0][mA.first] * H[1][mB->first];
					}
				}
			}break;	
			case 'd':{//"Add"
				for(auto m: H[0]){
					x = H[0][m.first] + H[1][m.first];
					if(x) H[2][m.first] = x;
				}
				for(auto m: H[1]){
					x = H[0][m.first] + H[1][m.first];
					if(x) H[2][m.first] = x;
				}
			}break;
		}
	}
	return 0;
}
