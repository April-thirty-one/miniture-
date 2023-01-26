#include <iostream>
#include <vector>
#include <ctime>

#include "../03_algorithms/algo.h"

bool func(int elem1, int elem2)
{
    return (2 * elem1) == elem2;
}


int main (int argc, char *argv[])
{
    srand(time(NULL));
    std::vector<int> iv1(10);
    std::vector<int> iv2(15);
    for (int & item : iv1)
    {
        item = rand() % 10;
    }
    for (int & item : iv2)
    {
        item = rand() % 10;
    }

    std::cout << "iv1 = (";
    for (auto iter = iv1.begin(); iter != iv1.end(); ++iter)
    {
        std::cout << *iter << "  ";
    }
    std::cout << ")" << std::endl;
    
    std::cout << "iv2 = (";
    for (auto iter = iv2.begin(); iter != iv2.end(); ++iter)
    {
        std::cout << *iter << "  ";
    }
    std::cout << ")" << std::endl;

    std::vector<int>::iterator result1 = mystl::find_first_of(iv1.begin(), iv1.end(), iv2.begin(), iv2.end());
    std::cout << "*resilt1 = " << *result1 << std::endl;
    
    std::vector<int>::iterator result2 = mystl::find_first_of(iv1.begin(), iv1.end(), iv2.begin(), iv2.end(), func);
    std::cout << "*resilt2 = " << *result2 << std::endl;
    return 0;
}
