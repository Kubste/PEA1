#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <string>
#include <vector>
#include <chrono>

using namespace std;

class File_manager {

    public:
        pair<vector<string>, vector<int>> read_config_file(const string& path);
        pair<vector<vector<int>>, int> read_data_file(const string& path);
        void write_to_file(string data_name, const string& results_name, int optimal_value, vector<chrono::duration<double,
                milli>> total_times, chrono::duration<double, milli> time, float absolute_error, float relative_error);
};

#endif