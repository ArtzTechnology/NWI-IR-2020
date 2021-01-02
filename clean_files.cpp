/* This program cleans the files by removing non 
   alphabetic symbols and setting everything to lowercase. 
   It removes stopwords and saves the results with one term per line.
   Input: data/metadata_text/ data/documents_text/ data/english.txt data/valid_uids.txt
   Output: data/metadata_clean/ data/documents_clean/
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map> 
#include "io.h"

using namespace std;

const string data_valid_uids = "data/valid_uids.txt";
const string base_documents_text = "data/documents_text/";
const string base_metadata_text = "data/metadata_text/";
const string base_documents_clean = "data/documents_clean/";
const string base_metadata_clean = "data/metadata_clean/";
const string english_stopwords = "data/english.txt";

// concat all paragraphs
string concat(vector<string> data){
    string result = "";
    for (auto const &d : data)
        result += d;
    return result;
}
    
// remove all non alphabetic symbols and set to lowercase
string filter_string(string data){
    for (int i = 0; i < data.size(); i++){
        if (data[i] >= 'A' && data[i] <= 'Z')
            data[i] = tolower(data[i]);
        if ((data[i] < 'a' || data[i] > 'z') && data[i] != ' '){
            data.erase(i, 1);
            i--;
        }
    }
    return data;
}  

// split up to vector of terms and remove stopwords
vector<string> split_terms(string data, vector<string> stopwords){
    vector<string> result;
    istringstream iss(data);
    while (iss >> data){
        bool stopword = false;
        for (auto const& w : stopwords){
            if (data == w){
                stopword = true;
                break;
            }
        }
        if (!stopword)
            result.push_back(data);
    }
    return result;
}

// clean the documents
void clean(vector<string> uids, vector<string> stopwords, string in, string out)
{
    int total = uids.size();
    int checkpoint = total / 100;
    for (int i = 0; i < total; i++)
    {
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        vector<string> data = read_file(in + uids[i] + ".txt");
        string term_list = concat(data);
        string filtered_list = filter_string(term_list);
        vector<string> clean_list = split_terms(filtered_list, stopwords);
        write_file(clean_list, out + uids[i] + ".txt");
    }
}

int main()
{
    cout << "Reading data/valid_uids.txt" << endl;
    vector<string> uids = read_file(data_valid_uids);
    cout << "Found " << uids.size() << " uids in valid_uids.txt" << endl;
    cout << "Read English stopwords" << endl;
    vector<string> stopwords = read_file(english_stopwords);
    cout << "Found " << stopwords.size() << " stopwords" << endl;
    cout << "Processing metadata" << endl;
    clean(uids, stopwords, base_metadata_text, base_metadata_clean);
    cout << "Processing documents" << endl;
    clean(uids, stopwords, base_documents_text, base_documents_clean);
    return 0;
}