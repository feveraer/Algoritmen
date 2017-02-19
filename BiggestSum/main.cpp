
/* 
 * File:   main.cpp
 * Author: Frederic
 *
 * Created on 14 februari 2017, 21:21
 */

#include <iostream>
using namespace std;

int get_biggest_sum(int* arr, int size) {
    if (size > 0) {
        int sum = arr[0] > 0 ? arr[0] : 0;
        int biggest_sum = sum;
        for (int i = 1; i < size; i++) {
            if (sum + arr[i] > 0) {
                sum += arr[i];
            }
            else {
                sum = 0;
            }

            if (sum > biggest_sum) {
                biggest_sum = sum;
            }
        }
        return biggest_sum;
    }
    else
        return 0;
}

int main() {
    const int SIZE = 8;
    int arr[SIZE] = { 3, 1, -5, 2, 4, -3, 5, -10 };

    int s = get_biggest_sum(arr, SIZE);
    cout << "Biggest sum was: " << s << endl;
    return 0;
}

