#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
int main(){
	ifstream input("input.txt",ios::in);
	ofstream output("output.txt",ios::out);
	map< pair<int,int>, int > H[3];
	string x, s;
	pair<int, int> point, S, E;
	stringstream ss;
	while(getline(input, s)){
		switch(s[1]){
			case 's':{//"Assign"
				ss << s;
				ss >> x >> x >> point.first >> point.second;
				ss >> H[x[0] - 'a'][point];
				ss.clear();
			}break;
			case 'e'://"Delete"
			case 'n'://"Init"
			case 'a':{//"Matrix"
				break;
			}
			case 'r':{//"Print"
				for(auto out: H[2]){
					output <<  "(" << out.first.first << " " << out.first.second << " " << out.second << ") ";
				}
				output << '\n';
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
