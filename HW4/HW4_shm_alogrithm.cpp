#include "data.hpp"
#include <fstream> 
#include <vector>
#include <algorithm>
#define int int_fast16_t
using namespace std;

int_fast32_t count1;
int n;


void merge1(vector<int32_t>& initial, const int start, const int mid, const int end){
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
    inplace_merge(initial.begin()+start, initial.begin()+mid+1, initial.begin()+end+1);
}
void mergePass(vector<int32_t>& initial, const int size){
    int i = 0;
    for(i = 0; i < n - 2 * size + 1; i += 2 * size){
        merge1(initial, i, i + size - 1, i + 2 * size - 1);
    }
    if(initial.size() - i + 1 > size)   merge1(initial, i, i + size - 1, n - 1);
    else                            	merge1(initial, i, n - 1, n - 1);
}

void merge_sort(vector<int32_t>& arr){
    for(int size = 1; size < n; size *= 2){
        mergePass(arr, size);
    }
}
void solve(tTestData* test_data){
	int i, j, t;
	vector<int32_t> arr;
	ofstream out("output.txt");
	for(t = 0; t < test_data->testcase_num; t++){
		count1 = 0;
		n = test_data->seq_num[t];
		arr.resize(n);
		for(i = 0, j = n - 1; i < n; i++, j--){
			arr[j] = test_data->seq[t][i];
		}
		merge_sort(arr);
		out << count1 << '\n';
	}
}
