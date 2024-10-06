#ifndef TSP_HPP
#define TSP_HPP
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class TSP {

    public:
        pair<vector<int>, int> random(const vector<vector<int>>& matrix, int iterations, vector<chrono::duration<double, milli>> &times);
        pair<vector<int>, int> nn(vector<vector<int>> matrix, vector<chrono::duration<double, milli>> &times);
        pair<vector<int>, int> brute_force(const vector<vector<int>>& matrix, vector<chrono::duration<double, milli>> &times);

    private:
        int calculate_path_length(vector<vector<int>> matrix, vector<int> path);
};

#endif