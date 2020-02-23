# include <string>
# include <iostream>
# include <stack>
# include <unordered_map>
# include "lcalg.h"

using namespace std;


int Lcalg::lc174(vector<vector<int> >& dungeon) {

    // 地下城游戏
    // dp[i][j]表示能够进入当前格子的最低血条
    int row = dungeon.size();
    int col = dungeon[0].size();
    vector<vector<int> > dp(row, vector<int>(col));

    dp[row-1][col-1] = max(1, 1-dungeon[row-1][col-1]);

    //初始化最后一列，利用下一行更新
    for (int i = 2; i <= row; i++) {
        dp[row-i][col-1] = max(1, dp[row-i+1][col-1]-dungeon[row-i][col-1]);
    }
    //初始化最后一行, 利用下一列进行更新
    for (int i = 2; i <=col; i++) {
        dp[row-1][col-i] = max(1, dp[row-1][col-i+1]-dungeon[row-1][col-i]);
    }

    //更新矩阵中间部分
    for (int i = row-2; i >= 0; i--) {
        for (int j = col-2; j >=0; j--) {
            dp[i][j] = max(1, min(dp[i+1][j]-dungeon[i][j], dp[i][j+1]-dungeon[i][j]));
        }
    }

    return dp[0][0];
}   

// lc343递归解法
int lc343_process(int n) {
    if (n == 2) return 1;
    // res = i*F(n-i)，但是当进行整数拆分的时候，显然拆到只剩2的时候，不拆比较大，而n=2时，因为必须要拆分
    // 所以结果为1。所以在进行递归的时候，需要判断res = max(i*max(F(n-i), (n-i)))
    int res = -1;
    for (int i = 2; i <= n; i++) {
        res = max(res, i*max((n-i), lc343_process(n-i)));
    }
    return res;
}
// lc343递归+备忘录解法
int lc343_processv2(int n, unordered_map<int, int>& memory) {
    if (n == 2) return 1;

    // 如果当前结果已经计算过，且存储。则直接返回    
    if (memory.find(n) != memory.end()) {
        return memory[n];
    }
    int res = -1;
    // 计算当前结果
    for (int i = 2; i <= n; i++) {
        res = max(res, i*max((n-i), lc343_processv2(n-i, memory)));
    }
    // 记录
    memory[n] = res;
    return res;
}
// lc343 动态规划解法
int lc343_processv3(int n) {
    if (n == 2) return 1;

    vector<int> dp(n+1, 0);
    dp[1] = 1;
    // dp[2] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i] = max(dp[i], i*max((i-j), lc343_processv3(i-j)));
        }
    }
    return dp[n];
}
//给定一个正整数，将其至少拆分成两个正整数的和，并使这些整数的乘积最大化，返回最大乘积
int Lcalg::lc343(int n) {
    return lc343_process(n);
}


int main() {
    vector<vector<int> > dungeon = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
    Lcalg l;
    int res = l.lc174(dungeon);
    cout << res << endl;
    return 0;
}