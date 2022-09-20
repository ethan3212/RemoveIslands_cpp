#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> getNeighbors(vector<vector<int>> &matrix, vector<vector<bool>> &connectedToBorder, int row, int col) {
    vector<vector<int>> neighbors = {};
    if(row > 0 && matrix[row - 1][col] == 1 && !connectedToBorder[row - 1][col]) {
        neighbors.push_back(vector<int> {row - 1, col});
    }
    if(row < matrix.size() - 1 && matrix[row + 1][col] == 1 && !connectedToBorder[row + 1][col]) {
        neighbors.push_back(vector<int> {row + 1, col});
    }
    if(col > 0 && matrix[row][col - 1] == 1 && !connectedToBorder[row][col - 1]) {
        neighbors.push_back(vector<int> {row, col - 1});
    }
    if(col < matrix[0].size() - 1 && matrix[row][col + 1] == 1 && !connectedToBorder[row][col + 1]) {
        neighbors.push_back(vector<int> {row, col + 1});
    }
    return neighbors;
}

void dfs(vector<vector<int>> &matrix, vector<vector<bool>> &connectedToBorder, int row, int col) {
    vector<vector<int>> stack = {{row, col}};
    while(!stack.empty()) {
        vector<int> current = stack.back();
        stack.pop_back();
        row = current[0];
        col = current[1];
        if(connectedToBorder[row][col]) {
            continue;
        }
        connectedToBorder[row][col] = true;
        if(matrix[row][col] != 1) {
            continue;
        }
        vector<vector<int>> neighbors = getNeighbors(matrix, connectedToBorder, row, col);
        for(const auto& neighbor : neighbors) {
            stack.push_back(neighbor);
        }
    }
}

vector<vector<int>> removeIslands(vector<vector<int>> matrix) {
    vector<vector<bool>> connectedToBorder;
    for(int i = 0; i < matrix.size(); i++) {
        connectedToBorder.emplace_back(matrix[0].size(), false);
    }
    for(int col = 0; col < matrix.size(); col++) {
        if(matrix[0][col] == 1) {
            dfs(matrix, connectedToBorder, 0, col);
        }
        if(matrix[matrix.size() - 1][col] == 1) {
            dfs(matrix, connectedToBorder, (int)matrix.size() - 1, col);
        }
    }
    for(int row = 0; row < matrix[0].size(); row++) {
        if(matrix[row][0] == 1) {
            dfs(matrix, connectedToBorder, row, 0);
        }
        if(matrix[row][matrix[0].size() - 1] == 1) {
            dfs(matrix, connectedToBorder, row, (int)matrix[0].size() - 1);
        }
    }
    for(int row = 0; row < matrix.size(); row++) {
        for(int col = 0; col < matrix[0].size(); col++) {
            if(!connectedToBorder[row][col] && matrix[row][col] == 1) {
                matrix[row][col] = 0;
            }
        }
    }
    return matrix;
}

int main() {
    vector<vector<int>> input = {
            {1, 0, 1, 1, 1, 0},
            {1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0, 1}
    };
    for(const auto& row : input) {
        for(auto element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    cout << endl;
    vector<vector<int>> output = removeIslands(input);
    for(const auto& row : output) {
        for(auto element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    return 0;
}
