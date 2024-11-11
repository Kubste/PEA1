#include "Main.hpp"
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void Main::run() {
    pair<vector<int>, int> results;
    vector<chrono::duration<double, micro>> times;
    pair<vector<vector<int>>, int> data;
    chrono::duration<double, micro> time{};

    assign_parameters(file_manager.read_config_file(config_path));
    data = file_manager.read_data_file(data_path);
    matrix = data.first;
    optimal_value = data.second;

    if(progress_indicator == 0) print_info();

    for(int i = 0; i < repetitions; i++) {
        if(method == 1)results = tsp.random(matrix, minutesR, time, progress_indicator, optimal_value);
        else if(method == 2) results = tsp.nn(matrix, time, progress_indicator, minutesNN);
        else if(method == 3) results = tsp.brute_force(matrix, minutesB, time, progress_indicator);

        print_partial_results(results, time, i + 1);
    }
    if(progress_indicator) print_info();
    print_total_results();
    size_t positionD = data_path.find_last_of('\\');
    size_t positionR = data_path.find_last_of('\\');
    file_manager.write_to_file(data_path.substr(positionD + 1), result_path.substr(positionR + 1), optimal_value, total_times,
                               total_time / time_measurements, total_absolute_error / repetitions, total_relative_error / repetitions);
}

void Main::assign_parameters(pair<vector<string>, vector<int>> parameters) {
    data_path = parameters.first[0];
    result_path = parameters.first[1];
    method = parameters.second[0];
    minutesR = parameters.second[1];
    if(parameters.second[2] == -1) minutesNN = INT_MAX;
    else minutesNN = parameters.second[2];
    if(parameters.second[3] == -1) minutesB = INT_MAX;
    else minutesB = parameters.second[3];
    repetitions = parameters.second[4];
    progress_indicator = parameters.second[5];
}

void Main::print_info() {

    size_t position = data_path.find_last_of('\\');
    cout << endl << "Plik zawierajacy dane problemu: " << data_path.substr(position + 1) << endl;
    cout << "Wynik optymalny: " << optimal_value << endl;
    cout << "Wybrana metoda: ";
    if(method == 1) cout << "losowa" << endl;
    else if(method == 2) cout << "najblizszego sasiada" << endl;
    else if(method == 3) cout << "przeglad zupelny" << endl;
    cout << "Liczba powtorzen przeszukania: " << repetitions << endl;
    if(method == 1) cout << "Czas pojedynczego przeszukania: " << minutesR << " min" << endl;
    else if(method == 3 && minutesB != INT_MAX) cout << "Maksymalny czas przeszukania: " << minutesB << " min" << endl;
    else if(method == 3) cout << "Brak ograniczenia czasowego" << endl;
    cout << endl;
}

void Main::print_partial_results(pair<vector<int>, int> results, chrono::duration<double, micro> &time, int repetition) {
    float absolute_error;
    float relative_error;

    cout << "Wykonano " << repetition << " przeszukanie" << endl;
    cout << "Otrzymana najkrotsza sciezka: ";
    for(int i = 0; i < results.first.size() - 1; i++) cout << results.first[i] << " -> ";
    cout << results.first.back() << endl;
    cout << "Dlugosc otrzymanej sciezki: " << results.second << endl;

    total_time = total_time + time;
    if(time.count() != 0) time_measurements++;

    cout << "Czas rozwiazania: " << repetition << ": ";
    cout << fixed << setprecision(3);
    if(time.count() >= 180000000) cout << chrono::duration<double, ratio<60>>(time).count() << " min" << endl;
    else if(time.count() >= 1000000) cout << chrono::duration<double>(time).count() << " s" << endl;
    else if(time.count() >= 1000) cout << chrono::duration<double, milli>(time).count() << " ms" << endl;
    else cout << time.count() << " micro" << endl;
    cout.unsetf(ios::fixed);
    total_times.emplace_back(time);

    absolute_error = results.second - optimal_value;
    relative_error = (absolute_error / optimal_value);
    total_absolute_error = total_absolute_error + absolute_error;
    total_relative_error = total_relative_error + relative_error;

    cout << "Blad bezwzgledny dla rozwiazania " << repetition << ": " << absolute_error << endl;
    cout << "Blad wzgledny dla rozwiazania " << repetition << ": " << relative_error << " = " << relative_error * 100 << "% " << endl << endl;

    time = chrono::duration<double, micro>(0.0);
}

void Main::print_total_results() {

    cout << endl << "Wykonano " << repetitions << " powtorzen" << endl;
    cout << fixed << setprecision(3);
    cout << "Sredni czas wyznaczenia rozwiazania: ";
    if(total_time.count() / time_measurements >= 180000000) cout << chrono::duration<double, ratio<60>>(total_time).count() << " min" << endl;
    else if(total_time.count() / time_measurements >= 1000000) cout << chrono::duration<double>(total_time).count() / time_measurements << " s" << endl;
    else if(total_time.count() / time_measurements >= 1000) cout << chrono::duration<double, milli>(total_time).count() / time_measurements << " ms" << endl;
    else cout << total_time.count() / time_measurements << " micro" << endl;
    cout.unsetf(ios::fixed);
    cout << "Sredni blad bezwzgledny: " << total_absolute_error / repetitions << endl;
    cout << "Sredni blad wzgledny: " << total_relative_error / repetitions << " = " << (total_relative_error / repetitions) * 100 << "% " << endl;

}

int main() {
    Main main_obj{};
    main_obj.run();

    system("pause");

    return 0;
}