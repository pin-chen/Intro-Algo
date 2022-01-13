#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt"); 
	int n, L, W, S, t, i, p , r, nowN;
	double x, nowP;
	std::pair<double, double> range[10000];
	while(in >> n >> L >> W){
		S = 0;
		for(i = 0; i < n; i++){
			in >> p >> r;
			if(r + r < W) continue;
			x = sqrt(r * r - W * W / 4);
			range[S++] = std::make_pair(p - x, p + x);
		}
		out << "-1\n";
	}
	return 0;
}
