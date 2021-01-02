#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map> 

using namespace std;

// return file content as a vector of strings
vector<string> read_file(string file_name){
    vector<string> data;
    ifstream in_file(file_name);
    string s;
    while (getline(in_file, s))
        data.push_back(s);
    in_file.close();
    return data;
}

// write vector of strings to file
void write_file(vector<string> data, string file_name){
    ofstream out_file;
    out_file.open(file_name);
    for (auto const &value : data)
        out_file << value + "\n";
    out_file.close();
}

// read unordered map to file
unordered_map<string, int> read_map_file(string file_name){
    unordered_map<string, int> data;
    ifstream in_file;
    in_file.open(file_name);
    string s;
    while (getline(in_file, s)){
        int index = s.find(' ');
        string word = s.substr(0, index);
        int count = stoi(s.substr(index));
        data.insert({word, count});
    }
    in_file.close();
    return data;
}

// write unordered map to file
void write_map_file(unordered_map<string, int> data, string file_name){
    ofstream out_file;
    out_file.open(file_name);
    for (auto &value : data)
        out_file << value.first + " " + to_string(value.second) + "\n";
    out_file.close();
}

// double variants for files with double precision

// read unordered map to file
unordered_map<string, double> read_map_file_double(string file_name){
    unordered_map<string, double> data;
    ifstream in_file;
    in_file.open(file_name);
    string s;
    while (getline(in_file, s)){
        int index = s.find(' ');
        string word = s.substr(0, index);
        double count = atof(s.substr(index).c_str());
        data.insert({word, count});
    }
    in_file.close();
    return data;
}

// write unordered map to file
void write_map_file_double(unordered_map<string, double> data, string file_name){
    ofstream out_file;
    out_file.open(file_name);
    for (auto &value : data)
        out_file << value.first + " " + to_string(value.second) + "\n";
    out_file.close();
}
