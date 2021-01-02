using namespace std;
vector<string> read_file(string file_name);
unordered_map<string, int> read_map_file(string file_name);
unordered_map<string, double> read_map_file_double(string file_name);
void write_file(vector<string> data, string file_name);
void write_map_file(unordered_map<string, int> data, string file_name);
void write_map_file_double(unordered_map<string, double> data, string file_name);