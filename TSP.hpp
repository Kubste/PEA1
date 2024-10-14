#ifndef TSP_HPP
#define TSP_HPP
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <cmath>

using namespace std;

class TSP {

    public:
        pair<vector<int>, int> random(const vector<vector<int>>& matrix, int minutes, chrono::duration<double, micro> &time, int progress_indicator);
        pair<vector<int>, int> nn(vector<vector<int>> matrix, chrono::duration<double, micro> &time, int progress_indicator);
        pair<vector<int>, int> brute_force(const vector<vector<int>>& matrix, int minutes, chrono::duration<double, micro> &time, int progress_indicator);
        void explore_paths(vector<int> path, int path_length, vector<int> Q, chrono::duration<double, micro> &time, int current_node, int start_node,
                            pair<vector<int>, int> &results, vector<vector<int>> matrix);

    private:
        int calculate_path_length(vector<vector<int>> matrix, vector<int> path);
};

#endif