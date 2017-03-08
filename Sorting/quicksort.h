/*

 */

/* 
 * File:   quicksort.h
 * Author: Frederic
 *
 * Created on 8 maart 2017, 8:11
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <vector>

using namespace std;

/**
 * Quicksort implementation with left element as pivot.
 * Partitions vector so that all elements smaller than the pivot come
 * before the pivot, while all elements greater than the pivot come after it.
 * Then recursively apply above partitioning for both parts.
 * @param v
 * @param l
 * @param r
 */
template<typename T>
void quicksort(vector<T> &v, int l, int r) {
    if (l < r) {
        // choose left element as pivot
        T pivot = v[l];
        int i = l, j = r;
        // decrease right index as long as element at that index is
        // bigger than pivot
        while (v[j] > pivot) {
            j--;
        }
        while (i < j) {
            // v[j] is smaller or equal to pivot, swap with v[i]
            swap(v[i], v[j]);
            i++;
            // find next index for i where its element is equal to or bigger
            // than pivot
            while (v[i] < pivot) {
                i++;
            }
            j--;
            // find next index for j where its element is equal to or smaller
            // than pivot
            while (v[j] > pivot) {
                j--;
            }
        }
        // recursive sort v[l..j]
        quicksort(v, l, j);
        // recursive sort v[j+1..r]
        quicksort(v, j + 1, r);
    }
}

template<typename T>
void quicksort(vector<T> &v) {
    quicksort(v, 0, v.size() - 1);
}

#endif /* QUICKSORT_H */

