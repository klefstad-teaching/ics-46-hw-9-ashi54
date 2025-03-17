#include "ladder.h"
#include <unordered_set>
#include <stack>

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

/*
void error(string word1, string word2, string msg);
*/
void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " [" << word1 << " -> " << word2 << "]" << endl;
}


bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    int diff_count = 0, i = 0, j = 0;
    
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (diff_count > d) return false;
            if (len1 > len2) i++; // Deletion case
            else if (len1 < len2) j++; // Insertion case
            else { i++; j++; } // Substitution case
        } else {
            i++; j++;
        }
    }
    
    return (diff_count <= d);
}


/*
bool is_adjacent(const string& word1, const string& word2);
*/

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
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
