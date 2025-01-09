//
// Created by kpl21 on 4/17/2024.
//
#include "helpers.h"
#include <vector>
std::vector<int> helpers::readConfigValues(const std::string& filePath, int &value1, int &value2, int &value3){
    std::ifstream cfgFile(filePath);
    std::string line;
    if(std::getline(cfgFile, line)){
        value1 = std::stoi(line);
    }
    if(std::getline(cfgFile, line)){
        value2 = std::stoi(line);
    }
    if(std::getline(cfgFile, line)){
        value3 = std::stoi(line);
    }
    std::vector<int> configValues;
    configValues.push_back(value1);
    configValues.push_back(value2);
    configValues.push_back(value3);
    cfgFile.close();
    return configValues;
}


vector<int> helpers::digitizer(int number) {
    vector<int> nums;

    // Can't handle < -99
    if (number < -99) {
        nums.push_back(10);
        nums.push_back(9);
        nums.push_back(9);
    }

        // -99 to -10
    else if (number < -9) {
        nums.push_back(10);
        int temp = (number * -1) / 10;
        nums.push_back(temp);
        temp = (number * -1) % 10;
        nums.push_back(temp);
    }

        // - 9 to -1
    else if (number < 0) {
        nums.push_back(10);
        nums.push_back(0);
        nums.push_back(number * -1);
    }

        // 0 to 9
    else if (number < 10) {
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(number);
    }

        // 10 to 99
    else if (number < 100) {
        nums.push_back(0);
        int temp = number / 10;
        nums.push_back(temp);
        temp = number % 10;
        nums.push_back(temp);
    }

        // 100 to 999 <- In our version, max is 400
    else if (number < 1000) {
        int temp = number / 100;
        nums.push_back(temp);
        temp = number % 100;
        temp /= 10;
        nums.push_back(temp);
        temp = number % 10;
        nums.push_back(temp);
    }

        // Unnecessary for our game but just in case, max at 999
    else if (number > 999) {
        nums.push_back(9);
        nums.push_back(9);
        nums.push_back(9);
    }

    return nums;
}