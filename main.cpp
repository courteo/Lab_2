#include <iostream>

#include "Cache.h"
#include "ctime"


int main() {
    Cache<int> A;
    A.Add(1);
    A.Add(3);
    A.Add(1);
    A.PrintCache();
    A.Add(3);
    A.Add(3);
    A.Add(2);
    A.Add(4);
    A.Add(2);
    A.Add(2);
    A.Add(2);
    A.PrintCache();
    A.Remove(3);
    A.PrintCache();
    //abc.Add(23);
    //std::cout << abc.IsContains(23);
    //abc.Add(23);

    return 0;
}
