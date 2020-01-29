# include <iostream>
# include <vector>
# include "algpoints.h"

using namespace std;

int getMaxBits(vector<int> arr) {
    
    int maxBits = 0;
    for (int i = 0; i < arr.size(); i++) {
        int val = arr[i];
        int curBits = 0;
        while (val > 0) {
            val /= 10;
            curBits++;
        }
        if (curBits > maxBits) {
            maxBits = curBits;
        }
    }
    return maxBits;
}

// 基数排序
void Algpoints::radix_sort(vector<int>& arr) {
    
    int num_bins = 10;
    // 声明10个桶
    vector<vector<int> > bins(10);
    // 获取循环次数
    int length = getMaxBits(arr);

    int r = 1;
    // 算法
    for (int i = 0; i < length; i++) {
        
        // 将数组拆分到桶中
        for (int j = 0; j < arr.size(); j++) {
            int curVal = arr[j];
            int tmp = curVal / r;
            int num_index = tmp%num_bins;
            bins[num_index].push_back(curVal);
        }

        // 从桶中拿出元素，在原有数组上排列
        int idx = 0;
        for (int j = 0; j < bins.size(); j++) {
            vector<int> bin = bins[j];
            for (int k = 0; k  < bin.size(); k++) {
                arr[idx] = bin[k];
                idx++;
            }
            bins[j].clear();
        }

        // 处理完当前位, 处理下一位
        r *= 10;

    }

}

int main() {
    int arr[6] = {1, 0, 6, 3, 8, 2};
    vector<int> v(arr,arr+6);
    Algpoints alg;
    alg.radix_sort(v);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}