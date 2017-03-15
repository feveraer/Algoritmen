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

int main(int argc, char** argv) {
    ifstream in("woordenlijst.txt");
    string word;

    vector<pair<string, string>> anagram_pairs;

    while (in >> word) {
        // copy word before sorting
        string sorted_word = word;
        sort(sorted_word.begin(), sorted_word.end());
        anagram_pairs.emplace_back(move(sorted_word), move(word));
    }

    sort(anagram_pairs.begin(), anagram_pairs.end());

    int number_groups_anagrams = 1;
    int max_number_groups_anagrams = number_groups_anagrams;
    string s_anagram = anagram_pairs[0].first;
    int pos_max_number_groups_anagrams;
    
    int pos_largest_anagram;
    int max_size_anagram = 0;
    for (int i = 1; i < anagram_pairs.size(); i++) {
        if (anagram_pairs[i].first == s_anagram) {
            number_groups_anagrams++;
            if (number_groups_anagrams > max_number_groups_anagrams) {
                max_number_groups_anagrams = number_groups_anagrams;
                pos_max_number_groups_anagrams = i - max_number_groups_anagrams + 1;
            }
            int size_anagram = anagram_pairs[i].first.size();
            if (size_anagram > max_size_anagram) {
                max_size_anagram = size_anagram;
                pos_largest_anagram = i;
            }
            
        } else {
            s_anagram = anagram_pairs[i].first;
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
    
    cout << "Largest anagram\n";
    
    cout << max_size_anagram << "\n";
    cout << anagram_pairs[pos_largest_anagram].first << "\n";

    return 0;
}

