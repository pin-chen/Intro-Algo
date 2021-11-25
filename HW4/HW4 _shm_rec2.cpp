#include "data.hpp"
#include <fstream>
#include <cstring>
#define int int_fast32_t
#define small_case_n 14
#define small_case_p 17
int_fast64_t count1;
int n;
int32_t mem[1500000];
int32_t* arr = &mem[790000];
int32_t* temp = &mem[540000];
void insert_sort_n(const int start, const int end){
	int i, j, k;
	for(i = start; i <= end; i++){
		for(j = i-1; j >= start; j--){
			if(arr[i] <= arr[j]){
				break;
			}
		}
		for(k = i-1;  arr[k] <= arr[i]/2 &&  k >= start; k--){
			if((long long)arr[k] + arr[k] <= arr[i]){
				count1++;
			}
		}
		int32_t temp = arr[i];
		for(k = i; k > j + 1; k--){
			arr[k] = arr[k-1];
		}
		arr[j+1] = temp;
	}
}

void insert_sort_p(const int start, const int end){
	int i, j ,k;
	for(i = start; i <= end; i++){
		for(j = i-1; j >= start; j--){
			if(arr[i] <= arr[j]){
				break;
			}
		}
		for(k = i-1; k > j; k--){
			if((long long) arr[k] + arr[k] <= arr[i] ){
				count1++;
			}
		}
		int32_t temp = arr[i];
		for(k = i; k > j + 1; k--){
			arr[k] = arr[k-1];
		}
		arr[j+1] = temp;
	}
}

inline void merge1(const int start, const int mid, const int end){
    int i = 0, iL = start, iR = mid + 1;
	while(iL <= mid){
    	while(arr[iR] >= arr[iL] && iR <= end){
    		temp[i++] = arr[iR++];
		}
		temp[i++] = arr[iL++];
	}
	if(iR <= end) std::memcpy(temp+i, arr+iR, (end-iR+1)*sizeof(int32_t));
	std::memcpy(arr+start, temp, (end-start+1)*sizeof(int32_t));
}

inline void counter(const int start, const int mid, const int end){
 	int iR = end, iL = mid;
 	while(iR > mid){
 		while((long long)arr[iL] + arr[iL] <= arr[iR] && iL >= start){
 			iL--;
            count1 += iR - mid;
		}
		iR--; 
	}
}

void merge_sort_p(const int start, const int end){
	if(end - start < small_case_p){
		insert_sort_p(start, end);
	}else{
        int mid = (end + start) / 2;
        merge_sort_p(start, mid);
        merge_sort_p(mid + 1, end);
       	counter(start, mid, end);
        merge1(start, mid, end);
    }
}

void merge_sort_n(const int start, const int end){
	if(end - start < small_case_n){
		insert_sort_n(start, end);
	}else{
        int mid = (end + start) / 2;
        merge_sort_n(start, mid);
        merge_sort_n(mid + 1, end);
       	counter(start, mid, end);
        merge1(start, mid, end);
    }
}

void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	int i, j, t;
	for(t = 0; t < test_data->testcase_num; t++){
		count1 = 0;
		n = test_data->seq_num[t];
		for(i = 0, j = 0; i < n; i++){
			if(test_data->seq[t][i] >= 0){
				arr[j] = test_data->seq[t][i];
				count1 += i - j;
				j++;
			}
		}
		merge_sort_p(0, j/2);
		merge_sort_p(j/2+1, j-1);
		counter(0, j/2, j-1);
		for(i = 0, j = 0; i < n; i++){
			if(test_data->seq[t][i] < 0){
				arr[j] = test_data->seq[t][i];
				j++;
			}
		}
		merge_sort_n(0, j/2);
		merge_sort_n(j/2+1, j-1);
		counter(0, j/2, j-1);
		out << count1 << '\n';
	}
}
