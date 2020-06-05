package algorithm;

public class three_steps {
    /*
    有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶，2阶或3阶。实现一种方法，计算小孩有多少种上楼梯的方式
     */
    int countWaysRecur(int n) {
        if (n <= 0) return 0;
        return countWaysRecur(n-1) + countWaysRecur(n-2) + countWaysRecur(n-3);
    }

    /*
    注意溢出问题
     */
    int countWaysMemo(int n, int[] memo) {
        memo[n] = countWaysMemo(n-1, memo) + countWaysMemo(n-2, memo) + countWaysMemo(n-3, memo);
        return memo[n];
    }
}
