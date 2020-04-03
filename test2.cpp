#include <vector>
#include <iostream>
#include "test2.h"

bool DataStorage::addObject(int obj)
{
    try
    {
        printf("A\n");
        map_of_game_objects.push_back(obj);
        printf("B\n");
        return true;
    }
    catch(...)
    {
        return false;
    }
}