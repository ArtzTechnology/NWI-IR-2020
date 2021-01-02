/* This program transforms the term frequencies with
   tf(w) = ln(1+ln(1+tf(w))
   Input: data/metadata_tf/ data/documents_tf/ data/valid_uids.txt
   Output: data/metadata_tf_transformed/ data/documents_tf_transformed/
*/
#include <iostream>
#include <vector>
#include <unordered_map> 
#include <math.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_documents_tf = "data/documents_tf/";
const string base_metadata_tf = "data/metadata_tf/";
const string base_documents_transformed = "data/documents_tf_transformed/";
const string base_metadata_transformed = "data/metadata_tf_transformed/";

// transform term frequencies
void transform(vector<string> uids, string in, string out)
{
    int total = uids.size();
    int checkpoint = total / 100;
    vector<string> lengths;
    for (int i = 0; i < total; i++)
    {
        unordered_map<string, double> result;
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, int> data = read_map_file(in + uids[i] + ".txt");
        for (auto &d : data){
            double tf_transformed = log(1 + log (1 + d.second));
            result.insert({d.first, tf_transformed});
        }
        write_map_file_double(result, out + uids[i] + ".txt");
    }
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Found " << uids.size() << " uids in valid_uids.txt" << endl;
    cout << "Processing metadata" << endl;
    transform(uids, base_metadata_tf, base_metadata_transformed);
    cout << "Processing documents" << endl;
    transform(uids, base_documents_tf, base_documents_transformed);
    return 0;
}