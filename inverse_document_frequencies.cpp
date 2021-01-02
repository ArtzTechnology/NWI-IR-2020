/* This program calculates the inverse document
   frequencies as log(m+1/ df(w)) where M is the 
   number of documents and df is the document frequency
   of term w.
   Input: data/metadata_df.txt data/documents_df.txt data/valid_uids.txt
   Output: data/metadata_idf.txt data/documents_idf.txt
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string metadata_df = "data/metadata_df.txt";
const string documents_df = "data/documents_df.txt";
const string metadata_idf = "data/metadata_idf.txt";
const string documents_idf = "data/documents_idf.txt";

      
// calculate and save idf's
void count(vector<string> uids, string in, string out){
    unordered_map<string, double> idf;
    unordered_map<string, int> data = read_map_file(in);
    int m = uids.size() + 1;
    for (auto &d : data){
        double idf_term = log(m / d.second);
        idf.insert({d.first, idf_term});                   
    }
    write_map_file_double(idf, out);
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Processing metadata" << endl;
    count(uids, metadata_df, metadata_idf);
    cout << "Processing documents" << endl;
    count(uids, documents_df, documents_idf);
    return 0;
}