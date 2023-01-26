#include <iostream>
#include <vector>

#include "../03_algorithms/algo.h"

int main (int argc, char *argv[])
{
    std::vector<int> iv1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> iv2 = {4, 5, 6, 7};
    auto iter = mystl::search(iv1.begin(), iv2.end(), iv2.begin(), iv2.end());
    std::cout << "*iter = " << *iter << std::endl;
    return 0;
}
