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
    // boundary condition if both the words are the same
    if (word1 == word2) return true; 
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

    queue<vector<string>> ladder_queue;  // BFS queue stores paths (vectors)
    unordered_set<string> visited;       // Track visited words

    ladder_queue.push({start});
    visited.insert(start);  // Mark start word as visited immediately

    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        unordered_set<string> level_visited; // Track words visited in this level

        for (int i = 0; i < level_size; i++) {
            vector<string> current_ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = current_ladder.back();

            for (const string& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end) {
                        return new_ladder; // Found the shortest ladder
                    }

                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }

        // Only mark words as visited after finishing the entire level
        visited.insert(level_visited.begin(), level_visited.end());
    }

    return {};  // No word ladder found
}


// Print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i != ladder.size() - 1) cout << " ";
    }
    cout << "\n";
}

void verify_word_ladder(const vector<string>& ladder, const set<string>& word_list) {
    if (ladder.empty()) {
        cout << "Invalid: Empty ladder." << endl;
        return;
    }

    for (size_t i = 1; i < ladder.size(); i++) {
        if (!is_adjacent(ladder[i - 1], ladder[i])) {
            cout << "Invalid word ladder: " << ladder[i - 1] << " -> " << ladder[i] << " is not adjacent." << endl;
            return;
        }
        if (word_list.find(ladder[i]) == word_list.end()) {
            cout << "Invalid word ladder: " << ladder[i] << " is not in the dictionary." << endl;
            return;
        }
    }

    cout << "Valid word ladder!" << endl;
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
