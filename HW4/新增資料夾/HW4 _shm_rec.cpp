#include "data.hpp"
#include <iostream> 
#include <fstream>
#include <algorithm>
#define int int_fast32_t
#define small_case_n 12
#define small_case_p 16
int_fast64_t count1;
int n;
int32_t mem[1200000];
int32_t* arr = &mem[640000];
int32_t* temp = &mem[1050000];

void insert_sort_n(const int start, const int end){
	for(int i = start; i <= end; i++){
		int j;
		for(j = i-1; j >= start; j--){
			if(arr[i] <= arr[j]){
				break;
			}
		}
		for(int k = i-1;  arr[k] <= arr[i]/2 &&  k >= start; k--){
			if((long long)arr[k] + arr[k] <= arr[i]){
				count1++;
			}
		}
		int32_t temp = arr[i];
		for(int k = i; k > j + 1; k--){
			arr[k] = arr[k-1];
		}
		arr[j+1] = temp;
	}
}

void insert_sort_p(const int start, const int end){
	for(int i = start; i <= end; i++){
		int j;
		for(j = i-1; j >= start; j--){
			if(arr[i] <= arr[j]){
				break;
			}
		}
		for(int k = i-1; k > j; k--){
			if((long long)arr[k] + arr[k] <= arr[i]){
				count1++;
			}
		}
		int32_t temp = arr[i];
		for(int k = i; k > j + 1; k--){
			arr[k] = arr[k-1];
		}
		arr[j+1] = temp;
	}
}

void merge1(const int start, const int mid, const int end){
	for(int i = start; i <= end; i++) temp[i - start] = arr[i];
    int iR = end - start, iL = mid - start;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    arr[i] = temp[iL--];
        else if(iL < 0) arr[i] = temp[iR--];
        else if(temp[iR] < temp[iL]){
            arr[i] = temp[iR--];
        }else{
            arr[i] = temp[iL--];
        }
    }
}

inline void counter(const int start, const int mid, const int end){
 	int iR = end, iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    break;
        else if(iL - start < 0) break;
        else if((long long)arr[iL] + arr[iL] > arr[iR]){
        	iR--;
        }else{
            count1 += iR - mid;
            iL--;
        }
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
			std::cout << test_data->seq[t][i] << " ";
			if(test_data->seq[t][i] >= 0){
				arr[j] = test_data->seq[t][i];
				count1 += i - j;
				j++;
			}	
		}
		std::cout << '\n';
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
