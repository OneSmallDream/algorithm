# include <iostream>
# include <vector>
# include <stack>
# include <algorithm>
# include "algpoints.h"

using namespace std;

// 输入一个字符串，打印出该字符串中字符的所有排列
// 把一个字符串看成由两部分组成，第一部分为它的第一个字符，第二部分是后面所有字符
// 所以求整个字符换的排列，可以看成两步，首先求所有可能出现在第一个位置上的上字符（即把第一个字符与其它字符交换）
// 第二部则是固定第一个字符，求后面所有字符的排列。（递归过程）

void permute(char* pStr, char* pBegin) {
    if (*pBegin == '\0') {
        cout << pStr << endl;
    }
    else
    {
        for (char* pCH = pBegin; *pCH != '\0'; ++pCH) {
            // 交换字符
            char temp = *pCH;
            *pCH = *pBegin;
            *pBegin = temp;

            //递归处理子问题
            permute(pStr, pBegin+1);

            // 回溯
            temp = *pCH;
            *pCH = *pBegin;
            *pBegin = temp;
        }
    }
}
// 如果不是求字符的排列，而是求字符的组合。
// 如果输入n个字符，则这n个字符能构成长度为1的组合、长度为2的组合、...
// 在求n个字符的长度为m的组合的时候，我们把这n个字符分成两个部分：第一个字符和其余所有字符
// 如果组合里包含第一个字符，则下一步在剩余的n-1个字符里选取m-1个字符；如果组合里不包含第一个字符，则在剩余的n-1个字符里选取m个字符

void Algpoints::Permutation(char* pStr) {
    if (!pStr) {
        return ;
    }
    permute(pStr, pStr);
}


void subsets_process(vector<int>& nums, vector<int>& tmp, vector<vector<int> >& result, int start) {
    
    // 任何情况的子集，都加入到结果集里面
    result.push_back(tmp);
    
    for (int i = start; i < nums.size(); i++) {
        // 当数据里含有相同元素时候, 需要在外部先对数据进行排序，在内部去重
        // if (i > start && nums[i] == nums[i-1]) continue;
        tmp.push_back(nums[i]);
        subsets_process(nums, tmp, result, i+1);
        tmp.pop_back();

    }
}

// 子集, 该问题的解法为大多数递归问题的模板方法
vector<vector<int> > Algpoints::subsets(vector<int>& nums) {

    // 当数据中含有相同元素的时候，需要先进行排序
    sort(nums.begin(), nums.end());
    vector<vector<int> > result;
    vector<int> tmp;
    subsets_process(nums, tmp, result, 0);
    return result;
}


int main() {
    vector<vector<int> > v(5, vector<int>(2));
    cout << v.size() << endl;
    cout << v[0].size() << endl;
    return 0;
}