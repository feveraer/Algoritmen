/*

 */

/* 
 * File:   heapsort.h
 * Author: Frederic
 *
 * Created on 28 februari 2017, 21:22
 */

#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstdlib>
#include <vector>

using namespace std;

// position of parent of node i

int i_parent(int i) {
    return (i - 1) / 2;
}

// position of left child of node i

int i_left_child(int i) {
    return 2 * i + 1;
}

// position of right child of node i

int i_right_child(int i) {
    return 2 * i + 2;
}


/**
 * Repair the heap whose root element is at index start, assuming the heaps
 * rooted at its children are valid.
 * Complexity: O(n).
 * @param v
 * @param start
 * @param end
 */
template<typename T>
void sift_down(vector<T> &v, int start, int end) {
    int root = start;

    // while the root has at least one child and its index isn't greater than
    // the end index
    while (i_left_child(root) <= end) {
        int child = i_left_child(root);
        // keeps track of child to swap with
        int pos_child_to_swap = root;

        if (v[pos_child_to_swap] < v[child]) {
            pos_child_to_swap = child;
        }
        // if there is a right child and that child is greater
        if (child + 1 <= end && v[pos_child_to_swap] < v[child + 1]) {
            pos_child_to_swap = child + 1;
        }
        // The root holds the largest element. Since we assume the heaps 
        // rooted at the children are valid, this means that we are done.
        if (pos_child_to_swap == root) {
            // by assigning root to end + 1, the loop will stop
            root = end + 1;
        } else {
            swap(v[root], v[pos_child_to_swap]);
            root = pos_child_to_swap;
        }
    }
}

/**
 * Put elements of v in heap order, in-place.
 * @param v
 */
template<typename T>
void heapify(vector<T> &v) {
    // start is assigned to the index in v of the last parent node
    int start = i_parent(v.size() - 1);

    while (start >= 0) {
        // sift down the node at index start to the proper place such that
        // all nodes below the start index are in heap order
        sift_down(v, start, v.size() - 1);
        // next parent node
        start--;
    }
}

template<typename T>
void heapsort(vector<T> &v) {
    // build heap in vector v so that largest value is at the root
    heapify(v);
    for (int i = v.size() - 1; i > 0; i--) {
        swap(v[i], v[0]);
        // swap ruined heap property, so restore it (to find next largest element)
        // the end index is i - 1, because element at 
        // index i was just put in its right place
        sift_down(v, 0, i - 1);
    }
}

#endif /* HEAPSORT_H */
