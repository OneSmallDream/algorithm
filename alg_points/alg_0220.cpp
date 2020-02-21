# include <iostream>
# include <vector>
# include <stack>
# include "algpoints.h"

using namespace std;



// 今天晚上闲来无事，突然想起来当初说要每天刷5道题，每周看两篇论文的誓言
// 由于工作比较忙（lan）不小心忘记了，今天开始要重新捡起这个习惯，保持每天刷题，每周看论文的习惯，保持竞争力！！
// 话不多说, 开始分析题目吧 -- 20200210 10:08

// “二叉搜索树转双向链表”道题目放在了重点的章节，因为这道题是一道非常基础且善于被考察的，结合了二叉树，链表，递归等三大基础问题，非常重要！
// (曾经有个室友面试头条的时候就挂在了这道题上) 要求不能创建新的节点，只能调整树中节点指针的指向。
// 对于二叉树的中序遍历递归版本
void convertNode(TreeNode* node, TreeNode** recordLastNode) {
    // 该递归函数包含两个入参
    // 当前处理的节点node 和 上一次处理后指向最后一个节点的指针（指向指针的指针）
    if (!node) {
        // 如果当前节点为空, 不做处理直接返回
        return ;
    }
    // 先copy一份当前节点
    TreeNode* curNode = node;
    
    // 开始递归版本的中序遍历, 中序遍历的顺序是对于二叉搜索树，从小到大进行依次遍历
    if (curNode -> left) {
        convertNode(curNode->left, recordLastNode);
    }

    // 上面的递归已经将该节点的左子树全部处理完成, 现在处理当前节点
    curNode->left = *recordLastNode;
    if (*recordLastNode) {
        // 这里一定要加上括号
        (*recordLastNode)->right = curNode;
    }
    *recordLastNode = curNode;

    if (curNode -> right) {
        convertNode(curNode->right, recordLastNode);
    }

}
TreeNode* Algpoints::convert(TreeNode* root) {
    
    TreeNode* nodeOfLast = NULL;
    convertNode(root, &nodeOfLast);
    TreeNode* pHead = nodeOfLast;
    while (pHead && pHead->left) {
        pHead = pHead->left;
    }
    return pHead;
}



int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    TreeNode* cur = root -> left;
    cur->left = new TreeNode(2);
    cur->right = new TreeNode(4);
    Algpoints a;
    TreeNode* start = a.convert(root);
    while (start) {
        cout << start->val << " ";
        start = start->right;
    }
    cout << endl;
    return 0;
}