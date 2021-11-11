#include <fstream>
#define int int_fast32_t
//#define int32_t int_fast32_t
#define small_case 16
#define MEM 640000
#define MAX_READ 500

int_fast64_t count1;
int n, nX;
int32_t mem[MEM+MEM+750000];
int32_t* arr = &mem[MEM];
int32_t* arr2;
int32_t* temp;
char x[1500];
char* in=&x[500];

void insert_sort(int32_t* arrX, const int start, const int end){
	for(int i = start; i <= end; i++){
		int j;
		for(j = i-1; j >= start; j--){
			if(temp[i] <= arrX[j]){
				break;
			}
		}
		if(temp[i] < 0){
			for(int k = i-1;  arrX[k] <= temp[i]/2 &&  k >= start; k--){
				if((long long)arrX[k] + arrX[k] <= temp[i]){
					count1++;
				}
			}
		}else{
			for(int k = i-1; k > j; k--){
				if((long long)arrX[k] + arrX[k] <= temp[i]){
					count1++;
				}
			}
		}
		for(int k = i; k > j + 1; k--){
			arrX[k] = arrX[k-1];
		}
		arrX[j+1] = temp[i];
	}
}

void merge_last(){
    int iR = n - 1, iL = nX/2 - 1;
    for(int i = nX - 1; i >= 0; i--){
        if(iR < 0)    	return;
        else if(iL < 0) return;
        else if((long long)arr[iL] + arr[iL] > arr2[iR]){
        	iR--;
        }else{
            count1 += iR + 1;
            iL--;
        }
    }
}

void merge1(int32_t* initial, int32_t* result, const int start, const int mid, const int end){
    int iR = end, iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    result[i] = initial[iL--];
        else if(iL - start < 0) result[i] = initial[iR--];
        else if(initial[iR] < initial[iL]){
            result[i] = initial[iR--];
        }else{
            result[i] = initial[iL--];
        }
    }
    iR = end; 
    iL = mid;
    for(int i = end; i >= start; i--){
        if(iR - mid - 1 < 0)    return;
        else if(iL - start < 0) return;
        else if((long long)initial[iL] + initial[iL] > initial[iR]){
        	iR--;
        }else{
            count1 += iR - mid;
            iL--;
        }
    }
}

void merge_sort(int32_t* arr){
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

inline int input(int& index, std::ifstream& fin, char delimiter) {
	int integer = 0, flag = 1;
	while (in[index] != delimiter) {
		if (in[index] == '-') {
			flag = -1;
		}
		else {
			integer = integer * 10 + (in[index] - '0');
		}
		index++;
		if (index == MAX_READ) {
			fin.read(in, MAX_READ);
			index = 0;
		}
	}
	integer *= flag;
	index++;
	if (index == MAX_READ) {
		fin.read(in, MAX_READ);
		index = 0;
	}
	return integer;
}

int32_t main(){
	std::ofstream out("output.txt");
	std::ifstream fin("input.txt");
	fin.read(in, MAX_READ);
	int index = 0;
	int i, j;
	int T = input(index, fin, '\n');
	while(T--){
		count1 = 0;
		nX = input(index, fin, ' ');
		arr2 = &mem[nX+MEM+1];
		temp = &mem[nX/2+MEM];
		n = nX/2;
		for(i = 0; i < n - 1; i++){
			temp[i] = input(index, fin, ' ');
		}
		temp[i] = input(index, fin, ' ');
		for(i = small_case; i < n; i += small_case){
			insert_sort(arr, i - small_case, i - 1);
		}
		insert_sort(arr, i - small_case, n - 1);
		merge_sort(arr);
		n = nX - n;
		for(i = 0; i < n - 1; i++){
			temp[i] = input(index, fin, ' ');
		}
		temp[i] = input(index, fin, '\n');
		for(i = small_case; i < n; i += small_case){
			insert_sort(arr2, i - small_case, i - 1);
		}
		insert_sort(arr2, i - small_case, n - 1);
		merge_sort(arr2);
		merge_last();
		out << count1 << '\n';
	}
	return 0;
}
