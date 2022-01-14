#include <iostream>
#include <fstream>
#define MAX 10000001
#define HASH_MASK 0x00000FFF
using namespace std;

int edge[20000002][2], node[100000], cur;
int_fast32_t n, I, i, j, t, a, b, k;
int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> t;
	while(t--){
		in >> n >> I;
		cout << "\n\n*******\n" <<  t << " " << n << " " << I << '\n'; 
		n--;
		cout << "input" << '\n'; cout << a << " " << b << '\n';
		for(i = 0, j = 0; i < n; i++){
			in >> a >> b;
			cout <<"Before: " <<  a << " " << b << '\n';
			a += MAX;
			b += MAX;
			cout << "After: " << a << " " << b << '\n';
			for(k = 0; ; k++){
				cout << a << " " << k << " " << edge[(a>>k)&HASH_MASK][0] <<" " << (edge[(a>>k)&HASH_MASK][0]==a) <<'\n';
				if(edge[(a+k)&HASH_MASK][0]==a){
					cout << "HIT" << '\n';
					edge[(a+k)&HASH_MASK][1] ^= (b^-1);
					break;
				}else if(edge[(a+k)&HASH_MASK][0]==0){
					cout << "Empty" << '\n';
					edge[(a+k)&HASH_MASK][0] = a;
					edge[(a+k)&HASH_MASK][1] ^= (b^-1);
					node[j++] = a;
					break;
				}else{
					cout << "MISS" << '\n';
				}
			}
			for(k = 0; ; k++){
				cout << b << " " << k << " " << edge[b&HASH_MASK+k][0] <<" " << (edge[b&HASH_MASK+k][0]==b) <<'\n';
				if(edge[(b+k)&HASH_MASK][0]==b){
					cout << "HIT" << '\n';
					edge[(b+k)&HASH_MASK][1] ^= (a^-1);
					break;
				}else if(edge[(b+k)&HASH_MASK][0]==0){
					cout << "Empty" << '\n';
					edge[(b+k)&HASH_MASK][0] = b;
					edge[(b+k)&HASH_MASK][1] ^= (a^-1);
					node[j++] = b;
					break;
				}else{
					cout << "MISS" << '\n';
				}
			}
			cout << b << " " << k << " " << edge[b&HASH_MASK+k][0] <<" " << (edge[b&HASH_MASK+k][0]==b) <<'\n';
			
			
			
		}
		
		cur = 0;
		cout << "Find" <<'\n'; 
		for(i = 0; ; i++){
			for(k = 0; ;k++){
				cout << node[i] << " " << edge[node[i]&HASH_MASK+k][0] << '\n';
				if(edge[(node[i]+k)&HASH_MASK][0]==node[i]) break; 
			}
			if(edge[(node[i]+k)&HASH_MASK][1] < 0){
				cout << node[i] << '\n';
				if(node[i] > cur) cur = node[i];
				edge[(node[i]+k)&HASH_MASK][1] ^= -1;
				if(b == 0) break;
				b = 0;
			}
			cout << "a";
		}
		cout << "Chain" << '\n';
		for(i = I; i > 0; i--){
			cout << "a";
			a = cur;
			for(k = 0; k < 9;k++){
				cout << cur << " " << edge[cur&HASH_MASK+k][0] << '\n';
				if(edge[(cur+k)&HASH_MASK][0]==cur) break; 
				
			}
			cur = edge[(cur+k)&HASH_MASK][1] ^ b;
			b = a;
		}
		cout << "Ans" << '\n';
		cout << cur - MAX << '\n';
		out << cur - MAX << '\n';
		cout << "Reset" << '\n';
		for(i = 0; i < j; i++){
			cout << "R";
			for(k = 0; ;k++){
				if(edge[(node[i]+k)&HASH_MASK][0]==node[i]){
					edge[(node[i]+k)&HASH_MASK][0] = 0;
					edge[(node[i]+k)&HASH_MASK][1] = 0;
					break;
				}
			}
		}
	}
	return 0;
}
