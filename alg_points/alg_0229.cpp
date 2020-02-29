# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
# include "algpoints.h"

using namespace std;

// 设置双指针，来计算连续的非零元素的个数，个数最大的即为面积最大的，返回当前最大面积
int calcMaxRecSize(vector<int> nums) {
    if (nums.size() == 0) return 0;
    int pre=0, cur=0;
    int maxSize = 0;
    while (cur < nums.size()) {
        // pre cur共同移动
        while (cur < nums.size() && pre < nums.size() && nums[pre] == 0 && nums[cur] == 0) {
            pre++;
            cur++;
        }
        // cur单独移动
        while (cur < nums.size() && nums[cur] > 0) {
            cur++;
        }
        // 此时cur为非0元素或界外, 计算当前面积
        if (pre < nums.size()) {
            maxSize = max(maxSize, (cur-pre)*nums[pre]);
        }else break;
        pre = cur;
    }
    return maxSize;
}

// // 其实该方法还能使用单调栈来求解，但是却多了O（N）的空间复杂度，有点大材小用的感觉
// int calcMaxRecSizeV2(vector<int> nums){
//     // 如果使用单调栈来求解的话，栈内元素从下到上是非递减的。
//     // 出栈条件为当前遍历的元素 小于 栈顶元素
//     // 对每个出栈的元素来计算当前矩阵面积。
//     stack<int> st;

//     for (int i = 0; i < nums.size(); i++) {
        
//         if (st.empty() || nums[st.top()] <= nums[i]) {
//             // 进栈
//             continue;
//         }
//         //出栈
//         while (!st.empty() && nums[st.top()] > nums[i]) {
//             // 对每个出栈的元素计算矩阵面积
//             maxSize = max(maxSize, curSize);
//         }
//     }
//     // 对栈内遗留元素进行处理，因为很有可能数据里全是非零值或者数组某个位置的右侧全是非零值
//     while (!st.empty()) {
//         // 出栈并计算面积
//         maxSize = max(maxSize, curSize);
//     }
//     return maxSize;

// }

// 一个矩阵中，只存在0，1元素，找出面积最大全1矩阵（或者方阵，解法应该都是一样的，就是判断下是不是方阵, 下面解决矩阵）
int Algpoints::maxRectangle(vector<vector<int> > nums) {
    // 首先矩阵中元素均为1，只要含有1个0便无效
    // 具体思路是，以每一行为矩阵的底边来求解
    if (nums.size() == 0 || nums[0].size() == 0) return 0;
    int row = nums.size();
    int col = nums[0].size();
    vector<int> height(col);
    int maxSize = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            height[j] = (nums[i][j] == 0) ? 0 : 1;
        }
        maxSize = max(maxSize, calcMaxRecSize(height));
    }
    return maxSize;
}

int main() {
    return 0;
}