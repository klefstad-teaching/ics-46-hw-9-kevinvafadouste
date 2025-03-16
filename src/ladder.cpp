#include "ladder.h"
#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <string>

using namespace std;

void load_words(set<string> &word_list, const string &file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    
    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff++;
            if (diff > d) return false;
            if (len1 > len2) i++;
            else if (len2 > len1) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return diff + abs(len1 - i) + abs(len2 - j) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
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
        return;
    }
    cout << "Word ladder found: ";
    for (const auto& word : ladder)
        cout << word << " ";
    cout << endl;
}

