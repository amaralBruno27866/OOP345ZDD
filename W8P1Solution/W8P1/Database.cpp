#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <iostream>
#include "Database.h"

namespace seneca {
	std::shared_ptr<Database> Database::getInstance(const std::string& filename) {
		return std::shared_ptr<Database>();
	}

	Err_Status Database::GetValue(const std::string& key, std::string& value) {
		return Err_Status();
	}

	Err_Status Database::SetValue(const std::string& key, const std::string& value) {
		return Err_Status();
	}

	Database::~Database() {
	}
}