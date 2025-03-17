#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    string start, end;
    cout << "Enter the starting word: ";
    cin >> start;
    cout << "Enter the ending word: ";
    cin >> end;

    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);

    return 0;
}