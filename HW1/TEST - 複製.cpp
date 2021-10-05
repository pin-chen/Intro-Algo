#include <iostream>
#include <fstream>
#define SIZE 5001
using namespace std;
int main(){
	//Input
	FILE *in;
	in = fopen("input.txt","rb");
	fseek(in,0,SEEK_END);
	long fsize = ftell(in);
	fseek(in,0,SEEK_SET);
	char *string =(char*) malloc(fsize + 1);
	fread(string, 1, fsize, in);
	fclose(in);
	string[fsize] = '\r';
	//
	int now = 0;
	int n = 0;
	while(string[now] >= '0' && string[now] <= '9'){
		n = n * 10 + (string[now] - '0');
		now++;
	}
	now++;
	now++;
	int now_start = 0;
	int table[SIZE] = {};
	while(n>0){
		int x = 0;
		while(string[now] >= '0' && string[now] <= '9'){
			x = x * 10 + (string[now] - '0');
			now++;
		}
		
		table[x]++; 
		if(string[now] == '\r'){
			bool zero = false;
			for(int i = 1; i < SIZE; i++){
				while(table[i] > 0){
					bool D = true;
					if(zero){
						string[now_start] = ' ';
						now_start++;
					}
					zero = true;
					int G = i; 
					for(int j = 1000; j >= 1; j /= 10){
						char w = '0' + G / j ;
						G %= j;
						if(w == '0' && D) continue;
						string[now_start] = w;
						now_start++;
						D = false;
					}
					table[i]--;
				}
			}
			//string[now_start] = '\r';
			//now_start++;
			string[now_start] = '\n';
			now_start++;
			now++;
			n--;
		}
		now++;
	}
	//Output
	FILE *out;
	out = fopen("output.txt","wb");
	fwrite(string, 1, now_start - 1, out);
	fclose(out);
	free(string);
	//
	return 0;
}
