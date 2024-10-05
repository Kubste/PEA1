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

vector<vector<int>> File_manager::read_data_file(const string& path) {
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
    }

    file.close();

    return matrix;
}