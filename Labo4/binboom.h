#include <cstdlib>
#include <iostream>
#include <cassert>
#include <stack>
#include <functional>
#include <memory>
#include <queue>

using namespace std;

template <class T>
class Binboom;

template <class T>
class Binknoop;

template<class T>
using Binknoopptr = std::unique_ptr<Binknoop<T> >;

template <class T>
class Binboom : public Binknoopptr<T> {
public:

    //overname constructoren van unique_ptr
    using std::unique_ptr<Binknoop<T>>::unique_ptr;

    friend istream& operator>>(istream& is, Binboom<T>& bb) {
        return bb.lees(is);
    }

    friend ostream& operator<<(ostream& os, const Binboom<T>& bb) {
        return bb.schrijflevelorder(os);
    }
    //schrijf schrijft uit in een vorm die min of meer menselijk leesbaar is
    ostream& schrijf(ostream&);
    int aantalSleutels() const;
    istream& lees(istream&);
    //schrijflevelorder schrijft uit in een vorm die door lees(...) kan gelezen worden.
    ostream& schrijflevelorder(ostream& os) const;
private:
};

template <class T>
class Binknoop {
    friend class Binboom<T>;
public:

    Binknoop<T>(const T& _sl) : sl(_sl) {
    }
private:
    T sl;
    Binboom<T> links, rechts;
};

//template<class T>
//istream& Binboom<T>::lees(istream& is) {
//
//}

template<class T>
int Binboom<T>::aantalSleutels() const {
    if (! * this)
        return 0;
    else
        return (*this)->links.aantalSleutels()+(*this)->rechts.aantalSleutels() + 1;
}

template<class T>
ostream& Binboom<T>::schrijflevelorder(ostream& os) const {
    if ((*this)) {
        os << aantalSleutels() << endl;
        queue<Binknoop<T> * > ATW; //Af Te Werken knopen
        ATW.push(this->get());
        int kindnr = 1;
        Binknoop<T>* nuknoop = *ATW.front();
        while (nuknoop != 0) {
            os << nuknoop->sl << ' ';
            if (!nuknoop->links)
                os << "-1 ";
            else {
                os << kindnr++ << ' ';
                ATW.push(nuknoop->links.get());
            }
            if (!nuknoop->rechts)
                os << "-1\n";
            else {
                os << kindnr++ << '\n';
                ATW.push(nuknoop->rechts.get());
            }
            ATW.pop();
            if (ATW.front() != 0)
                nuknoop = *ATW.front();
            else
                nuknoop = 0;
        }
    }
}

template<class T>
ostream& Binboom<T>::schrijf(ostream& os) {
    if ((*this) != 0) {
        os << "sleutel: " << (*this)->sl << " linkerkind: ";
        if ((*this)->links)
            os << (*this)->links->sl;
        else
            os << "(geen)";
        os << " rechterkind: ";
        if ((*this)->rechts)
            os << (*this)->rechts->sl;
        else
            os << "(geen)";
        os << endl;
        (*this)->links.schrijf(os);
        (*this)->rechts.schrijf(os);
    }
    return os;
}
