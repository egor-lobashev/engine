#ifndef _AXA_
#define _AXA_

#include <vector>
#include <iostream>

class DataStorage{
    public:
        bool addObject(int obj);
    private:
        std::vector<int> map_of_game_objects;
};

#endif