# include <string>
# include <iostream>
# include <stack>
# include <unordered_map>
# include "lcalg.h"

using namespace std;

void rev(string& s, int start, int end) {
    int i = start;
    int j = end;
    while(j > i) {
        swap(s[i++], s[j--]);
    }
}

string Lcalg::lc151(string s) {
    // 如果字符串为空
    if (s.size() == 0) {
        return s;
    }

    // 去掉两边空格
    int i = 0;
    while(s[i] == ' '){
        i++;
    }
    // 如果字符串全部为空格
    if (i == s.size()) return "";

    int start = i;
    int j = s.size()-1;
    while(s[j] == ' ') {
        j--;
    }
    int end = j+1;

    //设置两个指针, 一个指向整体字符串起始，另一个指向有效字符串的起始
    i = 0;
    j = start;
    while(j < end) {
        if (j+1<end && s[j]==' ' && s[j+1]==' ') {
            j++;
            continue;
        }
        s[i++] = s[j++];
    }
    
    // 翻转0到i, 因为排除了全部空格情况，所以i-1>0
    rev(s, 0, i-1);
    // 以空格为分隔符, 翻转内部单词
    int prev = 0;
    int cur = 0;
    for ( ; cur < i; cur++) {
        if (s[cur] == ' ') {
            // 处理空格
            rev(s, prev, cur-1);
            prev = cur + 1;
        }
    }
    if (cur > prev) {
        // 处理最后一个需要翻转的子串
        rev(s, prev, cur-1);
    }
    return s.substr(0, i);
}

// lc155 -- 数据栈与辅助栈同步
class MinStack {
public:
    stack<int> data;
    stack<int> helper;
    /** initialize your data structure here. */
    MinStack() {
    }
    void push(int x) {
        data.push(x);
        if (helper.size()==0 || x < helper.top()) {
            helper.push(x);
        }else {
            helper.push(helper.top());
        }
    }
    void pop() {
        if (data.size() > 0) {
            data.pop();
            helper.pop();
        }
    }
    int top() {
        return data.top();
    }
    
    int getMin() {
        return helper.top();
    }
};

string Lcalg::lc166(int numerator, int denominator) {
    // 溢出报错，类型需要转换为long long
    string res = "";
    long long num = static_cast<long long> (numerator);
    long long denom = static_cast<long long> (denominator);
    if (num < 0 && denom > 0 || num > 0 && denom < 0) {
        res += "-";
    }
    num = abs(num);
    denom = abs(denom);
    //整数部分
    string front_part = to_string(num / denom);
    res += front_part;
    // 如果余数为0，整除
    long long rem = num%denom;
    if (rem == 0) return res;
    // 否则,处理小数部分
    res += ".";
    int index = res.size();
    unordered_map<int, int> dic;
    unordered_map<int, int> rec;
    while (rem && dic.count(rem) == 0) {
        // 记忆该余数出现过
        dic[rem] = 1;
        // 记录第一次出现的位置
        rec[rem] = index++;
        // 计算当前结果
        string add_res = to_string(rem*10/denom);
        res += add_res;
        rem = rem*10%denom;
        if (rem == 0) {
            return res;
        }
    }
    if (dic.count(rem) == 1) {
        // 在第一次出现的位置增加左括号
        int pos = rec[rem];
        res.insert(pos, "(");
        res += ")";
    }
    return res;
}

int main(int argc, const char * argv[]) {
    string a = "12";
    if (a[0] != '1') {
        return 0;
    }
}
