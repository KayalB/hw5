#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


string alphabet = "abcdefghijklmnopqrstuvwxyz";
// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
    // Add your code here
    std::set<string> possible_words;
    helper(in, floating, possible_words);
    std::set<string> valid_words;
    for(std::set<string>::iterator it = possible_words.begin(); it != possible_words.end(); it++){
        if(dict.find(*it) != dict.end()){
            valid_words.insert(*it);
        }
        // cout << *it << endl;
    }
    return valid_words;
}

void helper(
    const std::string& in,
    const std::string& floating,
    std::set<std::string>& possible
    )
{
    int next_blank = get_next_index(in, '-');
    if(next_blank == -1){
        possible.insert(in);
        return;
    }
    string reference_in = in;
    if(floating.size() != 0){
        char next_letter = floating[0];
        string new_floating = floating;
        new_floating.erase(0, 1);
        for(int i = 0; i < (int)in.size(); i++){
            string new_in = reference_in;
            // cout << in << ", in[i]: " << in[i] << ", i " << i << endl;
            if(in[i] == '-'){
                new_in[i] = next_letter;
                helper(new_in, new_floating, possible);
            }
        }
        return;
    }

    for(int i = 0; i < 26; i++){
        reference_in[next_blank] = alphabet[i];
        helper(reference_in, floating, possible);
    }
}

int get_next_index(const std::string& in, char letter){
    for(int i = 0; i < (int)in.size(); i++){
        if(in[i] == letter){
            return i;
        }
    }
    return -1;
}


// Define any helper functions here
