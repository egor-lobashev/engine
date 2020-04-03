#include "Singleton.h"

Singleton* Singleton::getInstance()
{
    if (!instance)
        instance = new Singleton();
    return instance;
}

Singleton* Singleton::instance = nullptr;
