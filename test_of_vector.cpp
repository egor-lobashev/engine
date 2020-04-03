#include <vector>
#include <iostream>
#include "test2.h"

int main()
{
    DataStorage ds;
    int i = 5;
    ds.addObject(i);
    std::cout << "good\n";
    return 0;
}