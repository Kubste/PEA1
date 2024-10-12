#include "File_manager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

pair<vector<string>, vector<int>> File_manager::read_config_file(const string& path) {
    pair<vector<string>, vector<int>> results;
    string line;
    ifstream file;
    string sub_str;
    int line_num = 0;

    file.open(path);

    if(file.is_open()) {
        while(getline(file, line)) {
            size_t position = line.find('#');
            sub_str = line.substr(position + 2);
            if(line_num < 2) results.first.push_back(sub_str);
            else results.second.push_back(stoi(sub_str));
            line_num++;
        }
    }

    file.close();

    return results;
}

pair<vector<vector<int>>, int> File_manager::read_data_file(const string& path) {
    pair<vector<vector<int>>, int> data;
    vector<vector<int>> matrix;
    string line;
    ifstream file;

    file.open(path);

    if(file.is_open()) {
        getline(file, line);
        int size = stoi(line);
        for(int i = 0; i < size; i++) {
            getline(file, line);
            stringstream ss(line);
            vector<int> row;
            int number;
            while(ss >> number) row.push_back(number);
            matrix.push_back(row);
        }
        getline(file, line);
        data.second = stoi(line);
    }

    file.close();

    data.first = matrix;
    return data;
}

void File_manager::write_to_file(std::string data_name, const std::string& results_name, int optimal_value, vector<chrono::duration<double, milli>> total_times,
                                 chrono::duration<double, milli> time, float absolute_error, float relative_error) {

    ofstream file(results_name);

    file << "Nazwa instancji," << data_name << "\n";
    file << "Wynik optymalny," << optimal_value << "\n";
    file << "Sredni czas wykonania," << time.count() << "\n";
    file << "Sredni blad bezwzgledny," << absolute_error << "\n";
    file << "Sredni blad wzgledny," << relative_error << "\n";
    file << "Numer proby,Czas wykonania" << "\n";

    for(int i = 0; i < total_times.size(); i++) {
        file << i + 1 << "," << total_times[i].count() << "\n";
    }

    file.close();
}