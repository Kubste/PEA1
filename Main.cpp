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

    if(progress_indicator == 0) print_info();

    for(int i = 0; i < repetitions; i++) {
        if(method == 1)results = tsp.random(matrix, minutesR, times, progress_indicator);
        else if(method == 2) results = tsp.nn(matrix, times, progress_indicator);
        else if(method == 3) results = tsp.brute_force(matrix, minutesB, times, progress_indicator);

        if(progress_indicator) print_info();
        print_partial_results(results, times, i + 1);
    }
    print_total_results();
    size_t positionD = data_path.find_last_of('\\');
    size_t positionR = data_path.find_last_of('\\');
    file_manager.write_to_file(data_path.substr(positionD + 1), result_path.substr(positionR + 1), optimal_value, total_times,
                               total_time / repetitions, total_absolute_error / repetitions, total_relative_error / repetitions);
}

void Main::assign_parameters(pair<vector<string>, vector<int>> parameters) {
    data_path = parameters.first[0];
    result_path = parameters.first[1];
    method = parameters.second[0];
    minutesR = parameters.second[1];
    if(parameters.second[2] == -1) minutesB = INT_MAX;
    else minutesB = parameters.second[2];
    repetitions = parameters.second[3];
    progress_indicator = parameters.second[4];
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

void Main::print_partial_results(pair<vector<int>, int> results, vector<chrono::duration<double, milli>> &times, int repetition) {
    chrono::duration<double, milli> partial_time{};
    float absolute_error;
    float relative_error;

    cout << endl << "Wykonano " << repetition << " przeszukanie" << endl;
    cout << "Otrzymana najkrotsza sciezka: ";
    for(int i = 0; i < results.first.size() - 1; i++) cout << results.first[i] << " -> ";
    cout << results.first.back() << endl;
    cout << "Dlugosc otrzymanej sciezki: " << results.second << endl;

    for(int i = 0; i < times.size(); i++) partial_time = partial_time + times[i];
    total_time = total_time + partial_time;

    cout << "Sredni czas rozwiazania " << repetition << ": " << (partial_time / times.size()).count() << " ms" << endl;
    cout << "Laczny czas rozwiazania " << repetition << ": " << partial_time.count() << " ms" << endl;
    total_times.emplace_back(partial_time / times.size());

    absolute_error = results.second - optimal_value;
    relative_error = (absolute_error / optimal_value) * 100;
    total_absolute_error = total_absolute_error + absolute_error;
    total_relative_error = total_relative_error + relative_error;

    cout << "Blad bezwzgledny dla rozwiazania " << repetition << ": " << absolute_error << endl;
    cout << "Blad wzgledny dla rozwiazania " << repetition << ": " << relative_error << "%" << endl;

    times.clear();
    times.shrink_to_fit();
}

void Main::print_total_results() {

    cout << endl << "Wykonano " << repetitions << " powtorzen" << endl;
    cout << "Sredni czas wyznaczenia rozwiazania: " << total_time.count() / repetitions << endl;
    cout << "Sredni blad bezwzgledny: " << total_absolute_error / repetitions << endl;
    cout << "Sredni blad wzgledny: " << total_relative_error / repetitions << "%" << endl;

}

int main() {
    Main main_obj{};
    main_obj.run();

    system("pause");

    return 0;
}