#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	int n, m, i, j, k, ans;
	std::set<int> word[2];
	bool w, match;
	std::string cmp, str;
	in >> n;
	while(n--){
		in >> m;
		std::string substr[m+1];
		substr[m].push_back('{');
		for(i = 0; i < m; i++){
			in >> substr[i];
		}
		in >> str;
		str.push_back(' ');
		word[0].clear();
		word[1].clear();
		sort(substr, substr + m);
		cmp.push_back(str[0] + 1);
		for(j = std::lower_bound(substr, substr + m, str.substr(0,1)) - substr; substr[j] < cmp; j++){
			match = 1;
			for(k = 1; k < substr[j].size(); k++){
				if(substr[j][k] != str[k]){
					match = 0;
					break;
				}
			}
			if(match){
				word[0].insert(k);
			}
		}
		cmp.clear();
		w = 0;
		for(ans = 2; ; ans++){
			if(word[w].size() == 0){
				out << "-1" << '\n';
				break;
			}
			for(auto x: word[w]){
				cmp.push_back(str[x] + 1);
				for(j = std::lower_bound(substr, substr + m, str.substr(x,1)) - substr; substr[j] < cmp; j++){
					match = 1;
					for(k = 1; k < substr[j].size(); k++){
						if(substr[j][k] != str[x + k]){
							match = 0;
							break;
						}
					}
					if(match){
						if(x + k == str.size() - 1){
							out << ans << '\n';
							goto fin;
						}
						word[!w].insert(x + k);
					}
				}
				cmp.clear();
			}
			word[w].clear();
			w = !w;
		}
		fin:
		continue;
	}
	return 0;
}
