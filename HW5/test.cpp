#include <iostream>
#include <unordered_map>
using namespace std;
int main(){
	unordered_map<int, pair<int,int>> m;
	m[1];
	cout << m[1].first << " " << m[1].second<<'\n';
	return 0;
}
