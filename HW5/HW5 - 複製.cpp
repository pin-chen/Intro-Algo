#include <iostream>
#include <fstream>
#include <algorithm>
#define MAX 10000000
using namespace std;
long long edge[100000];
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int T;
	in >> T;
	while(T--){
		int n, I, cur, i, j;
		in >> n >> I;
		for(i = 0, j = 0; i < n - 1; i++){
			int a, b;
			in >> a >> b;
			a+=MAX;
			b+=MAX;
			edge[j++] = (long long) (a<<32) | b;
			edge[j++] = (long long) (b<<32) | a;
		}
		sort(edge, edge+j);
		for(i = 0; i < j; i++){
			if(edge[i]>>32 == edge[i+1]>>32) i++;
			
		}
	}
	return 0;
}
