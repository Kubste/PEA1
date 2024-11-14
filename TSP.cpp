#include "TSP.hpp"
using namespace std;

pair<vector<int>, int> TSP::random(const vector<vector<int>>& matrix, int minutes, chrono::duration<double, micro> &time, int progress_indicator, int optimal_value) {
    pair<vector<int>, int> results;
    vector<int> path;
    int path_length;
    random_device random;
    mt19937 g(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
    results.second = INT_MAX;
    chrono::high_resolution_clock::time_point t0, t1;
    auto start = chrono::steady_clock::now();
    int j = 0;
    for(int i = 0; i < matrix.size(); i++) path.push_back(i);

    while(chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - start).count() < minutes) {
        t0 = chrono::high_resolution_clock::now();

        shuffle(path.begin(), path.end(), g);
        reverse(path.begin() + g() % matrix.size(), path.end());

        path.push_back(path.front());

        path_length = calculate_path_length(matrix, path);
        if(path_length < results.second && path_length != -1) {
            results.first = path;
            results.second = path_length;
        }

        time = time + chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);

        path.pop_back();
        if(progress_indicator) cout << j++ << endl;
        if(path_length == optimal_value) break;
    }
    return results;
}

pair<vector<int>, int> TSP::nn(vector<vector<int>> matrix, chrono::duration<double, micro> &time, int progress_indicator, int minutes) {
    pair<vector<int>, int> results;
    results.second = INT_MAX;
    vector<int> path;
    vector<int> Q;
    chrono::high_resolution_clock::time_point t0, t1;
    auto start = chrono::steady_clock::now();

    for(int j = 0; j < matrix.size(); j++) {
        auto now = chrono::steady_clock::now();
        if(chrono::duration_cast<chrono::minutes>(now - start).count() >= minutes) break;

        t0 = chrono::high_resolution_clock::now();

        path.push_back(j);

        for(int i = 0; i < matrix.size(); i++) if(i != j) Q.push_back(i);
        explore_paths(path, 0, Q, time, j, j, results, matrix);
        t1 = chrono::high_resolution_clock::now();
        time = time + chrono::duration_cast<chrono::microseconds>(t1 - t0);

        if(progress_indicator) cout << "Ukonczono dla wierzcholka startowego : " << j << endl;
        path.clear();
        Q.clear();
    }
    return results;
}

void TSP::explore_paths(vector<int> path, int path_length, vector<int> Q, chrono::duration<double, micro> &time, int current_node, int start_node,
                        pair<vector<int>, int> &results, vector<vector<int>> matrix) {
    vector<pair<int, int>> min_edges;
    int min_edge_value = INT_MAX;
    vector<int> new_path;
    vector<int> new_Q;
    int next_node;
    int edge_length;

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

    for(int i = 0; i < matrix.size(); i++) {
        if(matrix[current_node][i] != -1 && find(Q.begin(), Q.end(), i) != Q.end()) {
            if(matrix[current_node][i] < min_edge_value) {
                min_edges.clear();
                min_edge_value = matrix[current_node][i];
                min_edges.emplace_back(i, matrix[current_node][i]);
            } else if(matrix[current_node][i] == min_edge_value) min_edges.emplace_back(i, matrix[current_node][i]);
        }
    }

    for(int i = 0; i < min_edges.size(); i++) {
        next_node = min_edges[i].first;
        edge_length = min_edges[i].second;

        new_path = path;
        new_path.push_back(next_node);
        new_Q = Q;
        new_Q.erase(remove(new_Q.begin(), new_Q.end(), next_node), new_Q.end());

        explore_paths(new_path, path_length + edge_length, new_Q, time, next_node, start_node, results, matrix);
    }
}

pair<vector<int>, int> TSP::brute_force(const vector<vector<int>>& matrix, int minutes, chrono::duration<double, micro> &time, int progress_indicator) {
    double j = 1;
    int path_length;
    vector<int> min_path;
    pair<vector<int>, int> results;
    vector<int> path;
    vector<int> path_to_calculate;
    chrono::high_resolution_clock::time_point t0;
    auto start = chrono::steady_clock::now();

    double num_of_paths = tgamma(matrix.size() + 1);

    results.second = INT_MAX;
    for(int i = 0; i < matrix.size(); i++) path.push_back(i);

    do {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::minutes>(now - start);
        if(elapsed.count() >= minutes && j/num_of_paths < 0.9) return results;
        t0 = chrono::high_resolution_clock::now();
        path_to_calculate = path;
        path_to_calculate.push_back(path_to_calculate.front());
        path_length = calculate_path_length(matrix, path_to_calculate);
        if(path_length < results.second && path_length != -1) {
            results.first = path_to_calculate;
            results.second = path_length;
        }
        time = time + chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);
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