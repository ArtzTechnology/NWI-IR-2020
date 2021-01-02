/* This program counts the total words per document and saves all
   results in one file. It also prints the average document length.
*/
#include <iostream>
#include <vector>
#include <unordered_map> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_documents_tf = "data/documents_tf/";
const string base_metadata_tf = "data/metadata_tf/";
const string base_documents_lengths = "data/documents_lengths.txt";
const string base_metadata_lengths = "data/metadata_lengths.txt";

// count the length
int count_length(unordered_map<string, int> data){
    int result = 0;
    for (auto &d : data)
        result += d.second;
    return result;
}  

// count and save term frequencies
int process_lengths(vector<string> uids, string in, string out)
{
    int result = 0;
    int total = uids.size();
    int checkpoint = total / 100;
    vector<string> lengths;
    for (int i = 0; i < total; i++)
    {
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, int> data = read_map_file(in + uids[i] + ".txt");
        int length = count_length(data);
        lengths.push_back(to_string(length));
        result += length;
    }
    write_file(lengths, out);
    return result;
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Found " << uids.size() << " uids in valid_uids.txt" << endl;
    cout << "Processing metadata" << endl;
    int metadata_length = process_lengths(uids, base_metadata_tf, base_metadata_lengths);
    cout << metadata_length / uids.size() << " avdl metadata" << endl;
    cout << "Processing documents" << endl;
    int document_length = process_lengths(uids, base_documents_tf, base_documents_lengths);
    cout << document_length / uids.size() << " avdl document" << endl;
    return 0;
}