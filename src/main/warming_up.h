#ifndef WARNING_UP_H
#define WARNING_UP_H

#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

/**
 * @brief Display a vector contains.
 * Items are separated by space.
 * 
 * @param v a vector of booleans.
 */
void display_vector(const vector<bool> &v);

/**
 * Decompose l'entier n en une liste de bits.
 * Les bits de poids les plus faibles sont en tête.
 */
vector<bool> decomposition(int n);

/**
 * @brief complete (with false) or tronc the giving list.
 * 
 * @param v vector to complete
 * @param n the size of the final vector.
 * @return vector<bool> of size n
 */
vector<bool> completion(vector<bool> v, int n);

/**
 * @brief decompose the integer x in base 2 then
 * make it size equals to n
 * 
 * @param x 
 * @param n 
 * @return vector<bool> 
 */
vector<bool> table(int x, int n);

#endif