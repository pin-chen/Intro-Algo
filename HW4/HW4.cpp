#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define test 10
using namespace std;

long long count1 = 0;
long long count2 = 0;
int n;
void merge1(vector<int>& initial, vector<int>& result, const int start, const int mid, const int end){
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
    //if(start == 0 && end == n-1) return;
    iR = end; 
    iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    result[i] = initial[iL--];
        else if(iL - start < 0) result[i] = initial[iR--];
        else if(initial[iR] < initial[iL]){
            result[i] = initial[iR--];
        }else{
        	count2 += iR - mid;
            result[i] = initial[iL--];
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
    for(int size = test; size < arr.size(); size *= 2){
        mergePass(arr, temp, size);
        size *= 2;
        mergePass(temp, arr, size);
    }
    
}
vector<int> arr;

void insert_sort(vector<int>& temp, const int start, const int end){
	//cout << end << '\n';
	for(int i = start; i <= end; i++){
		if(temp[i] < 0){
			for(int k = i-1; k >= start && temp[k] <= temp[i]/2; k--){
				if((long long)temp[k] + temp[k] <= temp[i]){
					count1++;
				}
			}
		}else{
			for(int k = i-1; k >= start && temp[i] >= temp[k]; k--){
				if((long long)temp[k] + temp[k] <= temp[i]){
					count1++;
				}
			}
		}
		sort(temp.begin()+start, temp.begin()+i+1, greater<int32_t>());
	}
}
vector<int32_t> temp;
vector<int32_t> temp2;
int nX;
void merge_last(){
    int iR = nX - nX/2 - 1, iL = nX/2 - 1;
    for(int i = nX - 1; i >= 0; i--){
        if(iR < 0)    break;
        else if(iL < 0) break;
        else if((long long)temp[iL] + temp[iL] > temp2[iR]){
        	iR--;
        }else{
            count1 += iR + 1;
            iL--;
        }
    }
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt"); 
	int T;
	long long ans;
	in >> T;
	while(T--){
		count1 = 0;
		ans = 0;
		in >> nX;
		n = nX/2;
		temp.resize(n);
		int i;
		for(int i = 0; i < n; i++){
			in >> temp[i];
		}
		
		int j;
		for(j = test; j < n; j += test){
			insert_sort(temp, j - test, j - 1);
		}
		insert_sort(temp, j - test, n - 1);
		//for(auto x : temp)cout << x << " ";
		cout << '\n'; 
		merge_sort(temp);
		n = nX - nX/2;
		temp2.resize(n);
		for(int i = 0; i < n; i++){
			in >> temp2[i];
		}
		for(j = test; j < n; j += test){
			insert_sort(temp2, j - test, j - 1);
		}
		insert_sort(temp2, j - test, n - 1);
		merge_sort(temp2);
		
		merge_last();
		out << count1 << '\n';
	}
	return 0;
}
