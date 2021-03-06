#include <fstream>
#include <iostream>
#include <algorithm>
#define int int_fast32_t
#define small_case 16
#define MEM 840000
#define FILE 10000
int_fast64_t count1;
int n;
int32_t mem[MEM+500000+MEM];
int32_t* arr = &mem[MEM];
int32_t* temp = &mem[MEM+500000];
char x[FILE+FILE+FILE];
char* s = &x[FILE];

inline void insert_sort(const int start, const int end){
	for(int i = start; i <= end; i++){
		int j;
		for(j = i-1; j >= start; j--){
			if(arr[i] < arr[j]){
				break;
			}
		}
		int e;
		if(start < i){
			e=std::upper_bound(arr+start, arr+i-1, arr[i], std::greater<int32_t>())-arr;
			if(arr[start] < arr[i]) e = start-1;
			if(arr[i-1] >= arr[i]) e = i -1;
			std::cout << j << " " <<e<<'\n';
		}
			
		//else if(arr[i-1]<=arr[j])
		if(arr[i] < 0){
			for(int k = i-1;  arr[k] <= arr[i]/2 &&  k >= start; k--){
				if((long long)arr[k] + arr[k] <= arr[i]){
					count1++;
				}
			}
		}else{
			int g = 0;
			for(int k = i-1; k > j; k--){
				if((long long)arr[k] + arr[k] <= arr[i]){
					count1++;
					g++;
				}
			}
			
		}
		int32_t temp = arr[i];
		for(int k = i; k > j + 1; k--){
			arr[k] = arr[k-1];
		}
		arr[j+1] = temp;
	}
}

inline void counter(const int start, const int mid, const int end){
 	int j = mid;
    for(int i = end; i > mid; i--){
    	while(j >= 0 && (long long) arr[j] + arr[j] <= arr[i]){
    		count1 += i - mid;
    		j--;
		}
	}
}

void merge1(const int start, const int mid, const int end){
	for(int i = start; i <= end; i++) temp[i - start] = arr[i];
    int s = start, e = end - start, m = mid - start, i, j;
	for(i = 0, j = m + 1; i <= m; ){
    	while(j <= e && temp[j] >= temp[i]){
    		arr[s++] = temp[j++];
		}
		arr[s++] = temp[i++];
	}
	while(j <= e){
		arr[s++] = temp[j++];
	}
}

void merge_sort(const int start, const int end){
	if(end - start < small_case){
		insert_sort(start, end);
	}else{
        int mid = (end + start) / 2;
        merge_sort(start, mid);
        merge_sort(mid + 1, end);
       	counter(start, mid, end);
       	merge1(start, mid, end);
        //inplace_merge(arr+start, arr+mid+1, arr+end+1, std::greater<int32_t>());
    }
}

inline void input(int32_t& num, int& p, std::ifstream& in, char end){
	bool negitive = 0;
	num = 0;
	while(s[p] != end){
		if(s[p] == '-')
			negitive = 1;
		else 
			num = num * 10 + (s[p] - '0');
		if(++p == FILE){
			in.read(s, FILE);
			p = 0;
		}
	}
	if(negitive) num = 0 - num;
	if(++p == FILE){
		in.read(s, FILE);
		p = 0;
	}
}

int32_t main(){
	std::ofstream out("output.txt");
	std::ifstream in("input.txt");
	in.read(s, FILE);
	int p = 0;
	int i, j, T;
	input(T, p, in, '\n');
	while(T--){
		//
		count1 = 0;
		input(n, p, in, ' ');
		//
		for(i = 0; i < n - 1; i++){
			input(arr[i], p, in, ' ');
		}
		input(arr[i], p, in, '\n');
		//
		merge_sort(0, n/2);
		merge_sort(n/2+1, n-1);
		counter(0, n/2, n-1);
		//
		out << count1 << '\n';
	}
	return 0;
}
