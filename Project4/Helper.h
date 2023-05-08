#ifndef HELPERS_H
#define HELPERS_H

#include <cstdlib>
#include <iostream>
#include <ctime>

class Helpers {

public:
    static int RandI(int min, int max) {
        if (min < max)
            return ((rand() % (max - min)) + min);
        return 0;
    }
};

#endif // HELPERS_H
#pragma once
