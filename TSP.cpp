#include "TSP.hpp"
using namespace std;

pair<vector<int>, int> TSP::random(const vector<vector<int>>& matrix, int minutes, vector<chrono::duration<double, milli>> &times, int progress_indicator) {
    pair<vector<int>, int> results;
    vector<int> path;
    int path_length;
    random_device random;
    mt19937 g(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
    results.second = INT_MAX;
    chrono::high_resolution_clock::time_point t0, t1;
    auto start = chrono::steady_clock::now();
    int j = 0;

    while(true) {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::minutes>(now - start);
        if(elapsed.count() >= minutes) break;
        t0 = chrono::high_resolution_clock::now();
        for(int i = 0; i < matrix.size(); i++) path.push_back(i);
        shuffle(path.begin(), path.end(), g);
        path.push_back(path.front());

        path_length = calculate_path_length(matrix, path);
        if(path_length < results.second && path_length != -1) {
            results.first = path;
            results.second = path_length;
        }
        path.clear();
        path.shrink_to_fit();
        t1 = chrono::high_resolution_clock::now();
        times.emplace_back(t1 - t0);
        if(progress_indicator) cout << j++ << endl;
    }
    return results;
}

pair<vector<int>, int> TSP::nn(vector<vector<int>> matrix, vector<chrono::duration<double, milli>> &times, int progress_indicator) {
    pair<vector<int>, int> results;
    results.second = INT_MAX;
    chrono::high_resolution_clock::time_point t0, t1;

    for(int j = 0; j < matrix.size(); j++) {
        t0 = chrono::high_resolution_clock::now();

        vector<int> path;
        vector<int> Q;

        path.push_back(j);
        int path_length = 0;

        for(int i = 0; i < matrix.size(); i++) if(i != j) Q.push_back(i);
        explore_paths(path, path_length, Q, times, j, j, results, matrix);
        t1 = chrono::high_resolution_clock::now();
        times.emplace_back(t1 - t0);

        if(progress_indicator) cout << "Completed for start node: " << j << endl;
    }
    return results;
}

void TSP::explore_paths(vector<int> path, int path_length, vector<int> Q, vector<chrono::duration<double, milli>> &times, int current_node, int start_node,
                        pair<vector<int>, int> &results, vector<vector<int>> matrix) {

    if(Q.empty()) {
        if(matrix[current_node][start_node] != -1) {
            path_length += matrix[current_node][start_node];
            path.push_back(start_node);

            if(path_length < results.second) {
                results.first = path;
                results.second = path_length;
            }
        }
        return;
    }

    vector<pair<int, int>> min_edges;
    int min_value = INT_MAX;
    for(int i = 0; i < matrix.size(); i++) {
        if(matrix[current_node][i] != -1 && find(Q.begin(), Q.end(), i) != Q.end()) {
            if(matrix[current_node][i] < min_value) {
                min_edges.clear();
                min_value = matrix[current_node][i];
                min_edges.emplace_back(i, matrix[current_node][i]);
            } else if(matrix[current_node][i] == min_value) min_edges.emplace_back(i, matrix[current_node][i]);
        }
    }

    // Dla każdej z minimalnych krawędzi wywołujemy rekurencyjnie funkcję
    for(int i = 0; i < min_edges.size(); i++) {
        int next_node = min_edges[i].first;
        int edge_length = min_edges[i].second;

        vector<int> new_path = path;
        new_path.push_back(next_node);
        vector<int> new_Q = Q;
        new_Q.erase(remove(new_Q.begin(), new_Q.end(), next_node), new_Q.end());

        explore_paths(new_path, path_length + edge_length, new_Q, times, next_node, start_node, results, matrix);
    }
}

pair<vector<int>, int> TSP::brute_force(const vector<vector<int>>& matrix, int minutes, vector<chrono::duration<double, milli>> &times, int progress_indicator) {
    double j = 1;
    int current_path_length;
    vector<int> min_path;
    pair<vector<int>, int> results;
    vector<int> path;
    vector<int> path_to_calculate;
    chrono::high_resolution_clock::time_point t0, t1;
    auto start = chrono::steady_clock::now();

    double num_of_paths = tgamma(matrix.size() + 1);

    results.second = INT_MAX;
    for(int i = 0; i < matrix.size(); i++) path.push_back(i);

    do {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::minutes>(now - start);
        if(elapsed.count() >= minutes && j/num_of_paths < 0.9) break;
        path_to_calculate = path;
        path_to_calculate.push_back(path_to_calculate.front());
        t0 = chrono::high_resolution_clock::now();
        current_path_length = calculate_path_length(matrix, path_to_calculate);
        if(current_path_length < results.second && current_path_length != -1) {
            results.first = path_to_calculate;
            results.second = current_path_length;
        }
        t1 = chrono::high_resolution_clock::now();
        times.emplace_back(t1 - t0);
        if(progress_indicator) cout << j << endl;
        j++;
    } while(next_permutation(path.begin(), path.end()));

    return results;
}

int TSP::calculate_path_length(vector<vector<int>> matrix, vector<int> path) {
    int path_length = 0;

    for(int i = 0; i < path.size() - 1; i++) {
        if(matrix[path[i]][path[i + 1]] == -1) return -1;
        else path_length = path_length + matrix[path[i]][path[i + 1]];
    }
    return path_length;
}