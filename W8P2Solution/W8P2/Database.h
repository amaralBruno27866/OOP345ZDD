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

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>

namespace seneca {
	enum class Err_Status
	{
		Err_Success,
		Err_NotFound,
		Err_OutOfMemory,
	};

	template <typename T>
	class Database {
	private:
		static std::shared_ptr<Database<T>> instance;
		std::string keys[20];
		T values[20] {};
		std::string filename;
		int entryCount = 0;

		Database(const std::string& filename) : filename(filename), entryCount(0) {
			std::cout << "[" << this << "] Database(const std::string&)\n";
			std::fill_n(values, 20, T{});
			std::ifstream file(filename);
			std::string line;
			while (std::getline(file, line)) {
				std::string key, value;
				size_t spacePos = line.find(' ');
				if (spacePos != std::string::npos) {
					key = line.substr(0, spacePos);
					value = line.substr(spacePos + 1);
					std::replace(key.begin(), key.end(), '_', ' ');
					if (entryCount < 20) {
						keys[entryCount] = key;
						std::istringstream iss(value);
						if (!(iss >> values[entryCount])) {
							std::cerr << "Error: Conversion from std::string to T failed for value: " << value << std::endl;
						}
						++entryCount;
					}
				}
			}
		}

		void encryptDecrypt(T& val) {}

	public:
		Database(const Database&) = delete;
		Database& operator=(const Database&) = delete;

		static std::shared_ptr<Database<T>> getInstance(const std::string& filename) {
			if (!instance) {
				instance = std::shared_ptr<Database<T>>(new Database<T>(filename));
			}
			return instance;
		}

		Err_Status GetValue(const std::string& key, T& value) {
			for (int i = 0; i < entryCount; ++i) {
				if (keys[i] == key) {
					value = values[i];
					encryptDecrypt(value);
					return Err_Status::Err_Success;
				}
			}
			return Err_Status::Err_NotFound;
		}

		Err_Status SetValue(const std::string& key, const T& value) {
			if (entryCount >= 20) {
				return Err_Status::Err_OutOfMemory;
			}
			keys[entryCount] = key;
			values[entryCount] = value;
			++entryCount;
			return Err_Status::Err_Success;
		}

		~Database() {
			std::cout << "[" << this << "] ~Database()\n";
			std::ofstream backupFile(filename + ".bkp.txt");
			for (int i = 0; i < entryCount; ++i) {
				backupFile << std::left << std::setw(25) << keys[i] << " -> " << values[i] << "\n";
			}
		}
	};

	template<typename T>
	std::shared_ptr<Database<T>> Database<T>::instance = nullptr;

	template<>
	void Database<std::string>::encryptDecrypt(std::string& value) {
		const char secret[] = "secret encryption key";
		for (char& c : value) {
			for (const char& k : secret) {
				c = c ^ k;
			}
		}
	}

	template<>
	void Database<long long>::encryptDecrypt(long long& value) {
		const char secret[] = "super secret encryption key";
		char* valueBytes = reinterpret_cast<char*>(&value);
		for (size_t i = 0; i < sizeof(long long); ++i) {
			for (const char& k : secret) {
				valueBytes[i] = valueBytes[i] ^ k;
			}
		}
	}
}

#endif // !SENECA_DATABASE_H
