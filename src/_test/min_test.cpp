#include <iostream>
#include <vector>

#include "../03_algorithms/algobase.h"

using std::cout, std::endl;

bool mod_lesser ( int elem1, int elem2 )
{
    if ( elem1 < 0 )
        elem1 = - elem1;
    if ( elem2 < 0 )
        elem2 = - elem2;
    return elem1 < elem2;
}

int main() 
{
    int a = 6, b = -7, c = 7 ;
    const int& result1 = mystl::min( a, b, mod_lesser );
    const int& result2 = mystl::min( b, c );

    cout << "The mod_lesser of the integers 6 & -7 is: "
        << result1 << "." << endl;
    cout << "The lesser of the integers -7 & 7 is: "
        << result2 << "." << endl;
    cout << endl;
    return 0;
}