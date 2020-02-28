# ifndef ALGPOINTS_H
# define ALGPOINTS_H

# include <vector>

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
    // todo 最大全1方阵
    
};


# endif