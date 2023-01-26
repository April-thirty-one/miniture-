#include <iostream>
#include <ostream>
#include <vector>

#include "../03_algorithms/algo.h"

int main (int argc, char *argv[])
{
    std::vector<int> iv = {1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 9};
    auto iter = mystl::search_n(iv.begin(), iv.end(), 6, 8);
    std::cout << "*iter = " << *iter << std::endl;
    return 0;
}
