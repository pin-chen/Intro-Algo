#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long count1 = 0;

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
    int i = 0;
    for(i = 0; i < (int) initial.size() - 2 * size + 1; i += 2 * size){
        merge1(initial, result, i, i + size - 1, i + 2 * size - 1);
    }
    if(initial.size() - i + 1 > size)   merge1(initial, result, i, i + size - 1, initial.size() - 1);
    else                            	merge1(initial, result, i, initial.size() - 1, initial.size() - 1);
}

void merge_sort(vector<int>& arr){
    vector<int> temp;
    temp.resize(arr.size());
    for(int size = 1; size < arr.size(); size *= 2){
        mergePass(arr, temp, size);
        size *= 2;
        mergePass(temp, arr, size);
    }
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt"); 
	int T, n;
	long long ans;
	in >> T;
	while(T--){
		count1 = 0;
		ans = 0;
		in >> n;
		vector<int> arr;
		arr.resize(n);
		for(int i = 0; i < n; i++){
			in >> arr[i];
		}
		for(int i = 0; i < n / 2; i++){
			int temp = arr[i];
			arr[i] = arr[n-1-i];
			arr[n-1-i] = temp;
		}
		merge_sort(arr);
		out << count1 << '\n';
	}
	return 0;
}
