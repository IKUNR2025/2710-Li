/**
 * @file main.cpp
 * @author Cunzhi You
 * @Auburn ID: 904168994
 * @brief Main driver for data analysis system
 * @date 2025-03-21
 *
 * Program workflow:
 * 1. File input collection and validation
 * 2. Data processing and statistical analysis
 * 3. Result presentation and output generation
 */

#include <iostream>
#include "DataAnalyzer.h"

int main() {
    DataAnalyzer analyzer;
    analyzer.readFiles();
    analyzer.displayResults();
    analyzer.saveToCSV();
    std::cout << "*** Goodbye. ***\n";
    return 0;
}