#include <iostream>
#include <vector>

#include "../03_algorithms/algo.h"

bool func(int elem1, int elem2)
{
    return elem1 * elem1 == elem2;
}

int main (int argc, char *argv[])
{
    std::vector<int> iv = {1, 2, 4, 3, 8, 8, 9};
    std::vector<int>::iterator iter1 = mystl::adjacent_find(iv.begin(), iv.end());
    std::cout << "*iter1 = " << *iter1 << std::endl;
    std::vector<int>::iterator iter2 = mystl::adjacent_find(iv.begin(), iv.end(), func);
    std::cout << "*iter2 = " << *iter2 << std::endl; 
    return 0;
}
