#include "Main.hpp"
#include <iostream>
#include <ctime>
using namespace std;

void Main::run() {
    int min_path = -1;
    int current_path;
    pair<vector<int>, int> results;

    assign_parameters(file_manager.read_config_file(config_path));
    matrix = file_manager.read_data_file(data_path);

    if(method == 1) {
        min_path = tsp.random(matrix).second;
        for(int i = 0; i < iterations - 1; i++) {
            current_path = tsp.random(matrix).second;
            if(current_path < min_path && current_path != -1) min_path = current_path;
        }
        cout << min_path << endl;
    } else if(method == 2) {
        tsp.nn(matrix);
    } else if(method == 3) {
        results = tsp.brute_force(matrix);
        cout << results.second << endl;
        for(int i = 0; i < results.first.size(); i++) cout << results.first[i] << " -> ";
        cout << endl;
    }
}

void Main::assign_parameters(pair<vector<string>, vector<int>> parameters) {
    data_path = parameters.first[0];
    result_path = parameters.first[1];
    method = parameters.second[0];
    iterations = parameters.second[1];
    optimal_value = parameters.second[2];
    progress_indicator = parameters.second[3];
}

int main() {
    srand(time(0));
    Main main_obj{};
    main_obj.run();

    return 0;
}