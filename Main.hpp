#ifndef MAIN_HPP
#define MAIN_HPP
#include "File_manager.hpp"
#include "File_manager.cpp"
#include "TSP.hpp"
#include "TSP.cpp"
#include <string>

using namespace std;

class Main {

    public:
        void run();

    private:
        string config_path = R"(C:\Users\jakub\OneDrive\Pulpit\PEAProjekt1\config.txt)";
        string data_path;
        string result_path;
        int method;
        int iterations;
        int optimal_value;
        int progress_indicator;
        File_manager file_manager;
        vector<vector<int>> matrix;
        TSP tsp;

        void assign_parameters(pair<vector<string>, vector<int>> parameters);
};

#endif