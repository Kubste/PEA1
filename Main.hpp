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
        string config_path = R"(config.txt)";
        string data_path;
        string result_path;
        int method;
        int minutesR;
        int minutesB;
        int optimal_value;
        int progress_indicator;
        int repetitions;
        File_manager file_manager;
        vector<vector<int>> matrix;
        TSP tsp;
        chrono::duration<double, micro> total_time{};
        float total_absolute_error;
        float total_relative_error;
        vector<chrono::duration<double, micro>> total_times;

        void print_info();
        void print_partial_results(pair<vector<int>, int> results, chrono::duration<double, micro> &time, int repetition);
        void print_total_results();
        void assign_parameters(pair<vector<string>, vector<int>> parameters);
};

#endif