#ifndef __INTSTRING_H
#define __INTSTRING_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
using std::string;

/** \class Intstring
 \brief stringklasse met een constructor die een getal gebruikt
 overerving van string is veilig: er worden geen extra gegevensvelden toegevoegd.
 */

class IntString : public string {
public:

    IntString(int a = 0) : string("0000000000") {
        int modulo = 1000000000;
        for (int i = 0; i < 10; i++) {
            this->operator[](i) = '0' + a / modulo;
            a = a % modulo;
            modulo /= 10;
        }

    };
};

#endif