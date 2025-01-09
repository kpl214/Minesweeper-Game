//
// Created by kpl21 on 4/18/2024.
//

#ifndef MINESWEEPER_RANDOM_H
#define MINESWEEPER_RANDOM_H
#include <random>

class random {
private:
    static std::mt19937 Random;
public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};


#endif //MINESWEEPER_RANDOM_H
