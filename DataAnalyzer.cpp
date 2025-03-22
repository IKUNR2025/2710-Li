/**
 * @file DataAnalyzer.cpp
 * @author Cunzhi You 
 * @Auburn ID: 904168994
 * @brief Implementation of data analysis toolkit
 * @date 2025-03-21
 *
 * Compilation: make (using provided Makefile)
 * Execution: ./bin/DataAnalyzer
 *
 * Implementation details:
 * - Strict numeric validation using stream parsing
 * - Recursive merge sort implementation
 * - Mode calculation handles multiple candidates
 * - Comprehensive error handling and logging
 */

#include "DataAnalyzer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <vector>

using namespace std;

DataAnalyzer::DataAnalyzer() {}

// Validate string represents proper numeric value
bool DataAnalyzer::isValidNumber(const string& str) {
    if (str.empty()) return false;
    istringstream iss(str);
    double val;
    iss >> val;
    // Verify full string consumption and no parsing errors
    return iss.eof() && !iss.fail();
}

void DataAnalyzer::logError(const string& message) {
    ofstream logFile("output/error.log", ios::app);
    if (logFile) {
        logFile << message << endl;
        logFile.close();
    }
}

void DataAnalyzer::readFiles() {
    int numFiles;
    string folder;

    cout << "*** Welcome to You's Data Analyzer ***\n";
    cout << "Enter the number of files to read: ";
    while (!(cin >> numFiles) || numFiles <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a positive integer: ";
    }

    cout << "Select input type:\n1. Normal input (input/)\n2. Error input (input_error/)\nChoice: ";
    int inputType;
    cin >> inputType;
    folder = (inputType == 1) ? "input/" : "input_error/";

    for (int i = 0; i < numFiles; i++) {
        string filename;
        bool validFile = false;
        while (!validFile) {
            cout << "Enter filename for file " << (i + 1) << ": ";
            cin >> filename;
            filename = folder + filename;

            ifstream file(filename);
            if (!file) {
                cout << "File not found. Try again.\n";
                continue;
            }

            string line;
            bool fileValid = true;
            vector<double> fileData;
            while (getline(file, line)) {
                line.erase(0, line.find_first_not_of(" \t\n\r"));
                line.erase(line.find_last_not_of(" \t\n\r") + 1);
                if (isValidNumber(line)) {
                    fileData.push_back(stod(line));
                }
                else {
                    cout << "Invalid content in " << filename << ": [" << line << "]\n";
                    logError("Invalid content in " + filename + ": " + line);
                    fileValid = false;
                    break;
                }
            }

            if (fileValid && !fileData.empty()) {
                data.insert(data.end(), fileData.begin(), fileData.end());
                cout << "List of " << fileData.size() << " values in " << filename << ":\n";
                for (double num : fileData) cout << num << endl;
                validFile = true;
            }
            else if (fileData.empty()) {
                cout << "Empty file. Try again.\n";
            }
            file.close();
        }
    }
}

// Merge two sorted subarrays [left..mid] and [mid+1..right]
void DataAnalyzer::merge(vector<double>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<double> L(n1), R(n2);
    copy(arr.begin() + left, arr.begin() + left + n1, L.begin());
    copy(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2, R.begin());

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Recursive merge sort implementation
void DataAnalyzer::mergeSort(vector<double>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

double DataAnalyzer::calculateMean() {
    if (data.empty()) return 0.0;
    double sum = 0;
    for (double num : data) sum += num;
    return sum / data.size();
}

double DataAnalyzer::calculateMedian() {
    if (data.empty()) return 0.0;
    int n = data.size();
    mergeSort(data, 0, data.size() - 1);
    return (n % 2 == 0) ? (data[n / 2 - 1] + data[n / 2]) / 2.0 : data[n / 2];
}

double DataAnalyzer::calculateMode() {
    if (data.empty()) return 0.0;
    map<double, int> freq;
    for (double num : data) freq[num]++;

    int maxCount = 0;
    vector<double> modes;
    for (auto& pair : freq) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            modes.clear();
            modes.push_back(pair.first);
        }
        else if (pair.second == maxCount) {
            modes.push_back(pair.first);
        }
    }

    double sum = 0;
    for (double num : modes) sum += num;
    return sum / modes.size();
}

void DataAnalyzer::displayResults() {
    mergeSort(data, 0, data.size() - 1);
    cout << fixed << setprecision(4);
    cout << "\n***** Summarized Statistics *****\n";
    cout << "Sorted values (" << data.size() << "): ";
    for (size_t i = 0; i < data.size(); i++) {
        cout << data[i];
        if (i != data.size() - 1) cout << ", ";
    }
    cout << "\nMean: " << calculateMean()
        << "\nMedian: " << calculateMedian()
        << "\nMode: " << calculateMode() << endl;
}

void DataAnalyzer::saveToCSV() {
    string outputPath;
    ofstream csvFile;
    bool validPath = false;

    while (!validPath) {
        cout << "Enter output filename: ";
        cin >> outputPath;
        csvFile.open(outputPath);
        if (csvFile) {
            validPath = true;
            csvFile << "Statistic,Value\n" << fixed << setprecision(4);
            csvFile << "Mean," << calculateMean() << "\nMedian," << calculateMedian()
                << "\nMode," << calculateMode() << "\n";
            csvFile << "Sorted values,";
            for (size_t i = 0; i < data.size(); i++) {
                csvFile << data[i];
                if (i != data.size() - 1) csvFile << ", ";
            }
            csvFile.close();
            cout << "*** File " << outputPath << " saved ***\n";
        }
        else {
            cout << "Invalid path. Try again.\n";
        }
    }
}