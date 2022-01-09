#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, m, i, j, k, ans;
	int set[2][32768] = {};
	int setL[2] = {};
	bool w, match;
	in >> n;
	while(n--){
		in >> m;
		string substr[m];
		string str;
		for(i = 0; i < m; i++){
			in >> substr[i];
		}
		in >> str;
		setL[0] = 0;
		setL[1] = 0;
		for(j = 0; j < m; j++){
			match = 1;
			if(str.size() < substr[j].size()){
				continue;
			}
			for(k = 0; k < substr[j].size(); k++){
				if(substr[j][k] != str[0 + k]){
					match = 0;
					break;
				}
			}
			if(match){
				if(k == str.size()){
					out << '1' << '\n';
					goto fin;
				}
				set[0][setL[0]] = k;
				setL[0]++;
			}
		}
		w = 0;
		for(ans = 1; ; ans++){
			if(setL[w] == 0){
				out << "-1\n";
				goto fin;
			}
			for(i = 0; i < setL[w]; i++){
				for(j = 0; j < m; j++){
					match = 1;
					if(str.size() < substr[j].size() + set[w][i]){
						continue;
					}
					for(k = 0; k < substr[j].size(); k++){
						if(substr[j][k] != str[set[w][i] + k]){
							match = 0;
							break;
						}
					}
					if(match){
						if(set[w][i] + k == str.size()){
							out << ans + 1 << '\n';
							goto fin;
						}
						set[!w][setL[!w]] = set[w][i] + k;
						setL[!w]++;
					}
				}
			}
			cout << setL[w] << '\n';
			setL[w] = 0;
			w = !w;
		}
		fin:
		continue;
	}
	return 0;
}
