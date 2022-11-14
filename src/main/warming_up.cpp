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
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<bool>(std::cout, " "));
    cout << "]";
}


/**
 * Decompose l'entier n en une liste de bits.
 * Les bits de poids les plus faibles sont en tête.
 */
vector<bool> decomposition(int n) {
    vector<bool> v;
    int quotient = n, reste;
    while (quotient != 0) {
        reste = quotient % 2;
        quotient /= 2;
        v.push_back(reste==1?true:false);
    }
    return v;
}

int main()
{
    vector<bool> v = decomposition(38);
    display_vector(v);
    return 0;
}