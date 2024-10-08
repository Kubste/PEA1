#include "Main.hpp"
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void Main::run() {
    pair<vector<int>, int> results;
    vector<chrono::duration<double, milli>> times;
    pair<vector<vector<int>>, int> data;

    assign_parameters(file_manager.read_config_file(config_path));
    data = file_manager.read_data_file(data_path);
    matrix = data.first;
    optimal_value = data.second;

    print_info();

    if(method == 1) {
        results = tsp.random(matrix, iterations, times);
        print_results(results, times);
    }
    else if(method == 2) {
        results = tsp.nn(matrix, times);
        print_results(results, times);
    }
    else if(method == 3) {
        results = tsp.brute_force(matrix, times);
        print_results(results, times);
    }

}

void Main::assign_parameters(pair<vector<string>, vector<int>> parameters) {
    data_path = parameters.first[0];
    result_path = parameters.first[1];
    method = parameters.second[0];
    iterations = parameters.second[1];
    progress_indicator = parameters.second[2];
}

void Main::print_info() {

    size_t position = data_path.find_last_of('\\');
    cout << "Plik zawierajacy dane problemu: " << data_path.substr(position + 1) << endl;
    cout << "Wynik optymalny: " << optimal_value << endl;
    cout << "Wybrana metoda: ";
    if(method == 1) cout << "losowa" << endl;
    else if(method == 2) cout << "najblizszego sasiada" << endl;
    else if(method == 3) cout << "przeglad zupelny" << endl;
}

void Main::print_results(pair<vector<int>, int> results, vector<chrono::duration<double, milli>> times) {
    chrono::duration<double, milli> total_time{};


    cout << "Otrzymana najkrotsza sciezka: ";
    for(int i = 0; i < results.first.size() - 1; i++) cout << results.first[i] << " -> ";
    cout << results.first.back() << endl;
    cout << "Dlugosc otrzymanej sciezki: " << results.second << endl;

    for(int i = 0; i < times.size(); i++) total_time = total_time + times[i];

    cout << "Sredni czas rozwiazania: " << (total_time / times.size()).count() << " ms" << endl;
    cout << "Laczny czas rozwiazania: " << total_time.count() << " ms" << endl;
}

int main() {
    srand(time(0));
    Main main_obj{};
    main_obj.run();

    return 0;
}