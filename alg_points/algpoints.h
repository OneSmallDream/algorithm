# ifndef ALGPOINTS_H
# define ALGPOINTS_H

# include <vector>
# include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Subsquare {
    int row;
    int col;
    int size;
    Subsquare(int r, int c, int s): row(r), col(c), size(s){}
};

class Algpoints {
    
public:
    // 基数排序
    void radix_sort(vector<int>& arr);
    // 中序遍历--非递归--0131
    vector<int> inorderTraveral(TreeNode* root);
    // 二叉树转按照中序遍历的顺序转换成双向链表
    TreeNode* convert(TreeNode* root);
    // 全排列
    void Permutation(char* pStr);
    // 子集
    vector<vector<int> > subsets(vector<int>& nums);
    // todo 数据流的中位数
    // 最大黑边方阵
    Subsquare findMaxBlackSubsquare(vector<vector<int> > matrix);
    // 单调栈 （重要概念）
    // 关于单调栈，单调栈用于解决在一个数组中对于每一个位置都找到左边离他最近的比他大的（或者小的）和右边离他最近的比他大的（或者小的）。 假设找两边的小的值，
    // 栈内存放的是值得index，从栈底到栈顶，index对应得值是从小到大的
    unordered_map<int, pair<int, int> > getNearLessNoRepeat(vector<int> nums);
    unordered_map<int, pair<int, int> > getNearLessWithRepeat(vector<int> nums);
    // todo 最大全1方阵 或者矩阵
    int maxRectangle(vector<vector<int> > nums);
    
};


# endif