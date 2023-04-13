#include <iostream>
#include <queue>

using namespace std;

class Solution {
   public:
    static int orangesRotting(vector<vector<int>>& grid);
    static void matrix_print(vector<vector<int>>& grid, const char* message);
};

int main(void) {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    Solution::matrix_print(grid, "Input: ");

    int minuts = Solution::orangesRotting(grid);

    printf("Output: %d", minuts);

    return 0;
}

int Solution::orangesRotting(vector<vector<int>>& grid) {
    queue<pair<pair<int, int>, int>> rotten;
    int dir[] = {0, -1, 0, 1, 0};

    int fresh = 0;
    for (int i = 0; i < (int)grid.size(); i++)
        for (int j = 0; j < (int)grid[0].size(); j++)
            if (grid[i][j] == 2)
                rotten.push({{i, j}, 0});
            else if (grid[i][j] == 1)
                fresh++;

    if (fresh == 0) return 0;

    int res_minuts = -1;

    while (!rotten.empty()) {
        int i = rotten.front().first.first;
        int j = rotten.front().first.second;
        int minute = rotten.front().second;
        rotten.pop();

        for (int k = 0; k < 4; k++) {
            int near_i = i + dir[k], near_j = j + dir[k + 1];

            if (near_i >= 0 && near_i < (int)grid.size() && near_j >= 0 && near_j < (int)grid[0].size() &&
                grid[near_i][near_j] == 1) {
                rotten.push({{near_i, near_j}, minute + 1});
                if (res_minuts < minute + 1) res_minuts = minute + 1;
                grid[near_i][near_j] = 2;
                fresh--;
            }
        }
    }

    return fresh == 0 ? res_minuts : -1;
}

void Solution::matrix_print(vector<vector<int>>& grid, const char* message) {
    cout << message << endl;
    for (auto& row : grid) {
        for (auto& i : row) {
            cout << i << ' ';
        }
        cout << endl;
    }
}