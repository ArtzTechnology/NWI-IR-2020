/* This program counts query frequencies
*  and saves these in data/topics_tf
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include "io.h"

using namespace std;

const string base_topics = "data/topics/";
const string base_topics_tf = "data/topics_tf/";

// count the term frequencies
unordered_map<string, int> term_frequencies(vector<string> terms){
    unordered_map<string, int> result;
    for (int i=0; i<terms.size(); i++)        
        result[terms[i]]++;
    return result;
}  

// count and save term frequencies
void process_term_frequencies(string in, string out)
{
    for (int i = 0; i < 50; i++)
    {
        vector<string> terms = read_file(in + to_string(i+1) + ".txt");
        unordered_map<string, int> tf = term_frequencies(terms);
        write_map_file(tf, out + to_string(i+1) + ".txt");
    }
}

int main()
{
    cout << "Processing topics" << endl;
    process_term_frequencies(base_topics, base_topics_tf);
    return 0;
}