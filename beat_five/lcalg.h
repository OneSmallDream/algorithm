#ifndef LCALG_H
#define LCALG_H

# include <string>
# include <vector>
using namespace std;

class Lcalg {

public:
    Lcalg() {}
    // 给定一个正整数，返回它在 Excel 表中相对应的列名称。
    // 1 -> A
    // 2 -> B
    // 3 -> C
    // ...
    // 26 -> Z
    // 27 -> AA
    // 28 -> AB 
    string lc168(int n);
    // 峰值元素是指其值大于左右相邻值的元素。
    // 给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。
    // 数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。
    // 你可以假设 nums[-1] = nums[n] = -∞。
    int lc162(vector<int>& nums);
    // 假设按照升序排序的数组在预先未知的某个点上进行了旋转。
    // (例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2])。
    // 请找出其中最小的元素。
    // 你可以假设数组中不存在重复元素。
    int lc153(vector<int>& nums);
    // 相对与lc153, lc154增加了元素可能重复的条件
    int lc154(vector<int>& nums);
};

#endif
