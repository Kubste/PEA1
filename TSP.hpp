#ifndef TSP_HPP
#define TSP_HPP
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>

using namespace std;

class TSP {

    public:
        pair<vector<int>, int> random(const vector<vector<int>>& matrix, int iterations, vector<chrono::duration<double, milli>> &times, int progress_indicator);
        pair<vector<int>, int> nn(vector<vector<int>> matrix, vector<chrono::duration<double, milli>> &times, int progress_indicator);
        pair<vector<int>, int> brute_force(const vector<vector<int>>& matrix, vector<chrono::duration<double, milli>> &times, int progress_indicator);

    private:
        int calculate_path_length(vector<vector<int>> matrix, vector<int> path);
};

#endif