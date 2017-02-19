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

using namespace std;

template<typename T>
void insertion_sort(vector<T> &v) {
    for (int i = 1; i < v.size(); i++) {
        // v[i] toegewezen aan h, v[i] is nu leeg
        T h = move(v[i]);
        int j = i - 1;
        // itereer over alle waarden links van h (v[i])
        while (j >= 0 && h < v[j]) {
            // als h kleiner is dan v[j], schuif v[j] 1 plaats naar rechts
            // in v, v[j] is nu leeg
            v[j+1] = move(v[j]);
            j--;
        }
        // plaats h terug in v op achtergelaten plaats
        v[j+1] = move(h);
    }
}

int main() {
    vector<int> v = {8, 5, 3, 9, 1, 15, 2};
    insertion_sort(v);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    return 0;
}

