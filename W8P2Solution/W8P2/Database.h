/*/////////////////////////////////////////////////////////////////////////
                  Workshop - #8 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <type_traits>
#include <mutex> // Include mutex header

namespace seneca {

    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    // Forward declaration of encryptDecrypt functions for specific types
    void encryptDecrypt(std::string& value);
    void encryptDecrypt(long long& value);

    template<typename T>
    class Database {
    private:
        static std::shared_ptr<Database<T>> instance;
        static std::mutex instanceMutex; // Static mutex for thread-safe singleton implementation
        std::vector<std::string> keys;
        std::vector<T> values;
        std::string filename;

        // Helper function to format names
        std::string formatName(const std::string& name) {
            std::string formattedName = name;
            std::replace(formattedName.begin(), formattedName.end(), '_', ' ');
            return formattedName;
        }

        // Encrypt/Decrypt for type T using external functions
        void encryptDecrypt(T& value) {
            // This will call the appropriate function based on T
            ::seneca::encryptDecrypt(value);
        }

        Database(const std::string& filename) : filename(filename) {
            std::cout << "[" << this << "] Database(const std::string&)" << std::endl;
            std::ifstream file(filename);
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string key;
                T value;
                if (!(iss >> key >> value)) { break; } // Error

                key = formatName(key); // Format the name
                encryptDecrypt(value); // Decrypt the value
                keys.push_back(key);
                values.push_back(value);
            }
        }

    public:
        static std::shared_ptr<Database<T>> getInstance(const std::string& filename) {
            if (!instance) {
                std::lock_guard<std::mutex> lock(instanceMutex); // Lock for thread safety
                if (!instance) { // Double-checked locking
                    instance = std::shared_ptr<Database<T>>(new Database(filename));
                }
            }
            return instance;
        }

        Err_Status GetValue(const std::string& key, T& value) const {
            auto it = std::find(keys.begin(), keys.end(), key);
            if (it != keys.end()) {
                value = values[std::distance(keys.begin(), it)];
                return Err_Status::Err_Success;
            }
            return Err_Status::Err_NotFound;
        }

        Err_Status SetValue(const std::string& key, const T& value) {
            auto it = std::find(keys.begin(), keys.end(), key);
            if (it != keys.end()) {
                values[std::distance(keys.begin(), it)] = value;
            }
            else {
                keys.push_back(key);
                values.push_back(value);
            }
            return Err_Status::Err_Success;
        }

        ~Database() {
            std::ofstream backupFile(filename + ".bkp.txt");
            for (size_t i = 0; i < keys.size(); ++i) {
                T encryptedValue = values[i];
                encryptDecrypt(encryptedValue); // Encrypt the value
                backupFile << keys[i] << " " << encryptedValue << "\n";
            }
            std::cout << "[" << this << "] ~Database()" << std::endl;
        }
    };

    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::instance = nullptr;

    template<typename T>
    std::mutex Database<T>::instanceMutex; // Define the static mutex
}

#endif // !SENECA_DATABASE_H