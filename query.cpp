/* This program calculates the inner product of the query
   per document and then saves the top 1000 scores of each 
   topic in one file, which can be evaluated by the trec tool
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include<bits/stdc++.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_topics_tf = "data/topics_tf/";
const string base_rankings = "data/rankings/";
const string base_documents_model = "data/documents_model_";
const string base_metadata_model = "data/metadata_model_";

bool sortbysec(const pair<string,double> &a, const pair<string,double> &b) { 
    return (a.second > b.second); 
} 

// score per query
double score(unordered_map<string, int> query, unordered_map<string, double> data){
    double result = 0;
    for (auto &q : query){
        if (data.find(q.first) != data.end()){
            result += q.second * data.at(q.first);
        }             
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
void process_queries(vector<string> uids, string name, int model, vector<unordered_map<string, int>> queries){
    double weight_metadata = 0.39;
    double weight_document = 0.61;
    int total = uids.size();
    int checkpoint = total / 100;
    vector < pair <string, double>> query_results[50];
    for (int i = 0; i < total; i++)
    {
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        unordered_map<string, double> document = read_map_file_double(base_documents_model + to_string(model) + "/" + uids[i] + ".txt");
        unordered_map<string, double> metadata = read_map_file_double(base_metadata_model + to_string(model) + "/" + uids[i] + ".txt");
        for(int j = 0; j < queries.size(); j++){
            double document_score = score(queries[j], document) * weight_document;
            double metadata_score = score(queries[j], metadata) * weight_metadata;
            double score = document_score + metadata_score;
            query_results[j].push_back(make_pair(uids[i], score));
        }
    }
    cout << "Sorting results" << endl;
    for(int i = 0; i < queries.size(); i++)
        sort(query_results[i].begin(), query_results[i].end(), sortbysec);
    cout << "Saving results" << endl;
    vector<string> results;
    for(int i = 0; i < queries.size(); i++){
        for (int j = 0; j < 1000; j++)
             results.push_back(to_string(i+1) + " 0 " + query_results[i][j].first + " " + to_string(j+1) + " " + to_string(query_results[i][j].second) + " " + name);
    }
    write_file(results, base_rankings + name + ".txt");
}

int main()
{
    int model = 25;
    string name;
    cout << "Give a name for this run" << endl;
    cin >> name;
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Retrieving queries" << endl;
    vector<unordered_map<string, int>> queries = get_queries();
    cout << "Processing queries" << endl;
    process_queries(uids, name, model, queries);
    return 0;
}