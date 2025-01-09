//
// Created by kpl21 on 4/17/2024.
//

#ifndef MINESWEEPER_HELPERS_H
#define MINESWEEPER_HELPERS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::vector;


class helpers {
public:
    static std::vector<int> readConfigValues(const std::string& filePath, int &value1, int &value2, int &value3);
    static vector<int> digitizer(int number);
};


#endif //MINESWEEPER_HELPERS_H
