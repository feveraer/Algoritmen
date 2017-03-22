/*

 */

/* 
 * File:   main.cpp
 * Author: Frederic
 *
 * Created on 22 maart 2017, 9:43
 */

#include <cstdlib>
#include <fstream>
#include "binboom.h"
#include <iostream>
#include <sstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    ifstream in("jacht.txt");
    string line;
    int lines_count = 0;
    int number_nodes;
    vector<Binboom < string>> nodes;

    while (getline(in, line)) {
        if (lines_count == 0) {
            number_nodes = atoi(line.c_str());
        } else {
            istringstream iss(line);
            string key;
            // first word is key
            iss >> key;
            nodes.emplace_back(new Binknoop<string>(key));
        }
        lines_count++;
    }

    in.close();

    return 0;
}

