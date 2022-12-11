#include "warming_up.h"
#include <iostream>
using namespace std;

/**
 * @brief Display a vector contains.
 * Items are separated by space.
 *
 * @param v a vector of booleans.
 */
void display_vector(const vector<bool> &v)
{
    cout << "[ ";
    copy(v.begin(), v.end(), ostream_iterator<bool>(cout, " "));
    cout << "]";
}

/**
 * Decompose l'entier n en une liste de bits.
 * Les bits de poids les plus faibles sont en tête.
 */
vector<bool> decomposition(NTL::ZZ n)
{
    vector<bool> v;
    NTL::ZZ quotient = n, reste;
    while (quotient != 0) {
        reste = quotient % 2;
        quotient /= 2;
        v.push_back(reste == 1 ? true : false);
    }
    return v;
}
vector<bool> decomposition(int n)
{
    return decomposition(NTL::ZZ(n));
}

/**
 * @brief complete (with false) or tronc the giving list.
 *
 * @param v vector to complete
 * @param n the size of the final vector.
 * @return vector<bool> of size n
 */
vector<bool> completion(vector<bool> v, NTL::ZZ n)
{
    if (n > v.size()) {
        NTL::ZZ difference = n - v.size();
        // Only Because NTL does not convert automatically to bool
        while (difference != 0) {
            difference--;
            v.push_back(false);
        }

    } else {
        NTL::ZZ difference = v.size() - n;
        // Only Because NTL does not convert automatically to bool
        while (difference != 0) {
            difference--;
            v.pop_back();
        }
    }
    return v;
}
vector<bool> completion(vector<bool> v, int n)
{
    return completion(v, NTL::ZZ(n));
}

/**
 * @brief decompose the integer x in base 2 then
 * make it size equals to n
 *
 * @param x
 * @param n
 * @return vector<bool>
 */
vector<bool> table(NTL::ZZ x, NTL::ZZ n)
{
    return completion(decomposition(x), n);
}
vector<bool> table(int x, int n)
{
    return table(NTL::ZZ(x), NTL::ZZ(n));
}