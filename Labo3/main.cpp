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
#include <time.h>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {

    // OEFENING 1: Welke groep anagrammen is het grootst? 
    // Welke paar anagrammen is het langst?

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

    cout << "\nLargest anagram\n";

    cout << max_size_anagram << "\n";
    cout << anagram_pairs[pos_largest_anagram].first << "\n";

    in.close();


    // OEFENING 2: Verander de tekst door, als er voor een woord in de tekst 
    // een anagram zit in de woordenlijst, het woord te vervangen door een van de 
    // anagrammen. Kies elke keer random een vervanging uit de mogelijkheden.

    ifstream in2("TimErwetenKoerst.txt");
    ofstream output_file;
    srand(time(NULL));
    string line;

    output_file.open("TimErwetenKoerst_out.txt");
    while (getline(in2, line)) {
        stringstream line_stream(line);
        string word;
        while (line_stream >> word) {
            string s_word = word;
            sort(s_word.begin(), s_word.end());
            // iterator to first found anagram
            vector<pair<string, string>>::iterator it_first =
                    find_if(anagram_pairs.begin(), anagram_pairs.end(),
                    [&](pair<string, string> const & ref) {
                        return ref.first == s_word; });
            // reverse iterator to last found anagram
            vector<pair<string, string>>::reverse_iterator it_last =
                    find_if(anagram_pairs.rbegin(), anagram_pairs.rend(),
                    [&](pair<string, string> const & ref) {
                        return ref.first == s_word; });
            // if anagram found, write random anagram to file
            if (it_first != anagram_pairs.end()) {
                // cout << it->second << "\n";
                // choose first anagram associated with found word
                // output_file << it->second << " ";

                // choose random anagram
                int lower_bound = it_first - anagram_pairs.begin();
                int upper_bound = it_last.base() - anagram_pairs.begin();
                int random_index = lower_bound + (rand() * (upper_bound - lower_bound) / RAND_MAX);
                output_file << anagram_pairs[random_index].second << " ";
            } else {
                // anagram not found, write same word to file
                output_file << word << " ";
            }
        }
        output_file << "\n";
    }
    output_file.close();
    in2.close();

    return 0;
}

