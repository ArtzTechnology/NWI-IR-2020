/* This program calculates the scores of the query
   per document and per metadata and saves the results of these
   seperately in one file per query.
   Input: data/metadata_model_25/ data/documents_model_25/ data/topics_tf data/valid_uids.txt
   Output: data/metadata_scores/ data/documents_scores/
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include<bits/stdc++.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_topics_tf = "data/topics_tf/";
const string base_documents_model = "data/documents_model_25/";
const string base_metadata_model = "data/metadata_model_25/";
const string base_documents_scores = "data/documents_scores/";
const string base_metadata_scores = "data/metadata_scores/";

// score per query
double score(unordered_map<string, int> query, unordered_map<string, double> data){
    double result = 0;
    for (auto &q : query){
        if (data.find(q.first) != data.end()){
            result += q.second * data.at(q.first);        
    }
    return result;
}

// retrieve all queries
vector<unordered_map<string, int>> get_queries(){
    vector<unordered_map<string, int>> result;
    for(int i = 0; i < 50; i++){
        unordered_map<string, int> query = read_map_file(base_topics_tf + to_string(i+1) + ".txt");
        result.push_back(query);
    }
    return result;        
}

// processs the queries
void process_queries(vector<string> uids, vector<unordered_map<string, int>> queries){
    int total = uids.size();
    int checkpoint = total / 100;
    vector <string> query_results_documents[50];
    vector <string> query_results_metadata[50];
    for (int i = 0; i < total; i++)
    {
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, double> document = read_map_file_double(base_documents_model + uids[i] + ".txt");
        unordered_map<string, double> metadata = read_map_file_double(base_metadata_model + uids[i] + ".txt");
        for(int j = 0; j < queries.size(); j++){
            double document_score = score(queries[j], document);
            double metadata_score = score(queries[j], metadata);
            query_results_documents[j].push_back(to_string(document_score));
            query_results_metadata[j].push_back(to_string(metadata_score));
        }
    }
    cout << "Saving results" << endl;
    for(int i = 0; i < queries.size(); i++){
        write_file(query_results_metadata[i], base_metadata_scores + to_string(i+1) + ".txt");
        write_file(query_results_documents[i], base_documents_scores + to_string(i+1) + ".txt");
    }    
}

int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Retrieving queries" << endl;
    vector<unordered_map<string, int>> queries = get_queries();
    cout << "Processing queries" << endl;
    process_queries(uids, queries);
    return 0;
}