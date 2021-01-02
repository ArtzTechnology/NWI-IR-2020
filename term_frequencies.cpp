/* This program counts the term frequencies
   Input: data/metadata_stemmed data/documents_stemmed/ data/valid_uids.txt
   Output: data/documents_tf/ data/metadata_tf/
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_documents_stemmed = "data/documents_stemmed/";
const string base_metadata_stemmed = "data/metadata_stemmed/";
const string base_documents_tf = "data/documents_tf/";
const string base_metadata_tf = "data/metadata_tf/";

// count the term frequencies
unordered_map<string, int> term_frequencies(vector<string> terms){
    unordered_map<string, int> result;
    for (int i=0; i<terms.size(); i++)        
        result[terms[i]]++;
    return result;
}  

// count and save term frequencies
void process_term_frequencies(vector<string> uids, string in, string out)
{
    int total = uids.size();
    int checkpoint = total / 100;
    for (int i = 0; i < total; i++){
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        vector<string> terms = read_file(in + uids[i] + ".txt");
        unordered_map<string, int> tf = term_frequencies(terms);
        write_map_file(tf, out + uids[i] + ".txt");
    }
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Found " << uids.size() << " uids in valid_uids.txt" << endl;
    cout << "Processing metadata" << endl;
    process_term_frequencies(uids, base_metadata_stemmed, base_metadata_tf);
    cout << "Processing documents" << endl;
    process_term_frequencies(uids, base_documents_stemmed, base_documents_tf);
    return 0;
}