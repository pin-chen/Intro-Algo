#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include <algorithm>
#include <cmath>
#define FILE 1024

char x[FILE+FILE];
char* s = &x[FILE];

int input(int& p, std::ifstream& in){
	int num = 0;
	while(s[p] > 32){
		num = num * 10 + (s[p] - '0');
		if(++p == FILE){
			in.read(s, FILE);
			p = 0;
		}
	}
	if(++p == FILE){
		in.read(s, FILE);
		p = 0;
	}
	return num;
}

int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in.read(s, FILE);
	int n, S, t, i, nowN, ans, index = 0, num;
	float x, nowP, p, r, W, L;
	std::pair<float, float> range[10001];
	for(t = 0; t < 936; t++){
		n = input(index, in);
		L = input(index, in);
		W = input(index, in);
		S = 0;
		for(i = 0; i < n; i++){
			p = input(index, in);
			r = input(index, in);
			if(r + r <= W) continue;
			x = sqrt( r * r -  W * W / 4 );
			range[S++] = std::make_pair(p - x, p + x);
		}
		range[S] = std::make_pair(L+1.0,L+1.0);
		sort(range, range + S);
		for(nowP= 0.0, nowN = 0, ans = 0; nowP < L; ans++, nowN = i, nowP = p){
			bool nope = 1;
			p = nowP;
			for(i = nowN; range[i].first <= nowP; i++){
				if(range[i].second > p){
					p = range[i].second;
					nope = 0;
				}
			}
			if(nope) break;
		}
		if(nowP >= L){
			out << ans << '\n';
		}else{
			out << "-1\n";
		}
	}
	return 0;
}
