#include "ladder.h"
#include <unordered_set>
#include <stack>

string to_lower(const string& word) {
    string lower_word = word;
    for (char& c : lower_word) {
        c = tolower(c);
    }
    return lower_word;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Cannot open file " << file_name << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        word_list.insert(to_lower(word));
    }

    file.close();
}

bool is_adjacent(const string& word1, const string& word2) {
    /*
    ex.
    ashi vs adi
    a = a
    s != d (1 difference)
    h != i (2 difference)
    return false

    car vs cat
    c = c
    a = a
    r != t (1 difference)
    reutrn true
    */
    int lenFirst = word1.size();
    int lenSecond = word2.size();
    // checking if words differ by only 1 char 
    if (abs(lenFirst - lenSecond) > 1) return false;

    int differences = 0;
    int index1 = 0;
    int index2 = 0;

    while (index1 < lenFirst && index2 < lenSecond) {
        /*
        
        */
        if (word1[index1] != word2[index2]) {
            differences++;
            if (differences > 1) return false;

            // handling 3 cases: deletion, insertion, & replacement cases
            if (lenFirst > lenSecond) {
                /*
                aashi vs adhi
                a = a
                a != d
                aashi > adhi
                -> delete a
                */
                index1++; // deletion case
            } else if (lenFirst < lenSecond) {
                /*
                adhi vs aashi
                w2 longer
                move index 2
                */
                index2++; 
            } else {
                /*
                if both have same length, need to move both the pointers (+1)
                */
                index1++;
                index2++; 
            }
        } else {
            index1++;
            index2++;
        }
    }
    // if dif == 1 (correct), dif = 0 and the diff = 1 (correct) -> both return false
    return (differences == 1) || (differences == 0 && abs(lenFirst - lenSecond) == 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string start = to_lower(begin_word);
    string end = to_lower(end_word);

    if (start == end) {
        cout << "Error: Start and end words must be different." << endl;
        return {};
    }

    if (word_list.find(end) == word_list.end()) {
        cout << "Error: End word must be in the dictionary." << endl;
        return {};
    }

    queue<stack<string>> ladder_queue; // Queue of ladders (stored as stacks)
    set<string> visited; // Track visited words

    stack<string> initial_ladder;
    initial_ladder.push(start);
    ladder_queue.push(initial_ladder);
    visited.insert(start);

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> level_visited;

        for (int i = 0; i < level_size; i++) {
            stack<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.top();

            for (const string& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    stack<string> new_ladder = ladder;
                    new_ladder.push(word);

                    if (word == end) {
                        vector<string> result;
                        while (!new_ladder.empty()) {
                            result.insert(result.begin(), new_ladder.top());
                            new_ladder.pop();
                        }
                        return result; // Return the shortest ladder
                    }

                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }

        for (const string& word : level_visited) {
            visited.insert(word);
        }
    }

    return {}; // No ladder found
}


// Print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i != ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// Verify if a given word ladder is valid
void verify_word_ladder(const vector<string>& ladder, const set<string>& word_list) {
    if (ladder.empty()) {
        cout << "Invalid: Empty ladder." << endl;
        return;
    }

    for (size_t i = 1; i < ladder.size(); i++) {
        if (!is_adjacent(ladder[i - 1], ladder[i]) || word_list.find(ladder[i]) == word_list.end()) {
            cout << "Invalid word ladder!" << endl;
            return;
        }
    }

    cout << "Valid word ladder!" << endl;
}
