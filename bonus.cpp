/* This program gives a bonus factor to the similar 
   documents of the top 20 retrieved and updates the ranking
   Input: data/rankings/unfiltered.txt data/valid_uids.txt data/sim/
   Output: results/
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <bits/stdc++.h>
#include "io.h"

using namespace std;

const string base_valid_uids = "data/valid_uids.txt";
const string base_ranking_result = "data/rankings/unfiltered.txt";
const string base_rankings = "data/sim/top20";
const string base_results = "results/";

bool sortbysec(const pair<string,double> &a, const pair<string,double> &b) { 
    return (a.second > b.second); 
} 

void process(vector<string> uids, double factor){
    int total = uids.size();
    string name = "ranking_b25_md3961_top20_bonus";
    string filename = name + to_string(int(factor*100));
    vector<string> rankings = read_file(base_ranking_result);
    vector<string> results;
    for(int c=0; c<50; c++){
        int start = c * total;
        int stop = start + total;
        cout << "Collect results from " <<  start << " to " << stop << endl;
        vector<string> candidates;
        vector<double> scores;
        string word;
        int index;
        for(int i = start; i < stop; i++){
            istringstream ss(rankings[i]);
            index = 0;
            while(ss >> word){
                if (index == 2)
                    candidates.push_back(word);
                if (index == 4)
                    scores.push_back(atof(word.c_str()));
                index++;
                index %= 6;
            }
        }
        vector<string> f1 = read_file(base_rankings + to_string(c+1) + ".txt");
        vector<int> friends;
        for(int i = 0; i < f1.size(); i++)
            friends.push_back(stoi(f1[i]));
        cout << "Factoring results of friends" << endl;
        cout << friends.size() << endl;
        for(int i = 0; i < friends.size(); i++)
            scores[friends[i]] *= factor;
        cout << "Adding results to list and sort them again" << endl;
        vector < pair <string, double>> query_results;
        for(int j = 0; j < total; j++)
            query_results.push_back(make_pair(candidates[j], scores[j]));
        cout << "Sorting results" << endl;
        sort(query_results.begin(), query_results.end(), sortbysec);
        cout << "Saving results" << endl;
        for (int j = 0; j < 1000; j++)
             results.push_back(to_string(c+1) + " 0 " + query_results[j].first + " " + to_string(j+1) + " " + to_string(query_results[j].second) + " " + name);
    }
    write_file(results, base_results + filename + ".txt");
}


int main()
{
    string input;
    cout << "Give the factor" << endl;
    cin >> input;
    double factor = atof(input.c_str());
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Retrieving document lenghts" << endl;
    process(uids, factor);
    return 0;
}