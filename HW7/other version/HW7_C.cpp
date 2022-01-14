#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <fstream>
#include <string>
int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	int n, m, i, j, k, ans, L, sL;
	bool w, match;
	int dp[32770];
	in >> n;
	while(n--){
		in >> m;
		std::string dicstr[m];
		std::string str;
		for(i = 0; i < m; i++){
			in >> dicstr[i];
		}
		in >> str;
		L = str.size();
		for(i = 0; i < L; i++) dp[i] = m;
        dp[L] = 1;
		for(i = L - 1; i >= 0; i--){
			for(j = 0; j < m; j++){
				sL = dicstr[j].size();
				if( i + sL <= L){
					if(dp[i + sL] == m) continue;
					if(str.substr(i,sL) == dicstr[j]){
						dp[i] = std::min(dp[i], dp[i+sL] + 1);
					}
				}
			}
		}
		out << dp[0] - 1 << '\n';
	}
	return 0;
}
