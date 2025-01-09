//
// Created by kpl21 on 4/18/2024.
//

#include "random.h"
#include <ctime>

std::mt19937 random::Random(time(0));

int random::Int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(Random);
}

float random::Float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(Random);
}
