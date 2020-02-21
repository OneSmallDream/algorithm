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

class Algpoints {
    
public:
    // 基数排序
    void radix_sort(vector<int>& arr);
    // 中序遍历--非递归--0131
    vector<int> inorderTraveral(TreeNode* root);
    // 二叉树转按照中序遍历的顺序转换成双向链表
    TreeNode* convert(TreeNode* root);
};


# endif