# include <string>
# include <iostream>
# include <stack>
# include <unordered_map>
# include "lcalg.h"

using namespace std;

int getDotNum(string v) {
    int res = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == '.') {
            res++;
        }
    }
    return res;
}
string make_up(string v, int length) {
    for (int i = 0; i < length; i++) {
        v += ".";
        v += ".";
    }

    return v;
}

int compare_single(string v1, string v2) {
    int i = 0, j = 0;
    while(i < v1.size() && v1[i] == '0') {
        i++;
    } 
    while(j < v2.size() && v2[j] == '0') {
        j++;
    }
    
    if (i == v1.size() && j == v2.size()) return 0;
    else if (i == v1.size() && j != v2.size()) return -1;
    else if (i != v1.size() && j == v2.size()) return 1;
    else {
        int ver1 = atoi(v1.substr(i, v1.size()-i).c_str());
        int ver2 = atoi(v2.substr(j, v2.size()-j).c_str());
        if (ver1 == ver2) return 0;
        else if (ver1 > ver2) return 1;
        else return -1;
    }
}

int compare_full(string v1, string v2) {
    // 比较两点之间的数字
    int prev1 = 0;
    int cur1 = 0;
    int prev2 = 0;
    int cur2 = 0;
    while (cur1 < v1.size() && cur2 < v2.size()) {
        //获取v1两点间字符串
        while (cur1 < v1.size() && v1[cur1] != '.') {
            cur1++;
        }
        string cur_version1 = v1.substr(prev1, cur1-prev1);
        cur1++;
        prev1 = cur1;

        // 获取v2两点间字符串
        while (cur2 < v2.size() && v2[cur2] != '.') {
            cur2++;
        }
        string cur_version2 = v2.substr(prev2, cur2-prev2);
        cur2++;
        prev2 = cur2;

        int comp_flag = compare_single(cur_version1, cur_version2);
        if (comp_flag != 0) {
            return comp_flag;
        }
    }
    return 0;
}
int Lcalg::lc165(string version1, string version2) {
    int numDotv1 = getDotNum(version1);
    int numDotv2 = getDotNum(version2);
    if (numDotv1 > numDotv2) {
        version2 = make_up(version2, numDotv1-numDotv2);
    }else if (numDotv1 < numDotv2) {
        version1 = make_up(version1, numDotv2-numDotv1);
    }
    int res = compare_full(version1, version2);
    return res;
}

int Lcalg::lc171(string s) {
    // 跟lc168是相反的，进制相关
    if (s.size() == 0) return -1;

    int res = 0;
    int i = s.size()-1;
    while (i >= 0) {

        int cur_pow = (s.size()-1-i);
        int left_part = (char)(s[i] - 'A' + 1);
        res += left_part * pow(26, cur_pow);
        i--;

    }
    return res;
}

int main() {
    return 0;
}