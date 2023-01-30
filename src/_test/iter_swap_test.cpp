#include <iostream>
#include <vector>

#include "../03_algorithms/algobase.h"

using std::cout, std::endl;

int main(int argc, char * argv[])
{   
    std::vector<int> iv = {1, 2, 3, 4, 5};
    mystl::iter_swap(iv.begin(), --iv.end());
    for (auto item : iv)
    {
        cout << item << "  ";
    }
    cout << endl;
    
    return 0;
}