#include "data.hpp"
#include <fstream> 
#include <vector>
#define int int_fast32_t
#define small_case 5
using namespace std;

int_fast64_t count1;
int n, t, i, j;
vector<int32_t> arr;
vector<int32_t> temp;

void insert_sort(const int start, const int end){
	for(int i = start; i <= end; i++){
		int j;
		for(j = i-1; j >= start; j--){
			if(temp[i] <= arr[j]){
				break;
			}
		}
		for(int k = i-1; k >= start; k--){
			if((long long)arr[k] + arr[k] <= temp[i]){
				count1++;
			}
		}
		for(int k = i; k > j + 1; k--){
			arr[k] = arr[k-1];
		}
		arr[j+1] = temp[i];
	}
}

void merge1(vector<int32_t>& initial, vector<int32_t>& result, const int start, const int mid, const int end){
    int iR = end, iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    break;
        else if(iL - start < 0) break;
        else if((long long)initial[iL] + initial[iL] > initial[iR]){
        	iR--;
        }else{
            count1 += iR - mid;
            iL--;
        }
    }
    if(start == 0 && end == n - 1) return;
    iR = end; 
    iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    result[i] = initial[iL--];
        else if(iL - start < 0) result[i] = initial[iR--];
        else if(initial[iR] < initial[iL]){
            result[i] = initial[iR--];
        }else{
            result[i] = initial[iL--];
        }
    }
}

void merge_sort(){
    for(int size = small_case; size < n; size += size){
        //mergePass(arr, temp, size);
		int i;
	    for(i = 0; i < n - 2 * size + 1; i += size + size){
	        merge1(arr, temp, i, i + size - 1, i + 2 * size - 1);
	    }
	    if(n - i + 1 > size)   merge1(arr, temp, i, i + size - 1, n - 1);
	    else                   merge1(arr, temp, i, n - 1, n - 1);
        //
		size += size;
        //mergePass(temp, arr, size);
	    for(i = 0; i < n - 2 * size + 1; i += 2 * size){
	        merge1(temp, arr, i, i + size - 1, i + 2 * size - 1);
	    }
	    if(n - i + 1 > size)  merge1(temp, arr, i, i + size - 1, n - 1);
	    else                  merge1(temp, arr, i, n - 1, n - 1);
    	//
	}
}



void solve(tTestData* test_data){
	arr.resize(500000);
	temp.resize(500000);
	ofstream out("output.txt");
	for(t = 0; t < test_data->testcase_num; t++){
		count1 = 0;
		n = test_data->seq_num[t];
		for(i = 0; i < n; i++){
			temp[i] = test_data->seq[t][i];
		}
		for(i = small_case; i < n; i += small_case){
			insert_sort(i - small_case, i - 1);
		}
		insert_sort(i - small_case, n - 1);
		merge_sort();
		out << count1 << '\n';
	}
}
