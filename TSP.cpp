#include "TSP.hpp"
using namespace std;

pair<vector<int>, int> TSP::random(vector<vector<int>> matrix) {
    pair<vector<int>, int> results;
    vector<int> path;
    for(int i = 0; i < matrix.size(); i++) path.push_back(i);

    random_device random;
    mt19937 g(random());
    shuffle(path.begin(), path.end(), g);

    results.first = path;
    results.second = calculate_path_length(matrix, path);

    return results;
}

pair<vector<int>, int> TSP::nn(vector<vector<int>> matrix) {
    pair<vector<int>, int> results;
    vector<int> path;
    vector<int> Q;
    pair<int, int> min_edge;
    int current_node;

    for(int j = 0; j < matrix.size(); j++) {
        current_node = j;
        path.push_back(j);
        for(int i = 0; i < matrix.size(); i++) Q.push_back(i);
        Q.erase(remove(Q.begin(), Q.end(), j), Q.end());
        min_edge.second = INT_MAX;
        for(int k = 0; k < matrix.size() - 1; k++) {
            for(int i = 0; i < matrix.size(); i++) {
                if(matrix[i][current_node] < min_edge.second && matrix[i][current_node] != -1 && find(Q.begin(), Q.end(), i) != Q.end()) {
                    min_edge.second = matrix[i][current_node];
                    min_edge.first = i;
                }
            }
            path.push_back(min_edge.first);
            current_node = min_edge.first;
            min_edge.second = INT_MAX;
            Q.erase(remove(Q.begin(), Q.end(), min_edge.first), Q.end());
        }
        cout << "test" << endl;
    }

    return results;
}

pair<vector<int>, int> TSP::brute_force(vector<vector<int>> matrix) {
    int j = 1;
    int current_path;
    vector<int> min_path;
    pair<vector<int>, int> results;
    vector<int> path;

    results.second = INT_MAX;
    for(int i = 0; i < matrix.size(); i++) path.push_back(i);

    do {
        cout << j++ << endl;
        current_path = calculate_path_length(matrix, path);
        if(current_path < results.second && current_path != -1) {
            results.first = path;
            results.second = current_path;
        }
    } while(next_permutation(path.begin(), path.end()));

    return results;
}

int TSP::calculate_path_length(vector<vector<int>> matrix, vector<int> path) {
    int path_length = 0;

    for(int i = 0; i < path.size() - 1; i++) {
        if(matrix[path[i]][path[i + 1]] == -1) return -1;
        else path_length = path_length + matrix[path[i]][path[i + 1]];
    }
    path_length = path_length + matrix[path[path.size() - 1]][path[0]];
    return path_length;
}