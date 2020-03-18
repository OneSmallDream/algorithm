# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
# include <cstdio>
# include <queue>
# include <stack>
# include "algpoints.h"

using namespace std;

// 节点间通路，给定有向图，找出两个节点之间是否有通路
// 利用广度优先遍历来搜索
bool search(vector<vector<int> > G, int start, int end) {

    if (start == end) return true;

    queue<int> que;
    que.push(start);
    // 记录
    int vNum = G.size();
    vector<int> visited(vNum);
    visited[start] = 1;
    while(!que.empty()) {
        int curV = que.front();
        que.pop();
        
        for (int i = 0; i < G[curV].size(); i++) {
            if (G[curV][i] == 1) {
                // 访问i节点
                if (visited[i] == 1) continue;
                if (i == end) return true;
                else {
                    visited[i] = 1;
                    que.push(i);
                }
            }
        }
    }
    return false;
}

vector<int> getAdjVertices(vector<vector<int> > G, int v) {
    vector<int> vSet = G[v];
    vector<int> ret;
    for (int i = 0; i < vSet.size(); i++) {
        if (vSet[i] == 1) {
            ret.push_back(i);
        }
    }
    return ret;
}

// 图的深度优先遍历非递归
void search_dfs_norecur(vector<vector<int> > G, int v) {
    
    stack<pair<int, vector<int> > > st;
    vector<int> visited(G.size());
    vector<int> dfs_seq;
    
    visited[v] = 1;
    pair<int, vector<int> > element = make_pair(0, getAdjVertices(G, v));
    st.push(element);

    while (!st.empty()) {
        
        pair<int, vector<int> > ele = st.top();
        st.pop();
        if (ele.first < ele.second.size()) {
            int curV = ele.second[ele.first];
            st.push(make_pair(ele.first+1, ele.second));
            // 如果当前点没有被访问过
            if (!visited[curV]) {
                dfs_seq.push_back(curV);
                visited[curV] = 1;
                st.push(make_pair(0, getAdjVertices(G, curV)));
            }
        }
    }
    
}

void search_dfs_recur(vector<vector<int> > G, int v, vector<int>& visited) {
    
    if (v < 0 || v >= G.size()) {
        return ;
    }

    for (int i = 0; i < G[v].size(); i++) {
        
        if (!visited[i] && G[v][i] == 1) {
            visited[i] = 1;
            search_dfs_recur(G, i, visited);
        }
    }
}

TreeNode* recurCreate(vector<int> nums, int start, int end) {
    if (end < start) return NULL;
    
    int mid = start + (end - start) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = recurCreate(nums, start, mid-1);
    root->right = recurCreate(nums, mid+1, end);
    return root;
}
// 最小高度树，给定一个有序整数数组，元素各不相同且按照升序排列，创建一颗高度最小的二叉搜索树
TreeNode* createMinHeightTree(vector<int> nums) {
    return recurCreate(nums, 0, nums.size()-1);
}

int getHeight(TreeNode* root) {
    
    if (root == NULL) return 0;

    if (root!=NULL && root->left==NULL && root->right==NULL) {
        return 1;
    }
    
    return max(getHeight(root->left), getHeight(root->right))+1;
}

// 检查平衡性, 任意一个节点，其两棵子树的高度差不超过1
bool checkBalance(TreeNode* root) {
    
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if (abs(leftHeight-rightHeight) > 1) {
        return false;
    }
    bool left = checkBalance(root->left);
    bool right = checkBalance(root->right);
    return left&&right;
}

bool checkBalanceV2(TreeNode* root) {
    if (root == NULL) return -1;
    int leftHeight = checkBalanceV2(root->left);
    if (leftHeight == INT_MIN) return INT_MIN;
    int rightHeight = checkBalanceV2(root->right);
    if (rightHeight == INT_MIN) return INT_MIN;

    int diff = abs(leftHeight-rightHeight);
    if (diff > 1) {
        return INT_MIN;
    }else {
        return max(leftHeight, rightHeight) + 1;
    }
}

int main() {
    return ;
}