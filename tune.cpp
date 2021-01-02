/* This program combines the score of the
   documents and metadata. It is created to tune 
   the factor of the scores.
   Input: data/metadata_scores/ data/documents_scores/ data/valid_uids.txt
   Output: data/rankings/
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include<bits/stdc++.h> 
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_rankings = "data/rankings/";
const string base_documents_scores = "data/documents_scores/";
const string base_metadata_scores = "data/metadata_scores/";

bool sortbysec(const pair<string,double> &a, const pair<string,double> &b) { 
    return (a.second > b.second); 
} 

// processs the queries
void process_queries(vector<string> uids, string name, double weight_metadata, double weight_document){
    cout << "Retrieving scores metadata" << endl;
    vector <string> query_results_metadata[50];
    for(int i = 0; i < 50; i++){
        query_results_metadata[i] = read_file(base_metadata_scores + to_string(i+1) + ".txt");
    }
    cout << "Retrieving scores documents" << endl;
    vector <string> query_results_documents[50];
    for(int i = 0; i < 50; i++){
        query_results_documents[i] = read_file(base_documents_scores + to_string(i+1) + ".txt");
    }
    cout << "Combining scores" << endl;
    int total = uids.size();
    int checkpoint = total / 100;
    vector < pair <string, double>> query_results[50];
    for (int i = 0; i < total; i++)
    {
        if (i % checkpoint == 0)
            cout << int(double(i)/total*100) << "%" << endl;
        for(int j = 0; j < 50; j++){
            double score =  atof(query_results_metadata[j][i].c_str()) * weight_metadata +  atof(query_results_documents[j][i].c_str()) * weight_document;
            query_results[j].push_back(make_pair(uids[i], score));
        }
    }
    cout << "Sorting results" << endl;
    for(int i = 0; i < 50; i++)
        sort(query_results[i].begin(), query_results[i].end(), sortbysec);
    cout << "Saving results" << endl;
    vector<string> results;
    for(int i = 0; i < 50; i++){
        for (int j = 0; j < 1000; j++)
             results.push_back(to_string(i+1) + " 0 " + query_results[i][j].first + " " + to_string(j+1) + " " + to_string(query_results[i][j].second) + " " + name);
    }
    write_file(results, base_rankings + name + ".txt");
}

int main()
{
    string m, d;
    cout << "Give the ratio for this run" << endl;
    cin >> m >> d;
    double weight_metadata = stoi(m) / 100.0; 
    double weight_documents = stoi(d) / 100.0; 
    string name = m+d;
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Processing queries" << endl;
    process_queries(uids, name, weight_metadata, weight_documents);
    return 0;
}