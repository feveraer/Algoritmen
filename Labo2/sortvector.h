#ifndef __SORTVECTOR
#define __SORTVECTOR
/**
 \class sortvector
 \brief is een klasse van sorteerbare vectoren
 Bovenop de vectoreigenschappen zijn er hulpfuncties om sorteervergelijkingen
 te vergemakkelijken.
 */
#include <iostream>
using std::istream;
using std::ostream;
using std::move;
using std::swap;
#include <iomanip>   // voor setw
#include <cstdlib>   // voor rand - opletten!! 
#include <vector>
#include <algorithm>

using std::vector;

template<class T>
class Sortvector : public vector<T> {
public:

    /// \fn Constructor: het argument geeft de grootte aan
    /// bij constructie zal de tabel opgevuld worden met
    /// n verschillende Ts in random volgorde
    /// (zie hulplidfuncties)
    Sortvector(int);

    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    /// \fn vul_range vul vector met de waarden T(0)...T(size()-1) in volgorde
    void vul_range();
    void draai_om();
    void vul_omgekeerd();
    void shuffle();
    void vul_random_zonder_dubbels();
    void vul_random(); //< nog niet implementeren

    bool is_gesorteerd() const;
    /// \fn is_range controleert of *this eruit ziet als het resultaat van vul_range(), d.w.z.
    /// dat, voor alle i, (*this)[i]==T(i);
    bool is_range() const;

    int aantal_inversies() const;
    int sort_and_count_inversions();

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s) {
        s.schrijf(os);
        return os;
    }

private:
    void schrijf(ostream & os)const;
    int topdown_split_and_count(Sortvector<T> &h, int l, int r, Sortvector<T> &v, bool resultInV) const;
    int merge_and_count(Sortvector<T> &v, int l, int m, int r, Sortvector<T> &h) const;

};

template <class T>
void Sortvector<T>::schrijf(ostream & os)const {
    for (auto&& t : * this) {
        os << t << " ";
    }
    os << "\n";
}

template <class T>
Sortvector<T>::Sortvector(int n) : vector<T>(n) {
    // het argument geeft de grootte aan
    // bij constructie zal de tabel opgevuld worden met
    // n verschillende Ts in random volgorde
    // (zie hulplidfuncties)

    // vector geïnitialiseerd met grootte n
}

template <class T>
void Sortvector<T>::vul_range() {
    for (int i = 0; i < this->size(); i++) {
        // move operator called, want compiler ziet T(i) als r-value
        (*this)[i] = T(i);
    }
}

template <class T>
void Sortvector<T>::draai_om() {
    std::reverse(this->begin(), this->end());
}

template <class T>
void Sortvector<T>::vul_omgekeerd() {
    for (int i = this->size() - 1; i >= 0; i--) {
        // move operator called, want compiler ziet T(i) als r-value
        (*this)[i] = T(i);
    }
}

/**
 * Shuffle methode gebaseerd op Fisher Yates
 * To shuffle an array a of n elements (indices 0..n-1):
 *    for i from n − 1 down to 1 do
 *        j ← random integer with 0 ≤ j ≤ i
 *        exchange a[j] and a[i]
 *
 * NOTE: http://www.cplusplus.com/reference/cstdlib/RAND_MAX/ rand limit = 32767
 */
template <class T>
void Sortvector<T>::shuffle() {
    for (int i = this->size() - 1; i > 0; --i) {
        int r1 = rand();
        int r2 = rand();
        std::swap((*this)[i], (*this)[(r1 + RAND_MAX * r2) % (i + 1)]);
    }
}

template <class T>
void Sortvector<T>::vul_random_zonder_dubbels() {
    vul_range();
    shuffle();
}

template <class T>
bool Sortvector<T>::is_gesorteerd() const {
    for (int i = 1; i < this->size(); i++) {
        if ((*this)[i - 1] > (*this)[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool Sortvector<T>::is_range() const {
    for (int i = 0; i < this->size(); i++) {
        if ((*this)[i] != i) {
            return false;
        }
    }
    return true;
}

// Naïeve implementatie: O(n²).
// Voor elk element, tel aantal elementen die rechts ervan liggen en kleiner zijn,
// geef totaal terug.

template <class T>
int Sortvector<T>::aantal_inversies() const {
    int aantal_inv = 0;
    for (int i = 0; i < this->size() - 1; i++) {
        for (int j = i + 1; j < this->size(); j++) {
            if ((*this)[i] > (*this)[j]) {
                aantal_inv++;
            }
        }
    }
    return aantal_inv;
}

// Verdeel-en-heers implementatie: O(n log(n)).
// Opm.: methode niet const, want vector van huidig object dient
// gemanipuleerd te worden.

template <class T>
int Sortvector<T>::sort_and_count_inversions() {
    Sortvector<T> h(this->size());
    return topdown_split_and_count(h, 0, this->size(), *this, true);
}

template <class T>
int Sortvector<T>::topdown_split_and_count(Sortvector<T>& h, int l, int r, Sortvector<T>& v,
        bool resultInV) const {
    if (l < r - 1) {
        int m = l + (r - l) / 2;
        int x = topdown_split_and_count(h, l, m, v, !resultInV);
        int y = topdown_split_and_count(h, m, r, v, !resultInV);
        int z;
        if (!resultInV) {
            z = merge_and_count(v, l, m, r, h);
        } else {
            z = merge_and_count(h, l, m, r, v);
        }
        return x + y + z;
    } else if (l == r - 1) {
        if (!resultInV) {
            h[l] = move(v[l]);
        }
        return 0;
    } else {
        return 0;
    }
}

template <class T>
int Sortvector<T>::merge_and_count(Sortvector<T>& v, int l, int m, int r, Sortvector<T>& h) const {
    int i = l, j = m, inv_count = 0;

    // zolang er elementen zijn in linker of rechter delen
    for (int k = l; k < r; k++) {
        // als i uit linker deel bestaat en <= j van rechter deel
        if (i < m && (j >= r || v[i] <= v[j])) {
            h[k] = v[i];
            i++;
        } else {
            h[k] = v[j];
            j++;
            // elke keer element uit rechter deel kleiner blijkt
            // dan alle overblijvende elementen uit linker, verhoog
            // aantal inversies teller met aantal overblijvende elementen
            // uit linker deel
            inv_count += (m - i);
        }
    }
    return inv_count;
}

#endif