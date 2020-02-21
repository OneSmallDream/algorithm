# include <iostream>
# include <vector>
# include <stack>
# include "algpoints.h"

using namespace std;

vector<int> Algpoints::inorderTraveral(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> st;
    // 用于遍历的指针
    TreeNode* cur = root;
    // 当栈不空或者指针不空的时候，循环
    while(!st.empty() || cur) {
        // 填数据, 保证当前和左子树不为空, 如果左子树为空, 需要调整到右子树
        if (cur && cur->left) {
            st.push(cur);
            cur = cur->left;
            continue;
        }

        // 当前指针为空(上一次)
        if (!cur) {
            if (!st.empty()) {
                // 恢复数据
                cur = st.top();
                st.pop();
            }else break;
        }

        // 弹出的数据 或 当前数据（此时左子树为空）
        result.push_back(cur->val);
        cur = cur -> right;
    }
    return result;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    TreeNode* cur = root -> left;
    cur->left = new TreeNode(4);
    cur->right = new TreeNode(5);
    Algpoints a;
    vector<int> res = a.inorderTraveral(root);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}