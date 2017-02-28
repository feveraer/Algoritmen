/*

 */

/* 
 * File:   main.cpp
 * Author: Frederic
 *
 * Created on 22 februari 2017, 9:15
 */

#include <iostream>
#include <cstdlib>
#include "intstring.h"
#include "sortvector.h"
#include "sorteermethode.h"

using namespace std;

/*
 * 
 */
int main() {
    //Sortvector<IntString> sortvector(50);
    Sortvector<int> sortvector(50);
    sortvector.vul_random_zonder_dubbels();

    //cout << "Is range? " << sortvector.is_range() << "\n";
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";

    //    STLSort<int> stl_sort;
    //    stl_sort(sortvector);
    // InsertionSort<IntString> insertion_sort;
    // insertion_sort(sortvector);

    InsertionSort<int> insertion_sort;
    insertion_sort(sortvector);

    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";

    cout << "Insertion sort:\n";
    insertion_sort.meet(10, 10000, cout);

    // results with IntStrings:
    //  length                random  gesorteerd      omgekeerd
    //        10               0               0               0
    //       100               0               0               0
    //      1000            0.03           0.001               0
    //     10000           2.983           0.004           0.005
    //    100000         304.686           0.044           0.047

    // results with ints:
    //  length                random  gesorteerd      omgekeerd
    //        10               0               0               0
    //       100               0               0               0
    //      1000           0.003               0               0
    //     10000           0.238               0               0
    //    100000          24.332           0.001           0.002

    sortvector.vul_random_zonder_dubbels();
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    
    ShellSort<int> shellsort;
    shellsort(sortvector);
    
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    
    cout << "Shellsort:\n";
    shellsort.meet(10, 10000, cout);
    
    return 0;
}

