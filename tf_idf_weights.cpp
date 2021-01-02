/* This program gives the weights by calculating the 
   transformed tf * inverse document frequency of that document
   Input: data/metadata_idf.txt data/documents_idf.txt data/metadata_tf_transformed/ data/documents_tf_transformed/
   Output: data/metadata_tf_idf/ data/documents_tf_idf/
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string metadata_idf = "data/metadata_idf.txt";
const string documents_idf = "data/documents_idf.txt";
const string base_metadata_tf_transformed = "data/metadata_tf_transformed/";
const string base_documents_tf_transformed = "data/documents_tf_transformed/";
const string base_metadata_tf_idf = "data/metadata_tf_idf/";
const string base_documents_tf_idf = "data/documents_tf_idf/";

      
// calculate and save tf*idf
void process(vector<string> uids, string idf_in, string in, string out){
    unordered_map<string, double> idf = read_map_file_double(idf_in);
    int total = uids.size();
    int checkpoint = total / 100;
    for (int i = 0; i < total; i++){
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, double> tf = read_map_file_double(in + uids[i] + ".txt");
        for (auto &d : tf)
            d.second *= idf[d.first];
        write_map_file_double(tf, out + uids[i] + ".txt");
    }
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Processing metadata" << endl;
    process(uids, metadata_idf, base_metadata_tf_transformed, base_metadata_tf_idf);
    cout << "Processing documents" << endl;
    process(uids, documents_idf, base_documents_tf_transformed, base_documents_tf_idf);
    return 0;
}