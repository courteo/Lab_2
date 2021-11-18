#include <iostream>

#include "Cache.h"
#include "ctime"
#include "string"
#include "AlphabetPointer.h"

int main() {
    AlphabetPointer b;
    b.InputArray();
    b.SetSizeOfPage(20);
    b.GetAlphabet();
    return 0;
    /*
    Cache<int> A;
    auto q = A.PersonInput();
    auto w = A.PersonInput();
    auto e = A.PersonInput();
    auto r = A.PersonInput();
    A.Add(q);
    A.Add(w);
    A.Add(q);
    A.Add(w);
    A.Add(w);
    A.Add(e);
    A.Add(r);
    A.Add(e);
    A.Add(e);
    A.Add(e);
    A.PrintCache();
    A.Remove(w);
    A.PrintCache();
    std::cout << A.FindCacheIn(e);

    return 0;
     */
}
