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

int Lcalg::lc162(vector<int>& nums) {
        
    int right = nums.size()-1;
    int left = 0;
    //先确定两个边界, 确保两个边界
    if (nums.size() == 1) {
        return 0;
    }
    if (nums[0] > nums[1]) {
        return 0;
    }
    if (nums[nums.size()-1] > nums[nums.size()-2]) {
        return nums.size()-1;
    }
    // 二分查找
    while (right > left) {
        int mid = left + (right - left) / 2;
        if (mid == 0 || mid == nums.size()-1) {
            return -1;
        }
        // 不满足条件
        if (nums[mid] > nums[mid+1] && nums[mid] < nums[mid-1]) {
            // 当前在下坡的时候
            right = mid;
        }else if (nums[mid] < nums[mid+1] && nums[mid] > nums[mid-1]) {
            // 当前在上坡的时候
            left = mid;
        }else if (nums[mid] < nums[mid+1] && nums[mid] < nums[mid-1]) {
            // 当前在谷底的时候, 向左向右均可
            left = mid;
        }else{
            return mid;
        }
    }

    return ((left==right)&&nums[left]>nums[left-1]&&nums[left]<nums[left+1])?left:-1;
}

int Lcalg::lc153(vector<int>& nums) {

    if (nums.size() == 1) return nums[0];
    // 旋转点在边界，即没进行旋转
    if (nums[0] < nums[nums.size()-1]) {
        return nums[0];
    }
    int left = 0;
    int right = nums.size()-1;
    
    // 二分
    while(right-left > 1) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[nums.size()-1]) {
            left = mid;
        }else if (nums[mid] < nums[0]) {
            right = mid;
        } 
    }

    return nums[left] > nums[right] ? nums[right] : -1;
} 

int Lcalg::lc154(vector<int>& nums){
    if (nums.size() == 1) return nums[0];

    int left = 0;
    int right = nums.size()-1;
    
    while (right > left) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        }else if (nums[mid] < nums[right]) {
            right = mid;
        }else {
            // 关键点
            right--;
        }
    }

    return nums[left];
}

int main(int argc, const char * argv[]) {
    string a = "hello world!";
    cout << a.substr(1, 3) << endl;
    return 0;
}
