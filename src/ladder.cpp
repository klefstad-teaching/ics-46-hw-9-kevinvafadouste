#include "ladder.h"
#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <string>

using namespace std;

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.length(), len2 = word2.length();
    if (abs(len1 - len2) > 1) 
      return false;
    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            diff++;
            if (diff > 1) return false;
            if (len1 > len2) i++;
            else if (len2 > len1) j++;
            else { 
                i++; 
                j++; 
            }
        } 
        else
            i++; 
            j++;
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) 
                  return new_ladder;
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for (const auto& word : ladder)
        cout << word << " -> ";
    cout << "end" << endl;
}

