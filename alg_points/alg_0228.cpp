# include <iostream>
# include <vector>

using namespace std;

// 最大黑方阵
// 题目是给定一个方阵，其中每个单元非黑即白，找出4条边结尾黑色像素的最大方阵
// 这道题的优化方法还是利用空间换时间， 首先最朴素的解法如下
struct Subsquare {
    int row;
    int col;
    int size;
    Subsquare(int r, int c, int s): row(r), col(c), size(s){}
};

bool isValidSubsquare(vector<vector<int> > matrix, int row, int col, int subSize) {
    // 检查上下边界是否均为黑(0)
    for (int j = 0; j < subSize; j++) {
        if (matrix[row][col+j] == 1) {
            return false;
        }
        if (matrix[row+subSize-1][col+j] == 1) {
            return false;
        }
    }
    return true;
}

bool isValidSubsquareV2(vector<vector<pair<int, int> > > processed_matrix, int row, int col, int subSize) {
    
    pair<int, int> topLeft = processed_matrix[row][col];
    pair<int, int> downLeft = processed_matrix[row+subSize-1][col];
    pair<int, int> topRight = processed_matrix[row][col+subSize-1];

    if (topLeft.first < subSize || topLeft.second < subSize || downLeft.first < subSize || topRight.second < subSize) {
        return false;
    }
    return true;

}

Subsquare findSubsquare(vector<vector<int> > matrix, int subSize) {
    int size = matrix.size();
    int count = size - subSize + 1;
    for (int row = 0; row < count; row++) {
        for (int col = 0; col < count; col++) {
            if (isValidSubsquare(matrix, row, col, subSize)) {
                return Subsquare(row, col, subSize);
            }
        }
    }
    return Subsquare(-1, -1, -1);
}

Subsquare findMaxBlackSubsquare(vector<vector<int> > matrix) {
    int size = matrix.size();
    for (int i = size; i >= 1; i--) {
        Subsquare square = findSubsquare(matrix, i);
        if (square.size != -1) return square;
    }
    return Subsquare(-1, -1, -1);
}

vector<vector<pair<int, int> > > process(vector<vector<int> > matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return ;
    }
    int row_size = matrix.size();
    int col_size = matrix[0].size();
    vector<vector<pair<int, int> > > processed_matrix(row_size, vector<pair<int, int> >(col_size));
    
    for (int row = row_size-1; row >= 0; row--) {
        for (int col = col_size-1; col < col_size; col++) {
            int blackRight = 0;
            int blackDown = 0;
            // 只针对黑像素进行处理
            if (matrix[row][col] == 0) {
                blackRight++;
                blackDown++;
                // 累加右侧点信息
                if (col+1<col_size) {
                    blackRight += processed_matrix[row][col+1].first;
                }
                // 累加下侧点信息
                if (row+1 <row_size) {
                    blackDown += processed_matrix[row+1][col].second;
                }
            }
            // 对矩阵当前位置赋值
            processed_matrix[row][col] = make_pair(blackRight, blackDown);

        }
    }
    return processed_matrix;
}

// 最外层遍历边长O(N)，内层遍历矩阵左上侧点O(N^2), 最内层遍历O(N), 总时间复杂度O(N^4)
// 优化方法，利用空间换取时间，最原始矩阵进行预处理，使得判断是否有效的过程从O(N) -> O(1)
Subsquare findMaxBlackSubsquare_v2(vector<vector<int> > matrix) {
    // 1. 对原始矩阵进行预处理
    // 2. 针对边长由大到小遍历，找有效方阵
    int size = matrix.size();
    vector<vector<pair<int, int> > > processed_matrix = process(matrix);

    for (int i = size; i >= 1; i--) {
        // 逻辑相同
        // 判断方阵有无效的方法为 isValidSubsquareV2
    }
    
}