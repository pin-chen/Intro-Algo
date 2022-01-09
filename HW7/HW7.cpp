#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <fstream>
#include <string>
#include <set>
int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	int n, m, i, j, k, ans;
	std::set<int> word[2];
	bool w, match;
	in >> n;
	while(n--){
		in >> m;
		std::string substr[m];
		std::string str;
		for(i = 0; i < m; i++){
			in >> substr[i];
		}
		in >> str;
		str.push_back(' ');
		word[0].clear();
		word[1].clear();
		for(j = 0; j < m; j++){
			match = 1;
			for(k = 0; k < substr[j].size(); k++){
				if(substr[j][k] != str[k]){
					match = 0;
					break;
				}
			}
			if(match){
				word[0].insert(k);
			}
		}
		w = 0;
		for(ans = 1; ; ans++){
			if(word[w].size() == 0){
				out << "-1" << '\n';
				break;
			}
			for(auto x: word[w]){
				for(j = 0; j < m; j++){
					match = 1;
					for(k = 0; k < substr[j].size(); k++){
						if(substr[j][k] != str[x + k]){
							match = 0;
							break;
						}
					}
					if(match){
						if(x + k == str.size()-1){
							out << ans + 1 << '\n';
							goto fin;
						}
						word[!w].insert(x + k);
					}
				}
			}
			word[w].clear();
			w = !w;
		}
		fin:
		continue;
	}
	return 0;
}
