#include "ladder.h"
#include <iostream>
#include <set>
#include <fstream>

using namespace std;

void load_words(set<string> &word_list, const string &file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening: " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word)
        word_list.insert(word);
    file.close();
}

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    string start_word, end_word;
    cin >> start_word;
    cin >> end_word;
    if (start_word == end_word)
        return 1;
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    return 0;
}

