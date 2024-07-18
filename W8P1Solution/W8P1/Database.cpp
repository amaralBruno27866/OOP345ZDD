#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include "Database.h"

namespace seneca {
    // Initialize the static instance pointer to nullptr at the start.
    std::shared_ptr<Database> Database::instance = nullptr;

    Database::Database(const std::string& filename) : filename(filename), entryCount(0) {
        std::cout << "[" << this << "] Database(const std::string&)\n";
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            // Temporary storage for key and value extracted from the line
            std::string key, value;

            // Replace underscores with spaces in the key
            std::replace(line.begin(), line.end(), '_', ' ');

            // Split the line into key and value based on whitespace
            std::istringstream iss(line);
            iss >> key;
            while (iss >> value) {
                // Append subsequent words to the key if more than two words are present
                if (value.front() != '$') { // Check if the value does not start with '$', indicating it's part of the name
                    key += " " + value;
                }
                else {
                    // Once the value starting with '$' is found, break the loop
                    break;
                }
            }

            // Store the key and value in the arrays if there's space
            if (entryCount < 20) {
                keys[entryCount] = key;
                values[entryCount] = value;
                ++entryCount;
            }
        }
    }

    // Singleton getInstance method
    std::shared_ptr<Database> Database::getInstance(const std::string& filename) {
        if (!instance) { // Check if the instance doesn't exist
            instance = std::shared_ptr<Database>(new Database(filename));
        }
        return instance;
    }

    // GetValue method
    Err_Status Database::GetValue(const std::string& key, std::string& value) {
        for (int i = 0; i < entryCount; ++i) {
            if (keys[i] == key) {
                value = values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    // SetValue method
    Err_Status Database::SetValue(const std::string& key, const std::string& value) {
        if (entryCount >= 20) {
            return Err_Status::Err_OutOfMemory;
        }
        keys[entryCount] = key;
        values[entryCount] = value;
        ++entryCount;
        return Err_Status::Err_Success;
    }

    // Destructor
    Database::~Database() {
        std::cout << "[" << this << "] ~Database()\n";
        std::ofstream backupFile(filename + ".bkp.txt");
        for (int i = 0; i < entryCount; ++i) {
            backupFile << std::left << std::setw(25) << keys[i] << " -> " << values[i] << "\n";
        }
    }
}