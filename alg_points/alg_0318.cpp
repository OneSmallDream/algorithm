# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
# include <cstdio>
# include <queue>
# include <stack>
# include "algpoints.h"

using namespace std;

// 检查是否是二叉搜索树
int last_point = INT_MIN;
bool checkBST(TreeNode* root) {

    if (!checkBST(root->left)) return false;

    if (last_point != INT_MIN && root->val >= last_point) return false;
    last_point = root->val;

    if (!checkBST(root->right)) return false;
    
    return true;
}

struct TreeNodeWithFather {
    TreeNodeWithFather* left;
    TreeNodeWithFather* right;
    TreeNodeWithFather* father;
    int val;
};
// 二叉树 后继节点
// 1. 当前节点如果有右子树，它的后继节点为右子树中最左边的节点
// 2. 当前节点如果没有右子树
//    a. 如果当前节点n的父节点q，n是q的左子树，那么q就是n的后继节点
//    b. 如果n是q的右子树，从q往上访问，直到找到q是其父节点的左节点x，则后继节点为x; 如果找不到, 那么n就是整颗
//    树的最右侧的点，其后继节点为NULL。
TreeNodeWithFather* leftMostTree(TreeNodeWithFather* root) {
    if (!root) return root;
    
    while (root->left) {
        root = root->left;
    }

    return root;
}

TreeNodeWithFather* inorderSuc(TreeNodeWithFather* node) {
    if (!node) return node;

    if (node->right) {
        return leftMostTree(node->right);
    }else {
        while (node->father && node->father->right == node) {
            node = node->father;
        }
        if (!node->father) return NULL;
        else {
            return node->father;
        }
    }
}
// 编译顺序。给你一系列项目，和一系列依赖关系(依赖关系dependencies为一个链表，其中每个元素为两个项目的编组，且第二个项目依赖于第一个项目)
// 所有项目的依赖项必须在该项目被编译前编译, 请找出可以使得所有项目顺利编译的顺序。如果没有合法的编译顺序，返回错误。
// 例如，输入: projects: a, b, c, d, e, f ; dependencies: (a,d),(f,b),(b,d),(f,a),(d,c)
class Project {
    private:
        vector<Project> children;
        unordered_map<string, Project> m;
        string name;
        int dependencies = 0;
    public:
        Project(string n) {
            this->name = n;
        }
        void addNeighbors(Project& node) {
            if (m.find(node.getName()) == m.end()) {
                children.push_back(node);
                m[node.getName()] = node;
                node.incrementDependencies();
            }
        }

        string getName() {return this->name;}
        void incrementDependencies() {this->dependencies++;}
        void decrementDependencies() {this->dependencies--;}
        vector<Project> getChildren() {return this->children;}
        int getNumDendencies() {return this->dependencies;}
};

class Graph {
private:  
    vector<Project> nodes;
    unordered_map<string, Project> m;
public:
    Project createAndAddNode(string name) {
        if (m.find(name) != m.end()) {
            Project curNode(name);
            nodes.push_back(curNode);
            m[name] = curNode;
        }
        return m[name];
    }
    void addEdge(string srcName, string dstName) {
        m[srcName].addNeighbors(m[dstName]);
    }

    vector<Project> getNodes() {return nodes;}
};

Graph buildGraph(vector<string> projects, vector<pair<string, string>> dependencies) {

    Graph graph;
    // 1. 往图中增加节点
    for (int i=0; i<projects.size(); i++) {
        graph.createAndAddNode(projects[i]);
    }
    // 2. 为图中节点增加依赖关系
    for (int i=0; i<dependencies.size(); i++) {
        graph.addEdge(dependencies[i].first, dependencies[i].second);
    }
    return graph;
}

int addNonDependent(vector<pair<Project, int> >& order, vector<Project> projects, int offset) {
    
    for (int i=0; i<projects.size(); i++) {
        Project project = projects[i];
        if (project.getNumDendencies() == 0) {
            order[offset] = make_pair(project, 1);
            offset++;
        }
    }
    return offset;
}

vector<Project> getOrderedCompileProjects(vector<Project>& projects) {
    vector<pair<Project, int> > order;
    for (int i = 0; i < projects.size(); i++) {
        order.push_back(make_pair(projects[i], 0));
    }

    // 找到第一个无依赖节点
    int endOfList = addNonDependent(order, projects, 0);

    int toBeProcessed = 0;
    while (toBeProcessed < order.size()) {
        Project current = order[toBeProcessed].first;
        int valid = order[toBeProcessed].second;
        if (valid == 0) return vector<Project>();

        vector<Project> children = current.getChildren();
        for (int i=0; i<children.size(); i++) {
            children[i].decrementDependencies();
        }

        endOfList = addNonDependent(order, projects, endOfList);
        toBeProcessed++;
    }
    return order;
} 

