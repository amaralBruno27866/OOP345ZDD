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

		// Private constructor
		Database(const std::string& filename) : filename(filename), entryCount(0) {
			std::cout << "[" << this << "] Database(const std::string&)\n";
			std::ifstream file(filename);
			std::string line;
			while (std::getline(file, line)) {
				std::string key, value;

				// Find the position of the first space to separate the key and value
				size_t spacePos = line.find(' ');
				if (spacePos != std::string::npos) {
					key = line.substr(0, spacePos);
					value = line.substr(spacePos + 1);

					// Replace underscores with spaces in the key
					std::replace(key.begin(), key.end(), '_', ' ');

					// Store the key and value in the arrays if there's space
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

		// Encrypt/Decrypt function
		void encryptDecrypt(T& val) {}

	public:
		// Deleted copy constructor and assignment operator to enforce singleton pattern
		Database(const Database&) = delete;
		Database& operator=(const Database&) = delete;

		// Singleton getInstance method
		static std::shared_ptr<Database<T>> getInstance(const std::string& filename) {
			if (!instance) {
				instance = std::shared_ptr<Database<T>>(new Database<T>(filename));
			}
			return instance;
		}

		// Public interface for getting and setting values
		Err_Status GetValue(const std::string& key, T& value) {
			for (int i = 0; i < entryCount; ++i) {
				if (keys[i] == key) {
					value = values[i];
					encryptDecrypt(value); // Decrypt the value
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

		// Destructor
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
