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
#include "sortvector.h"
#include "sorteermethode.h"

using namespace std;



/*
 * 
 */
int main() {
    Sortvector<int> sortvector(50);
    sortvector.vul_random_zonder_dubbels();
    
    //cout << "Is range? " << sortvector.is_range() << "\n";
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    
//    STLSort<int> stl_sort;
//    stl_sort(sortvector);
    InsertionSort<int> insertion_sort;
    insertion_sort(sortvector);
    
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    
    insertion_sort.meet(10,100000,cout);
    
    return 0;
}

