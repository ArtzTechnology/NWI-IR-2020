/* This program find the most similar documents of the 
   top k results of all the topics.
   Input: data/metdata_model_25/ data/valid_uids.txt data/rankings/unfiltered.txt
   Output: data/sim/
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>
#include "io.h"

using namespace std;

const string base_metadata_model = "data/metadata_model_25/";
const string base_valid_uids = "data/valid_uids.txt";
const string base_ranking_result = "data/rankings/unfiltered.txt";
const string base_similarity = "data/sim/";

// score per query
double score(unordered_map<string, double> data1, unordered_map<string, double> data2){
    double result = 0;
    for (auto &d1 : data1){
        unordered_map<string, double>::const_iterator iter = data2.find(d1.first);
        if(iter != data2.end())
            result += d1.second * iter->second;
    }
    return result;
}

bool sortbysec(const pair<string,double> &a, const pair<string,double> &b) { 
    return (a.second > b.second); 
} 

int count_length(unordered_map<string, double> data){
    int result = 0;
    for (auto &d : data)
        result += d.second;
    return result;
}  

void process(vector<string> uids){
    int total = uids.size();
    string name = "top20";
    vector<string> rankings = read_file(base_ranking_result);
    int threshold = 25;
    int tops = 20;
    for(int c=0; c<50; c++){
        cout << "Query " << c+1 << endl;
        // step 1: save scores in vectors
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
        // Step 2: retrieve documents on order
        cout << "Retrieving documents" << endl;
        unordered_map<string, double> documents[62736];
        for(int i = 0; i < total; i++)
                documents[i]= read_map_file_double(base_metadata_model + candidates[i] + ".txt");
        // count lenghts 
        vector<int> lenghts;
        for(int i = 0; i < total; i++){
            lenghts.push_back(count_length(documents[i]));
        }
        vector<bool> abstract;
        for(int i = 0; i < total; i++){
            if(lenghts[i]>15)
                abstract.push_back(true);
            else
                abstract.push_back(false);
        }
        cout << "Calculating divisors" << endl;
        double divisors [62736];
        for(int i = 0; i < total; i++){
            if(abstract[i]){
                double result = 0;
                for (auto &d : documents[i])
                    result += pow(d.second, 2);
                divisors[i] = sqrt(result);
            }
        }
        cout << "Finding friends of top 20 candidates" << endl;
        double sim;
        vector<string> finals;
        vector<int> friends;
        for(int i = 0; i < tops; i++){
            if (abstract[i]){
                friends.push_back(i);
                for(int j=0; j < total; j++){
                    if(abstract[j] && i!=j ){
                        sim = score(documents[i], documents[j]) / (divisors[i] * divisors[j]);
                        if (sim * 100 > threshold){
                            friends.push_back(j);
                        }
                    }
                }   
            }
        }
    sort( friends.begin(), friends.end() );
    friends.erase( unique( friends.begin(), friends.end() ), friends.end() );
    for(int i = 0; i < friends.size(); i++)
        finals.push_back(to_string(friends[i]));
    write_file(finals, base_similarity + name + to_string(c+1) + ".txt");
    }
}


int main()
{
    cout << "Reading valid uids" << endl;
    vector<string> uids = read_file(base_valid_uids);
    cout << "Retrieving document lenghts" << endl;
    process(uids);
    return 0;
}