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

using namespace std;



/*
 * 
 */
int main() {
    Sortvector<int> sortvector(50);
    sortvector.vul_range();
    
    cout << "Is range? " << sortvector.is_range() << "\n";
    cout << "Is gesorteerd? " << sortvector.is_gesorteerd() << "\n";
    
    sortvector.draai_om();
    
    
    return 0;
}

