#include <fstream>
#include <vector>
#include "data.hpp"
using namespace std;

int_fast64_t count1;
int_fast32_t t, i, j;
vector<int> arr;
vector<int> temp;

void merge1(vector<int>& initial, vector<int>& result, const int start, const int mid, const int end){
    int iR = end, iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    result[i] = initial[iL--];
        else if(iL - start < 0) result[i] = initial[iR--];
        else if(initial[iR] >= initial[iL]){
            result[i] = initial[iR--];
        }else{
            result[i] = initial[iL--];
        }
    }
    iR = end; 
    iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    break;
        else if(iL - start < 0) break;
        else if((long long)2 * initial[iR] > initial[iL]){
            iR--;
        }else{
            count1 += iR - mid;
            iL--;
        }
    }
}
void mergePass(vector<int>& initial, vector<int>& result, const int size){
    int i;
    for(i = 0; i < (int) initial.size() - 2 * size + 1; i += 2 * size){
        merge1(initial, result, i, i + size - 1, i + 2 * size - 1);
    }
    if(initial.size() - i + 1 > size)   merge1(initial, result, i, i + size - 1, initial.size() - 1);
    else                            	merge1(initial, result, i, initial.size() - 1, initial.size() - 1);
}

void merge_sort(vector<int>& arr){
    temp.resize(arr.size());
    for(int size = 1; size < arr.size(); size *= 2){
        mergePass(arr, temp, size);
        size *= 2;
        mergePass(temp, arr, size);
    }
}

void solve(tTestData* test_data){
	ofstream out("output.txt");
	for(t = 0; t < test_data->testcase_num; t++){
		count1 = 0;
		arr.resize(test_data->seq_num[t]);
		for(i = 0, j = test_data->seq_num[t] - 1; j >= 0; i++, j--){
			arr[j] = test_data->seq[t][i];
		}
		merge_sort(arr);
		out << count1 << '\n';
	}
}
