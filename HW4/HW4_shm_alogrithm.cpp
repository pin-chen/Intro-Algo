#include "data.hpp"
#include <fstream>
#include <algorithm>
#define int int_fast32_t
#define small_case 16
#define MEM 540000
using namespace std;

int_fast64_t count1;
int n, nX;
int32_t mem[MEM+MEM+750000];
int32_t* arr = &mem[MEM];

void insert_sort(int32_t* arr, const int start, const int end){
	for(int i = start; i <= end; i++){
		int j;
		for(j = i-1; j >= start; j--){
			if(temp[i] <= arr[j]){
				break;
			}
		}
		if(temp[i] < 0){
			for(int k = i-1;  arr[k] <= temp[i]/2 &&  k >= start; k--){
				if((long long)arr[k] + arr[k] <= temp[i]){
					count1++;
				}
			}
		}else{
			for(int k = i-1; k > j; k--){
				if((long long)arr[k] + arr[k] <= temp[i]){
					count1++;
				}
			}
		}
		for(int k = i; k > j + 1; k--){
			arrX[k] = arr[k-1];
		}
		arr[j+1] = temp[i];
	}
}

void merge1(int32_t* initial, const int start, const int mid, const int end){
    int iR = end, iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    break;
        else if(iL - start < 0) break;
        else if((long long)initial[iR] + initial[iR] > initial[iL]){
        	iR--;
        }else{
            count1 += iR - mid;
            iL--;
        }
    }
    inplace_merge(initial+start, initial+mid+1, initial+end+1);
}
void mergePass(int32_t* initial, const int size){
    int i = 0;
    for(i = 0; i < n - 2 * size + 1; i += 2 * size){
        merge1(initial, i, i + size - 1, i + 2 * size - 1);
    }
    if(n - i + 1 > size)   merge1(initial, i, i + size - 1, n - 1);
    else                            	merge1(initial, i, n - 1, n - 1);
}

void merge_sort(int32_t* arr){
    for(int size = 1; size < n; size *= 2){
        mergePass(arr, size);
    }
}
void solve(tTestData* test_data){
	int i, j, t;
	ofstream out("output.txt");
	for(t = 0; t < test_data->testcase_num; t++){
		count1 = 0;
		n = test_data->seq_num[t];
		for(i = 0, j = n - 1; i < n; i++, j--){
			arr[j] = test_data->seq[t][i];
		}
		merge_sort(arr);
		out << count1 << '\n';
	}
}
