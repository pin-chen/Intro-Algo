#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
int main(){
	fstream input("input.txt",ios::in);
	fstream output("output.txt",ios::out);
	map< pair<int,int>, int > H[3];
	string x, s;
	pair<int, int> point;
	int pos, A, B, C;
	stringstream ss;
	while(getline(input, s)){
		switch(s[1]){
			case 's':{//"Assign"
				ss << s;
				ss >> x >> x >> point.first >> point.second;
				pos = x[0] - 'a';
				ss >> H[pos][point];
				ss.clear();
			}break;	
			case 'r':{//"Print"
				pos = s[6] - 'a';
				for(auto out: H[pos]){
					output <<  "(" << out.first.first << " " << out.first.second << " " << out.second << ") ";
				}
				output << '\n';
			}break;	
			case 'e':{//"Delete"
				pos = s[7] - 'a';
				H[pos].clear();
			}break;
			case 'u':{//"Mult"
				ss << s;
				ss >> x >> x;
				A = x[0] - 'a';
				ss >> x;
				B = x[0] - 'a';
				ss >> x;
				C = x[0] - 'a';
				for(auto mA: H[A]){
					pair<int, int> S = make_pair(mA.first.second,0);
					pair<int, int> E = make_pair(mA.first.second + 1,0);
					H[B][S];
					H[B][E];
					for(auto mB = H[B].find(S); mB != H[B].find(E); mB++){
						point = make_pair(mA.first.first, mB->first.second);
						H[C][point] += H[A][mA.first] * H[B][mB->first];
						if( H[C][point] == 0) H[C].erase( H[C].find(point) );
					}
				}
				ss.clear();
			}break;	
			case 'd':{//"Add"
				ss << s;
				ss >> x >> x;
				A = x[0] - 'a';
				ss >> x;
				B = x[0] - 'a';
				ss >> x;
				C = x[0] - 'a';
				for(auto m: H[A]){
					int temp = H[A][m.first] + H[B][m.first];
					if(temp) H[C][m.first] = temp;
				}
				for(auto m: H[B]){
					int temp = H[A][m.first] + H[B][m.first];
					if(temp) H[C][m.first] = temp;
				}
				ss.clear();
			}break;
		}
	}
	return 0;
}
