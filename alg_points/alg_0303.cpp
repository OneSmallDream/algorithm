# include <iostream>
# include <vector>
# include <stack>
# include <unordered_map>
#include <cstdio>
# include "algpoints.h"

using namespace std;


vector<int> G[10000];
int color[10];
int V = 10;

bool color_dfs(int v, int c) {
    color[v] = c;
    for (int i = 0; i < G[v].size(); i++) {
        // 如果相邻点被染成相同颜色，则返回false
        if (color[G[v][i]] == c) return false;
        //否则,如果相邻点无染色, 那么染成-c
        if (color[G[v][i]] == 0 && !color_dfs(G[v][i], -c)) return false;
    }

    return true;
}

void check_color() {
    for (int i = 0; i < V; i++) {
        if (color[i] == 0) {
            if (!color_dfs(i, 1)) {
                cout << "no" << endl;
                return ;
            }
        }
    }
    cout << "yes" << endl;
}


// 输入 第一行是顶点个数n，颜色数m
// 接下来每行是顶点之间的相互关系 a b，表示a b相邻，当a, b均为0是输入结束
// 输出所有着色方案，表示某个顶点涂某种着色号，最后一行是着色方案总数
int planCount = 0;
int a = 1;
int b = 1;
int n, m;
vector<vector<int> > Graph;
vector<int> color_v2;

bool checkColorValid(int v, int c) {
    
    for (int i = 0; i < Graph.size(); i++) {
        if (G[v][i] == 1 && color[i] == c) return false;
    }
    return true;
}

void colorPlan(int v) {

    if (v > n) {
        planCount++;
        for (int i = 0; i < color_v2.size(); i++) {
            cout << color[i] << " ";
        }
        cout << endl;
    }else {
        for (int i = 1; i <= m; i++) {
            color[v] = i;
            if (checkColorValid(v, i)) {
                colorPlan(v+1);
            }
            color[v] = 0;
        }
    }


}

void calcColorPlan() {
    scanf("%d %d", &n, &m);
    while(scanf("%d %d", &a, &b)!=EOF && a!=0 && b!=0) {
        Graph[a][b] = 1;
        Graph[b][a] = 1;
    }
    colorPlan(1);
    cout << planCount << endl;
}


int main() {
    return 0;
}

