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
    std::copy(v.begin(), v.end(), std::ostream_iterator<bool>(std::cout, " "));
    cout << "]";
}

/**
 * Decompose l'entier n en une liste de bits.
 * Les bits de poids les plus faibles sont en tête.
 */
vector<bool> decomposition(int n)
{
    vector<bool> v;
    int quotient = n, reste;
    while (quotient != 0) {
        reste = quotient % 2;
        quotient /= 2;
        v.push_back(reste == 1 ? true : false);
    }
    return v;
}

/**
 * @brief complete (with false) or tronc the giving list.
 *
 * @param v vector to complete
 * @param n the size of the final vector.
 * @return vector<bool> of size n
 */
vector<bool> completion(vector<bool> v, int n)
{
    if (n > v.size()) {
        int difference = n - v.size();
        while (difference--)
            v.push_back(false);
    } else {
        int difference = v.size() - n;
        while (difference--)
            v.pop_back();
    }
    return v;
}

/**
 * @brief decompose the integer x in base 2 then
 * make it size equals to n
 *
 * @param x
 * @param n
 * @return vector<bool>
 */
vector<bool> table(int x, int n)
{
    return completion(decomposition(x), n);
}