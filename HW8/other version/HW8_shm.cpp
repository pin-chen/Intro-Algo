#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
#include <fstream>
#include <algorithm>
#include <cmath>
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	int n, S, t, i, nowN, ans;
	double x, nowP, p, r, W, L;
	std::pair<double, double> range[10001];
	for(t = 0; t < 936; t++){
		n = test_data->data[t].n;
		L = test_data->data[t].l;
		W = test_data->data[t].w;
		S = 0;
		for(i = 0; i < n; i++){
			p = test_data->data[t].p[i];
			r = test_data->data[t].r[i];
			if(r + r <= W) continue;
			x = sqrt( r * r -  W * W / 4 );
			range[S++] = std::make_pair(p - x, p + x);
		}
		range[S] = std::make_pair(L+1.0,L+1.0);
		sort(range, range + S);
		ans = 0;
		nowP = 0.0;
		nowN = 0;
		while(nowP < L){
			bool nope = 1;
			p = nowP;
			for(i = nowN; range[i].first <= nowP; i++){
				if(range[i].second > p){
					p = range[i].second;
					nope = 0;
				}
			}
			if(nope) break;
			ans++;
			nowN = i;
			nowP = p;
		}
		if(nowP >= L){
			out << ans << '\n';
		}else{
			out << "-1\n";
		}
	}
}
