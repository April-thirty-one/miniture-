#include <iostream>
#include <vector>

#include "../03_algorithms/algobase.h"

using std::cout, std::endl;

bool abs_greater(int elem1, int elem2)
{
    if (elem1 < 0)
    {
        elem1 = -elem1;
    }
    
    if (elem2 < 0)
    {
        elem2 = -elem2;
    }

    return elem1 > elem2;
}

int main(int argc, char * argv[])
{
    int a = 6, b = -7;
    // Return the integer with the larger absolute value
    const int& result1 = mystl::max(a, b, abs_greater);
    // Return the larger integer
    const int& result2 = mystl::max(a, b);

    cout << "Using integers 6 and -7..." << endl;
    cout << "The integer with the greater absolute value is: "
            << result1 << "." << endl;
    cout << "The integer with the greater value is: "
            << result2 << "." << endl;
    cout << endl;

    return 0;
} 