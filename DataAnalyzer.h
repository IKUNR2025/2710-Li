/**
 * @file DataAnalyzer.h
 * @author Cunzhi You
 * @Auburn ID: 904168994
 * @brief Header file for data analysis toolkit
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025 Auburn University
 *
 * Features:
 * - Multi-file input handling with validation
 * - Merge sort implementation (O(n log n) complexity)
 * - Statistical calculations (mean, median, mode)
 * - CSV output generation
 */

#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H

#include <iostream>
#include <vector>
#include <string>

 /**
  * @class DataAnalyzer
  * @brief Core class for data processing and analysis operations
  *
  * Handles complete workflow from file input to statistical output generation.
  * Implements sorting and calculation algorithms meeting project specifications.
  */
class DataAnalyzer {
public:
    DataAnalyzer();

    /// @brief Main entry point for file processing workflow
    void readFiles();

    /// @brief Merge sort implementation for numeric data
    void mergeSort(std::vector<double>& arr, int left, int right);

    // Statistical calculation interfaces
    double calculateMean();
    double calculateMedian();
    double calculateMode();

    /// @brief Displays formatted results to standard output
    void displayResults();

    /// @brief Handles CSV file generation with path validation
    void saveToCSV();

    /// @brief Error logging utility
    void logError(const std::string& message);

    std::vector<double> data; ///< Consolidated dataset from all valid files

private:
    /// @brief Merge helper for merge sort algorithm
    void merge(std::vector<double>& arr, int left, int mid, int right);

    /// @brief Validates numeric format compliance
    bool isValidNumber(const std::string& str);
};

#endif