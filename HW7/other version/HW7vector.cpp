#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
using namespace std;
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, m, i, j, k, ans;
	bool w;
	in >> n;
	while(n--){
		in >> m;
		string substr[m];
		string str;
		for(i = 0; i < m; i++){
			in >> substr[i];
		}
		in >> str;
		vector<int> word[2];
		for(j = 0; j < m; j++){
			bool match = 1;
			for(k = 0; k < substr[j].size(); k++){
				if(substr[j][k] != str[k]){
					match = 0;
					break;
				}
			}
			if(match){
				word[0].push_back(k);
			}
		}
		w = 0;
		for(ans = 1; ; ans++){
			if(word[w].size() == 0){
				out << "-1" << '\n';
				goto fin;
			}
			for(auto x: word[w]){
				cout << ans << ":" << x << '\n';
				for(j = 0; j < m; j++){
					bool match = 1;
					for(k = 0; k < substr[j].size(); k++){
						if(substr[j][k] != str[x + k]){
							match = 0;
							break;
						}
					}
					if(match){
						if(x + k == str.size()){
							out << ans + 1 << '\n';
							goto fin;
						}
						word[!w].push_back(x + k);
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
