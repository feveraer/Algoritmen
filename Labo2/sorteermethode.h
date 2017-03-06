#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE
#include "sortvector.h"
#include "chrono.h"
#include <iostream>
using std::move;
using std::swap;
using std::endl;
using std::cout;
#include <algorithm>
#include <deque>   // voor sort()-methode uit STL
#include "csv.h"

/** class Sorteermethode
    \brief abstracte klasse van methodes die een vector sorteren
 */
template <typename T>
class Sorteermethode {
public:
    /// \fn operator() sorteert de vector gegeven door het argument
    virtual void operator()(vector<T> & v) const = 0;

    /// \fn meet(int kortste, int langste, ostream& os) schrijft naar os een overzicht (met de nodige ornamenten)
    /// met de snelheid van de opgegeven sorteermethode *this. Er wordt 1 lijn uitgedrukt voor elke mogelijke
    /// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
    /// enzovoorts, tot aan grootste.
    /// Op een lijn staat de snelheid van de methode toegepast op
    /// (1) een random tabel
    /// (2) een al gesorteerde tabel.
    /// (3) een omgekeerd gesorteerde tabel.

    /// Deze functie werkt alleen als T een toekenning van een int toelaat,
    /// zodat bv.
    ///    T a=5;
    /// geldig is.

    void meet(int kortste, int langste, ostream& os) {
        // Print header
        os << std::setw(10) << "length\t\t"
                << "random\t"
                << "gesorteerd\t"
                << "omgekeerd"
                << std::endl;

        // Print results
        for (int i = kortste; i <= langste; i *= 10) {

            Sortvector<T> svr(i);
            svr.vul_random_zonder_dubbels();

            Sortvector<T> svg(i);
            svg.vul_range();

            Sortvector<T> svo(i);
            svo.vul_omgekeerd();

            Chrono cr;
            cr.start();
            (*this)(svr);
            cr.stop();

            Chrono cr2;
            cr2.start();
            (*this)(svg);
            cr2.stop();

            Chrono cr3;
            cr3.start();
            (*this)(svo);
            cr3.stop();

            os << std::setw(10) << i
                    << "\t" << std::setw(10) << cr.tijd()
                    << "\t" << std::setw(10) << cr2.tijd()
                    << "\t" << std::setw(10) << cr3.tijd()
                    << std::endl;
        }

    }

    void meet(int kortste, int langste, CsvData & csv) {

        vector<double> csv_data_vector;

        // Print results
        for (int i = kortste; i <= langste; i *= 10) {

            Sortvector<T> svr(i);
            svr.vul_random_zonder_dubbels();

            Sortvector<T> svg(i);
            svg.vul_range();

            Sortvector<T> svo(i);
            svo.vul_omgekeerd();

            Chrono cr;
            cr.start();
            (*this)(svr);
            cr.stop();

            Chrono cr2;
            cr2.start();
            (*this)(svg);
            cr2.stop();

            Chrono cr3;
            cr3.start();
            (*this)(svo);
            cr3.stop();

            csv_data_vector.push_back(i);
            //            tijden.push_back(cr.tijd());
            //            tijden.push_back(cr2.tijd());
            //            tijden.push_back(cr3.tijd());
        }

        csv.voegDataToe(csv_data_vector);
    }
};

/** \class STLSort
   \brief STANDARD TEMPLATE LIBRARY SORT
 */
template <typename T>
class STLSort : public Sorteermethode<T> {
public:
    void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const {
    sort(v.begin(), v.end());
}

/** \class InsertionSort
 */
template <typename T>
class InsertionSort : public Sorteermethode<T> {
public:
    void operator()(vector<T> & v) const;
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const {
    for (int i = 1; i < v.size(); i++) {
        T h;
        h = move(v[i]);
        int j = i - 1;
        while (j >= 0 && h < v[j]) {
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(h);
    }
}

/** \class Shellsort
 */

template <typename T>
class ShellSort : public Sorteermethode<T> {
public:
    void operator()(vector<T> & v) const;
};

template <typename T>
void ShellSort<T>::operator()(vector<T>& v) const {
    // originele incrementen van Shell (n/2, n/4, ..., 1)
    int k = v.size() / 2;
    // start met grootste increment, ga door tot k = 1
    while (k >= 1) {
        // insertion sort voor k
        // eerste elementen v[0..k-1] staan al in volgorde
        for (int i = k; i < v.size(); i++) {
            T h = move(v[i]);
            int j = i - k;
            while (j >= 0 && h < v[j]) {
                v[j + k] = move(v[j]);
                j -= k;
            }
            v[j + k] = move(h);
        }
        // volgend increment
        k /= 2;
    }
}

template <typename T>
class MergeSort : public Sorteermethode<T> {
public:
    void operator()(vector<T> &v) const;
private:
    void topdown(vector<T> &h, int l, int r, vector<T> &v) const;
    void merge(vector<T> &v, int l, int m, int r, vector<T> &h) const;
    void copy(vector<T> &a, vector<T> &b) const;
};

/**
 * Vector v[] bevat alle elementen die te sorteren zijn,
 * vector h[] is een hulpvector van dezelfde grootte.
 * @param v te sorteren vector
 */
template <typename T>
void MergeSort<T>::operator()(vector<T>& v) const {
    Sortvector<T> h(v.size());
    // kopieer vector v[] in vector h[]
    copy(v, h);
    // sorteer elementen van h[] in v[]
    topdown(h, 0, v.size(), v);
}

/**
 * Sorteer gegeven vector v[] gebruik makend van vector h[] als bron.
 * Merk op dat bij elke recursiestap de richting van de merge wordt afgewisseld,
 * hierdoor wordt een copy terug stap vermeden.
 * @param h hulpvector
 * @param l inclusieve index voor begin vector
 * @param r exclusieve index voor eind vector
 * @param v te sorteren vector
 */

template <typename T>
void MergeSort<T>::topdown(vector<T>& h, int l, int r, vector<T>& v) const {
    // laat recursie lopen tot de grootte van vector 1 is (exclusief)
    if (l < r - 1) {
        // deel de vector, die meer dan 1 element bevat, op in 2
        int m = l + (r - l) / 2; // veiliger dan (l + r) / 2
        // sorteer beide delen van v[] recursief naar hulpvector h[]
        topdown(v, l, m, h);
        topdown(v, m, r, h);
        // voeg de delen van h[] samen in v[]
        merge(h, l, m, r, v);
    }
}

/**
 * Voeg linkse en rechtse delen van vector v[] samen in vector h[].
 * Linkerdeel is v[l:m-1], rechterdeel is v[m:r-1],
 * resultaat is h[l:r-1].
 * @param v te sorteren vector
 * @param l inclusieve index begin linkerdeel
 * @param m exclusieve index eind linkerdeel, inclusieve index begin rechterdeel
 * @param r exclusieve index eind rechterdeel
 * @param h bevat resultaat na merge
 */
template <typename T>
void MergeSort<T>::merge(vector<T>& v, int l, int m, int r, vector<T>& h) const {
    int i = l, j = m;

    // zolang er elementen zijn in linker of rechter delen
    for (int k = l; k < r; k++) {
        // Zolang index zich bevindt in linkerdeel en het element
        // op die index kleiner is dan elementen van het rechter deel.
        // Opm.: Indien j groter of gelijk is aan r, wilt dit zeggen
        // dat voor deze iteratiestap sowieso een element uit linkerdeel
        // gebruikt zal worden voor de merge, want het rechterdeel bevat geen
        // elementen meer om te mergen.
        if (i < m && (j >= r || v[i] <= v[j])) {
            // kies element uit linkerdeel om te mergen
            h[k] = move(v[i]);
            // verhoog index voor linkerdeel
            i++;
        } else {
            // kies element uit rechterdeel om te mergen
            h[k] = move(v[j]);
            // verhoog index voor rechterdeel
            j++;
        }
    }
}

template <typename T>
void MergeSort<T>::copy(vector<T>& a, vector<T>& b) const {
    if (a.size() == b.size()) {
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i];
        }
    }
}

#endif 