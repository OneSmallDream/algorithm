# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
# include "algpoints.h"

using namespace std;

// 最大黑方阵
// 题目是给定一个方阵，其中每个单元非黑即白，找出4条边结尾黑色像素的最大方阵
// 这道题的优化方法还是利用空间换时间， 首先最朴素的解法如下
struct Subsquare {
    int row;
    int col;
    int size;
    Subsquare(int r, int c, int s): row(r), col(c), size(s){}
};

bool isValidSubsquare(vector<vector<int> > matrix, int row, int col, int subSize) {
    // 检查上下边界是否均为黑(0)
    for (int j = 0; j < subSize; j++) {
        if (matrix[row][col+j] == 1) {
            return false;
        }
        if (matrix[row+subSize-1][col+j] == 1) {
            return false;
        }
    }
    return true;
}

bool isValidSubsquareV2(vector<vector<pair<int, int> > > processed_matrix, int row, int col, int subSize) {
    
    pair<int, int> topLeft = processed_matrix[row][col];
    pair<int, int> downLeft = processed_matrix[row+subSize-1][col];
    pair<int, int> topRight = processed_matrix[row][col+subSize-1];

    if (topLeft.first < subSize || topLeft.second < subSize || downLeft.first < subSize || topRight.second < subSize) {
        return false;
    }
    return true;

}

Subsquare findSubsquare(vector<vector<int> > matrix, int subSize) {
    int size = matrix.size();
    int count = size - subSize + 1;
    for (int row = 0; row < count; row++) {
        for (int col = 0; col < count; col++) {
            if (isValidSubsquare(matrix, row, col, subSize)) {
                return Subsquare(row, col, subSize);
            }
        }
    }
    return Subsquare(-1, -1, -1);
}

Subsquare Algpoints::findMaxBlackSubsquare(vector<vector<int> > matrix) {
    int size = matrix.size();
    for (int i = size; i >= 1; i--) {
        Subsquare square = findSubsquare(matrix, i);
        if (square.size != -1) return square;
    }
    return Subsquare(-1, -1, -1);
}

vector<vector<pair<int, int> > > process(vector<vector<int> > matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return ;
    }
    int row_size = matrix.size();
    int col_size = matrix[0].size();
    vector<vector<pair<int, int> > > processed_matrix(row_size, vector<pair<int, int> >(col_size));
    
    for (int row = row_size-1; row >= 0; row--) {
        for (int col = col_size-1; col < col_size; col++) {
            int blackRight = 0;
            int blackDown = 0;
            // 只针对黑像素进行处理
            if (matrix[row][col] == 0) {
                blackRight++;
                blackDown++;
                // 累加右侧点信息
                if (col+1<col_size) {
                    blackRight += processed_matrix[row][col+1].first;
                }
                // 累加下侧点信息
                if (row+1 <row_size) {
                    blackDown += processed_matrix[row+1][col].second;
                }
            }
            // 对矩阵当前位置赋值
            processed_matrix[row][col] = make_pair(blackRight, blackDown);

        }
    }
    return processed_matrix;
}

// 最外层遍历边长O(N)，内层遍历矩阵左上侧点O(N^2), 最内层遍历O(N), 总时间复杂度O(N^4)
// 优化方法，利用空间换取时间，最原始矩阵进行预处理，使得判断是否有效的过程从O(N) -> O(1), 从而总时间复杂度为O(N^3)
Subsquare findMaxBlackSubsquare_v2(vector<vector<int> > matrix) {
    // 1. 对原始矩阵进行预处理
    // 2. 针对边长由大到小遍历，找有效方阵
    int size = matrix.size();
    vector<vector<pair<int, int> > > processed_matrix = process(matrix);

    for (int i = size; i >= 1; i--) {
        // 逻辑相同
        // 判断方阵有无效的方法为 isValidSubsquareV2
    }
    
}

// 单调栈，非常重要的概念。在很多题目上都有应用。
unordered_map<int, pair<int, int>> Algpoints::getNearLessNoRepeat(vector<int> nums) {

    unordered_map<int, pair<int, int> > result;
    stack<int> st;

    for (int i = 0; i < nums.size(); i++) {
        // 压栈条件
        if (st.empty() || nums[st.top()] < nums[i]) {
            st.push(i);
            continue;
        }
        
        // 否则出栈, 计算当前栈顶值的相关信息
        while (!st.empty() && nums[st.top()] > nums[i]) {
            int popIndex = st.top();
            st.pop();
            int leftLessIndex = st.empty() ? -1 : st.top();
            int rightLessIndex = i;
            result[popIndex] = make_pair(leftLessIndex, rightLessIndex);
        }
    }

    // 最后很有可能在栈里还存在元素，从下到上递增,他们的右侧没有比他们再小的
    while (!st.empty()) {
        int popIndex = st.top();
        st.pop();
        int leftLessIndex = st.empty() ? -1 : st.top();
        int rightLessIndex = -1;
        result[popIndex] = make_pair(leftLessIndex, rightLessIndex);
    }
    return result;
}

// 这里是数组可能存在重复的情况, 即更通用的解法。
// 在无重复的情况下，压入栈的是index，在有重复的情况下，压入栈的是index的vector
unordered_map<int, pair<int, int> > Algpoints::getNearLessWithRepeat(vector<int> nums) {
    unordered_map<int, pair<int, int> > result;
    stack<vector<int> > st;

    for (int i = 0; i < nums.size(); i++) {
        // 进栈情况1 -- 当前遍历元素 大于 栈顶元素
        if (st.empty() || nums[st.top()[0]] < nums[i]) {
            vector<int> curVec;
            curVec.push_back(i);
            st.push(curVec);
            continue;
        }else if (!st.empty() && nums[st.top()[0]] == nums[i]) {
            // 进栈情况2 -- 当前遍历元素 与 栈顶元素 相等
            st.top().push_back(i);
            continue;
        }

        //出栈并计算相关结果 -- 此时当前遍历元素 小于 栈顶元素
        while (!st.empty() && nums[st.top()[0]] > nums[i]) {
            vector<int> popIndexVec = st.top();
            st.pop();
            int leftLessIndex = st.empty() ? -1 : st.top()[st.top().size()-1];
            for (auto index : popIndexVec) {
                result[index] = make_pair(leftLessIndex, i);
            }
        }
    } 

    // 对栈内遗留元素进行处理, 此时遗留元素由下到上一次递增, 且他们在数组里右侧没有小于它们的元素
    while (!st.empty()) {
        vector<int> popIndexVec = st.top();
        st.pop();
        int leftLessIndex = st.empty() ? -1 : st.top()[st.top().size()-1];
        for (auto index : popIndexVec) {
            result[index] = make_pair(leftLessIndex, -1);
        }
    }

    return result;
}

int main() {
    
    vector<int> nums;
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(0);
    
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

    cout << maxSize << endl;
}