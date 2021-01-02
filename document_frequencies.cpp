/* This program counts the document frequency for 
*  the metadata and documents
*  Input: data/metadata_tf/ data/documents_tf/
*  Output: data/metadata_df.txt data/documents_df.txt
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_documents_tf = "data/documents_tf/";
const string base_metadata_tf = "data/metadata_tf/";
const string metadata_df = "data/metadata_df.txt";
const string documents_df = "data/documents_df.txt";

      
// count and save frequencies
void count(vector<string> uids, string in, string out){
    unordered_map<string, int> frequencies;
    int total = uids.size();
    int checkpoint = total / 100;
    for (int i = 0; i < total; i++){
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, int> data = read_map_file(in + uids[i] + ".txt");
        for (auto &d : data){
            string word = d.first;
            if (frequencies.find(d.first) == frequencies.end())
                frequencies.insert({d.first, 1});
            else
                frequencies[d.first]++;                
        }
    }
    write_map_file(frequencies, out);
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Processing metadata" << endl;
    count(uids, base_metadata_tf, metadata_df);
    cout << "Processing documents" << endl;
    count(uids, base_documents_tf, documents_df);
    return 0;
}