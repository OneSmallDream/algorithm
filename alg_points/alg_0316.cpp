# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
# include <cstdio>
# include <queue>
# include <stack>
# include "algpoints.h"

using namespace std;

TreeNode* create(vector<int> nums, int start, int end) {
    
    if (end < start) return NULL;
    int mid = start + (end-start)/2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = create(nums, 0, mid-1);
    root->right = create(nums, mid+1, end);
    return root;
}

// 最小高度树,给定一个有序整数数组，元素各不相同，且按升序排列，创建一颗高度最小的二叉搜索树
TreeNode* createMinHeightTree(vector<int> nums) {
    
    return create(nums, 0, nums.size()-1);
}


// 特定深度节点链表，给定一颗二叉树，设计算法，创建含有某一深度上所有节点的链表
// 也就是层次遍历
struct Node {
    TreeNode* treeNode;
    Node* next;
    Node(TreeNode* t, Node* n) {
        treeNode = t;
        next = n;
    }
};

vector<Node*> createLevelLinkList(TreeNode* root) {

    queue<TreeNode*> que;
    que.push(root);
    vector<Node*> res;
    while (!que.empty()) {

        // 当前层节点个数
        int size = que.size();
        Node* node = new Node(NULL, NULL);
        Node* root = node;
        for (int i = 0; i < size; i++) {
            TreeNode* cur = que.front();
            que.pop();
            node->next = new Node(cur, NULL);
            node = node->next;
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
        }

        res.push_back(root->next);
    }
    return res;
}

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(7);
    TreeNode* left = root->left;
    left->left = new TreeNode(2);
    left->right = new TreeNode(4);
    TreeNode* right = root->right;
    right->left = new TreeNode(6);
    right->right = new TreeNode(8);
    vector<Node*> res = createLevelLinkList(root);
    for(int i = 0 ; i < res.size(); i++) {
        Node* cur = res[i];
        while (cur) {
            cout << cur->treeNode->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    cout << "end" << endl;
}
