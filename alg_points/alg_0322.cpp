# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
# include <cstdio>
# include <queue>
# include <stack>
# include "algpoints.h"

using namespace std;

// 首个共同祖先，不得将其他的节点存储在另外的数据结构中。注意：这不一定是一颗二叉搜索树
// 1. 如果这是二叉搜索树？那么需要找出第一个节点，该节点的值大于node1, 且小于node2(如果node1的值小于node2的值)
// 从根节点开始，由上到下，第一个满足以上条件的节点，即为公共祖先。假设A为公共祖先，A为其父节点的左子树或右子树，
// 所以在A以上的节点，均不会满足，
TreeNode* findFirstCommonAncestor(TreeNode* root, TreeNode* node1, TreeNode* node2) {
    // 这里结束条件很重要
    if (!root || root==node1 || root==node2) return root;
    if (root->val > node1->val && root->val > node2->val) {
        return findFirstCommonAncestor(root->left, node1, node2);
    }else if (root->val < node1->val && root->val<node2->val) {
        return findFirstCommonAncestor(root->right, node1, node2);
    }else {
        return root;
    }
}

// 如果该二叉树不是搜索二叉树
// 首先，从上到下，两个节点，肯定均在某节点的左侧或者右侧，如果在两侧，那么此时则满足条件，该节点为公共祖先

bool checkDirection(TreeNode* root, TreeNode* p) {
    if (!root) {
        return false; 
    }
    if (root == p) {
        return true;
    }
    
    return checkDirection(root->left, p) || checkDirection(root->right, p);
}

TreeNode* findFirstCommonAncestorV2(TreeNode* root, TreeNode* p, TreeNode* q) {

    // 1. 检测当前p, q在root的左侧还是右侧
    // 2. 判断如果不在同一侧，则返回当前节点root
    // 3. 如果在同一侧，则向那一侧搜索结果
    // 分析:
    // 时间复杂度: 假设树的节点数为n， 第一次搜索要遍历n个节点确定p或q在左侧还是右侧, 
    // 如果是=平衡树，那么第二次要(n/2)，第三次要(n/4).....经过m次（树的高度-1)

    if (!root || root==p || root==q) {
        return root;
    }

    bool pIsOnLeft = checkDirection(root, p);
    bool qIsOnLeft = checkDirection(root, q);
    
    if (pIsOnLeft != qIsOnLeft) {
        return root;
    }
    
    TreeNode* child = (pIsOnLeft ? root->left : root->right);
    return findFirstCommonAncestorV2(child, p, q);
}

// 在搜索p 和 q的时候进行求解，如果左子树和右子树分别有p和q，那么当前结果便是答案
// 公共祖先有三种情况: 1. 不等于q且不等于q;
//                  2. 等于p或q其中之一(即p是q的子树或者q是p的子树,或者p==NULL||q==NULL);
//                  3. 不存在公共祖先(此时p和q不在同一颗树中)
// 首先 忽略第三种情况; 只需要考虑前两种情况, 在遍历树查找p, q的过程中，搜索答案。
// 该方法改进类似与 “平衡树” 的改进方法: 在搜索左子树和右子树的高度时，如果不符合条件，返回非法的标记，同时在递归函数
// 后增加判断，判断是否非法。如果合法，那么就返回当前节点的高度。
// 这道题也是，在V2版本中，针对每个节点都要搜索一遍p和q处于当前节点的左侧还是右侧。而V3的改进版，则是在搜索p, q
// 的过程中，如果发现结果，则返回结果，在每个递归函数后，判断如果当前返回为标记的结果时，那么直接返回，不再搜索。
TreeNode* findFirstCommonAncestorV3(TreeNode* root, TreeNode* p, TreeNode* q) {
    
    if (root==NULL) return root;
    // 如果节点p和节点q相同，且遍历到root时发现，则直接返回root
    if (root==p && root==q) return root;

    TreeNode* x = findFirstCommonAncestorV3(root->left, p, q);
    if (x != NULL && x != p && x != q) {
        return x; // 已经找到祖先, 直接返回;
    }

    TreeNode* y = findFirstCommonAncestorV3(root->right, p, q);
    if (y != NULL && y != p && y != q) {
        return y; // 已经找到祖先, 直接返回;
    }

    // 将第一种祖先情况作为第一优先级返回。
    if (x != NULL && y != NULL) {
        return root;
    // 该条件可以覆盖两种情况: 1. 当前节点便是p(或q), 但是子树中没有q(或p)
    //                     2. 当前节点便是p(或q), 但是子树中含有q(或p)
    }else if(root==p || root==q) {
        return root;
    // 如果有非空值，该条件返回非空。
    }else {
        return x==NULL?y:x;
    }
}