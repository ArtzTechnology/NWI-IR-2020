/*  This program filters all the documents in metadata.csv and judgements.txt 
    that do not include a parsed pmc file. It also creates a file with valid ids.
    Input: COVID-19/
    Output: data/metadata.csv data/judgements.txt data/valid_uids.txt
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "io.h"

using namespace std;

const string covid_metadata = "COVID-19/metadata.csv";
const string data_metadata = "data/metadata.csv";
const string pmc_file = "document_parses/pmc_json/";
const string covid_judgements = "COVID-19/judgements.txt";
const string data_judgements = "data/judgements.txt";
const string data_valid_uids = "data/valid_uids.txt";

// filter the documents that do not include a pmc parsed file out the metadata
vector<string> filter_metadata(vector<string> metadata){
    vector<string> data;
    for(auto const& value: metadata){
        if (value.find(pmc_file) != std::string::npos)
            data.push_back(value);
    }
    return data;
}

// get a list of valid ids from the metadata
vector<string> get_valid_uids(vector<string> metadata){
    vector<string> uids; 
    for(auto const& document: metadata)
            uids.push_back(document.substr(0, document.find(",")));
    return uids;
}

// filter the documents that do not include a pmc parsed file out the judgements
vector<string> filter_judgements(vector<string> uids, vector<string> judgements){
    vector<string> data;
    string uid_judgement;
    for(auto const& judgement: judgements) {
        istringstream iss(judgement);
        for (int i = 0; i < 3; i++)
            iss >> uid_judgement;
        for(auto const& uid: uids) {
            if (uid_judgement == uid){
                data.push_back(judgement);
                break;
            }
        }
    }
    return data;
}

int main()
{
    cout << "Reading COVID-19/metadata.csv" << endl;
    vector<string> metadata = read_file(covid_metadata);
    cout << "Found " << metadata.size() << " documents in COVID-19/metadata.csv" << endl;
    cout << "Filtering metadata for pmc parsed files" << endl;
    vector<string> filtered_metadata = filter_metadata(metadata);
    cout << "Found " << filtered_metadata.size() << " documents with pmc parsed files" << endl;
    cout << "Writing filtered metadata to data/metadata.csv" << endl;
    write_file(filtered_metadata, data_metadata);
    cout << "Retrieving list of valid uids" << endl;
    vector<string> valid_uids = get_valid_uids(filtered_metadata);
    cout << "Found " << valid_uids.size() << " valid uids in total" << endl;
    cout << "Writing valid uids to data/valid_uids.txt" << endl;
    write_file(valid_uids, data_valid_uids);
    cout << "Reading COVID-19/judgements.txt" << endl;
    vector<string> judgements = read_file(covid_judgements);
    cout << "Found " << judgements.size() << " judged documents in total" << endl;
    cout << "Filtering judgements for pmc parsed files" << endl;
    vector<string> filtered_judgements = filter_judgements(valid_uids, judgements);
    cout << "Found " << filtered_judgements.size() << " judged documents with pmc parsed files" << endl;
    cout << "Writing filtered judgements to data/judgements.txt" << endl;
    write_file(filtered_judgements, data_judgements);
    return 0;
}