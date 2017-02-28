/*

 */

/* 
 * File:   main.cpp
 * Author: Frederic
 *
 * Created on 14 februari 2017, 22:23
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include "heapsort.h"

using namespace std;

// compiler C++11 ondersteuning: voeg -std=c++11 toe als option

/**
 * Selection sort:
 * - best case:     O(n²)
 * - average case:  O(n²)
 * - worst case:    O(n²)
 * - is not stable
 * - rarely used, unless number of swaps need to be low
 * @param v
 */
template<typename T>
void selection_sort(vector<T> &v) {
    for (int i = v.size() - 1; i > 0; i--) {
        // zoek plaats van maximum
        int imax = i;
        for (int j = 0; j < i; j++) {
            if (v[j] > v[imax]) {
                imax = j;
            }
        }
        // wissel maximum om met huidige positie in iteratie
        swap(v[i], v[imax]);
    }
}

/**
 * Shellsort:
 * - best case:     O(n log n)
 * - average case:  depends on increment sequence: Sedgewick gives O(n^(7/6))
 * - worst case:    depends: Sedgewick gives O(n^(4/3))
 * - is not stable
 * @param v
 */
template<typename T>
void shellsort(vector<T> &v) {
    // originele incrementen van Shell (n/2, n/4, ..., 1)
    int k = v.size() / 2;
    // start met grootste increment, ga door tot k = 1
    while (k >= 1) {
        // insertion sort voor k
        // eerste elementen v[0..k-1] staan al in volgorde
        for (int i = k; i < v.size(); i++) {
            T h = move(v[i]);
            int j = i - k;
            while (j >= 0 && h < v[j]) {
                v[j + k] = move(v[j]);
                j -= k;
            }
            v[j + k] = move(h);
        }
        // volgend increment
        k /= 2;
    }
}


/**
 * Insertion sort:
 * - best case:     O(n)
 * - average case:  O(n²)
 * - worst case:    O(n²)
 * - is stable
 * @param v
 */
template<typename T>
void insertion_sort(vector<T> &v) {
    for (int i = 1; i < v.size(); i++) {
        // v[i] toegewezen aan h, v[i] is nu leeg
        T h = move(v[i]);
        int j = i - 1;
        // itereer over alle waarden links van h (= v[i])
        while (j >= 0 && h < v[j]) {
            // als h kleiner is dan v[j], schuif v[j] 1 plaats naar rechts
            // in v, v[j] is nu leeg
            v[j + 1] = move(v[j]);
            j--;
        }
        // plaats h terug in v op achtergelaten plaats
        v[j + 1] = move(h);
    }
}

int main() {
    vector<int> v = {8, 5, 3, 9, 1, 15, 2};
    //insertion_sort(v);
    //shellsort(v);
    //selection_sort(v);
    heapsort(v);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    return 0;
}

