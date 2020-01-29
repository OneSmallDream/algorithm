# include <string>
# include <iostream>
# include "lcalg.h"

using namespace std;


string Lcalg::lc168(int n) {
    
    string res;
    
    while (n > 0) {
        int tmp = n % 26;
        if (tmp == 0) {
            tmp = 26;
            n--;
        }
        res = (char)('A' + tmp - 1) + res;
        n = n / 26;
    }
    
    return res;
} 

int main(int argc, const char * argv[]) {
    int n = 702;
    Lcalg lc;
    string res = lc.lc168(n);
    cout << "输入: " << n << "  输出: " << res << endl;
    return 0;
}
