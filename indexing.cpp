/* This program calculates the final weights of the
   terms after the normalization. The normalization is
   given by 1 - b + b * document_length / avld. 
   Input: data/metadata_tf_idf/ data/documents_tf_idf/ data/valid_uids.txt
   Output: data/metadata_model_25/ data/document_model_25/ 
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_metadata_tf_idf = "data/metadata_tf_idf/";
const string base_documents_tf_idf = "data/documents_tf_idf/";
const string base_metadata_model = "data/metadata_model_";
const string base_documents_model = "data/documents_model_";
const string document_lengths = "data/documents_lengths.txt";
const string metadata_lengths = "data/metadata_lengths.txt";
      
// calculate the final weight with normalizer
void process(vector<string> uids, string len, string in, string out, int avdl, double b){
    vector<string> lengths = read_file(len);
    double a = 1 - b;
    int total = uids.size();
    int checkpoint = total / 100;
    for (int i = 0; i < total; i++){
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, double> tf_idf = read_map_file_double(in + uids[i] + ".txt");
        if(stoi(lengths[i]) > 0){
            double normalizer = stoi(lengths[i]) / avdl;
            for (auto &d : tf_idf)
                d.second /= a + b * normalizer;
        }
        write_map_file_double(tf_idf, out + to_string(int(b*100)) + "/"  + uids[i] + ".txt");
    }
}

int main()
{
    int metadata_avdl = 104;
    int documents_avdl = 2085;
    double b = 0.25;
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Processing metadata for " << base_metadata_model << int(b*100) << endl;
    process(uids, metadata_lengths, base_metadata_tf_idf, base_metadata_model, metadata_avdl, b);
    cout << "Processing documents for " << base_metadata_model << int(b*100) << endl;
    process(uids, document_lengths, base_documents_tf_idf, base_documents_model, documents_avdl, b);
    return 0;
}