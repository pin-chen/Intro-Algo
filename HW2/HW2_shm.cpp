#include <iostream>
#include <string>
#include <vector>
#include <map>
#pragma GCC optimization ("O2")
#include <fstream>
#include "data.hpp"
using namespace std;
void solve(tTestData* test_data){
	fstream output("output.txt",ios::out);
	vector< map< pair<int,int>, int > > H;
	H.resize(3);
	for(int i = 0; i < test_data->line_num; i++){
		switch(test_data->data[i][1]){
			case 's':{//"Assign"
				int pos = test_data->data[i][7] - 'a';
				pair<int, int> point;
				int x, count = 0;
				for(int j = 10;; j++){
					x = 0;
					while(test_data->data[i][j] >= '0' && test_data->data[i][j] <= '9'){
						x = x * 10 + (test_data->data[i][j] - '0');
						j++;
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
							H[pos][point] = x;
							break;
						}
					}
					if(test_data->data[i][j] == '\0')break;
					count++;
				}
			}break;	
			case 'r':{//"Print"
				int pos = test_data->data[i][6] - 'a';
				string OUT;
				for(auto out: H[pos]){
					OUT += "(" + to_string(out.first.first) + " " + to_string(out.first.second )+ " " + to_string(out.second) + ")" + " ";
				}
				OUT.push_back('\n');
				output << OUT;
			}break;	
			case 'e':{//"Delete"
				int pos = test_data->data[i][7] - 'a';
				H[pos].clear();
			}break;
			case 'u':{//"Mult"
				int A = test_data->data[i][5] - 'a';
				int B = test_data->data[i][9] - 'a';
				int C = test_data->data[i][13] - 'a';
				for(auto mA: H[A]){
					pair<int, int> pointA = mA.first;
					pair<int, int> S = make_pair(pointA.second,0);
					pair<int, int> E = make_pair(pointA.second + 1,0);
					H[B][S];
					H[B][E];
					for(auto mB = H[B].find(S); mB != H[B].find(E); mB++){
						pair<int, int> pointB = mB->first;
						pair<int, int> pointC = make_pair(pointA.first, pointB.second);
						H[C][pointC] += H[A][pointA] * H[B][pointB];
						if(H[C][pointC]==0) H[C].erase(H[C].find(pointC));
					}
				}
			}break;	
			case 'd':{//"Add"
				int a = test_data->data[i][4] - 'a';
				int b = test_data->data[i][8] - 'a';
				int c = test_data->data[i][12] - 'a';
				for(auto m: H[a]){
					int temp = H[a][m.first] + H[b][m.first];
					if(temp) H[c][m.first] = temp;
				}
				for(auto m: H[b]){
					int temp = H[a][m.first] + H[b][m.first];
					if(temp) H[c][m.first] = temp;
				}
			}break;
		}
	}
} 
