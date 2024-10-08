#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <string>
#include <vector>

using namespace std;

class File_manager {

    public:
        pair<vector<string>, vector<int>> read_config_file(const string& path);
        pair<vector<vector<int>>, int> read_data_file(const string& path);
};

#endif