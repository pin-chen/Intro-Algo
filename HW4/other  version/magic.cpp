#include "data.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#define int int_fast32_t
using namespace std;
inline int lowBit(int x) {
    return x & -x;
}
inline int query(int x, vector<int> &bit) {
    int sum = 0;
    for(int i = x; i > 0; i -= lowBit(i)) {
        sum += bit[i];
    }
    return sum;
}
inline void update(int x, int d, vector<int> &bit, int n) {
    for(int i=x;i<=n;i+=lowBit(i)) {
        bit[i] += d;
    }
}
struct ele {
    int x, id;
    bool operator<(const ele & a) const {
        return x > a.x;
    }
};
inline long long reversePairs(vector<int>& nums) {
    int n = nums.size();
    vector<int> bit(n + 1, 0);
    vector<ele> tmp(n, ele{});
    for(int k=0;k<n;k++) {
        tmp[k] = ele{nums[k], k + 1};
    }
    sort(tmp.begin(), tmp.end());
    long long ans = 0;
    int now = 0;
    for(int k=0;k<n;k++) {
        ele ee = tmp[k];
        int x = ee.x, id = ee.id;
        while (now < n) {
            if ((long long)x <= (long long)tmp[now].x - x) {
                update(tmp[now].id, 1, bit, n);
                now++;
            } else {
                break;
            }
        }
        ans += query(id - 1, bit);
    }
    return ans;
}
    
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	int i, n, t, j;
	vector<int> nums;
	
	for(t = 0; t < test_data->testcase_num; t++){
		n = test_data->seq_num[t];
		nums.resize(n);
		for(i = 0, j = n - 1; i < n; i++, j--){
			nums[j] = test_data->seq[t][i];
		}
		out << reversePairs(nums) << '\n';
	}
}

