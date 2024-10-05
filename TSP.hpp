#ifndef TSP_HPP
#define TSP_HPP
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class TSP {

    public:
        pair<vector<int>, int> random(vector<vector<int>> matrix);
        pair<vector<int>, int> nn(vector<vector<int>> matrix);
        pair<vector<int>, int> brute_force(vector<vector<int>> matrix);

    private:
        int calculate_path_length(vector<vector<int>> matrix, vector<int> path);
};

#endif