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
//    Sortvector<int> sortvector(50);
//    sortvector.vul_random_zonder_dubbels();

    //cout << "Is range? " << sortvector.is_range() << "\n";
//    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";

//    STLSort<int> stl_sort;
//    stl_sort(sortvector);
    // InsertionSort<IntString> insertion_sort;
    // insertion_sort(sortvector);

    //    InsertionSort<int> insertion_sort;
    //    insertion_sort(sortvector);

//    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
//
//    cout << "STL sort:\n";
//    stl_sort.meet(100, 100000000, cout);

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

    // STL sort results:
    //      length                random  gesorteerd      omgekeerd
    //       100               0               0               0
    //      1000               0               0               0
    //     10000           0.015               0               0
    //    100000           0.038           0.016           0.015
    //   1000000           0.377            0.21           0.214
    //  10000000           4.231           2.567           2.596
    // 100000000          48.324          28.754          28.856

    //    sortvector.vul_random_zonder_dubbels();
    //    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    //    
    //    ShellSort<int> shellsort;
    //    shellsort(sortvector);
    //    
    //    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    //    
    //    cout << "Shellsort:\n";
    //    shellsort.meet(10, 10000, cout);
    
    Sortvector<int> sortvector(20);
    sortvector.vul_random_zonder_dubbels();
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    cout << sortvector << std::endl;
    
    cout << "Aantal inversies: " << sortvector.geef_aantal_inversies() << std::endl;
    
    MergeSort<int> mergesort;
    mergesort(sortvector);
    
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    cout << sortvector << std::endl;
    
    //mergesort.meet(10, 1000000, cout);

    return 0;
}

