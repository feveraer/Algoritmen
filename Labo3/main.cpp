/*

 */

/* 
 * File:   main.cpp
 * Author: Frederic
 *
 * Created on 15 maart 2017, 9:19
 */

#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

bool sort_by_sec(const pair<string, string> &a,
        const pair<string, string> &b) {
    return (a.second < b.second);
}

int main(int argc, char** argv) {
    ifstream in("woordenlijst.txt");
    string word;

    vector<pair<string, string>> anagram_pairs;

    while (in >> word) {
        // copy word before sorting
        string sorted_word = word;
        sort(sorted_word.begin(), sorted_word.end());
        anagram_pairs.emplace_back(move(word), move(sorted_word));
    }

    sort(anagram_pairs.begin(), anagram_pairs.end(), sort_by_sec);

    int number_groups_anagrams = 1;
    int max_number_groups_anagrams = number_groups_anagrams;
    string s_anagram = anagram_pairs[0].second;
    int pos_max_number_groups_anagrams;
    for (int i = 1; i < anagram_pairs.size(); i++) {
        if (anagram_pairs[i].second == s_anagram) {
            number_groups_anagrams++;
            if (number_groups_anagrams > max_number_groups_anagrams) {
                max_number_groups_anagrams = number_groups_anagrams;
                pos_max_number_groups_anagrams = i - max_number_groups_anagrams + 1;
            }
        } else {
            s_anagram = anagram_pairs[i].second;
            number_groups_anagrams = 1;
        }
    }

    // grootste groep
    
    cout << max_number_groups_anagrams << "\n";

    for (int i = pos_max_number_groups_anagrams;
            i < pos_max_number_groups_anagrams + max_number_groups_anagrams;
            i++) {
        cout << anagram_pairs[i].first << ", " << anagram_pairs[i].second << "\n";
    }


    return 0;
}

