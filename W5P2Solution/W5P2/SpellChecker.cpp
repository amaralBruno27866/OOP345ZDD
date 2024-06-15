#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "SpellChecker.h"

namespace seneca {
	SpellChecker::SpellChecker(const char* filename) {
		std::ifstream file(filename);
		if (!file) throw "Bad file name!";
		std::string line;
		for (size_t i = 0; i < 6 && getline(file, line); ++i) {
			auto pos = line.find(' ');
			m_badWords[i] = line.substr(0, pos);
			m_goodWords[i] = line.substr(line.find_last_not_of(' ') + 1);
		}
	}

	void SpellChecker::operator()(std::string& text) {
		for (size_t i = 0; i < 6; ++i) {
			size_t pos = text.find(m_badWords[i]);
			while (pos != std::string::npos) {
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
				pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
				++m_replacements[i];
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const {
		for (size_t i = 0; i < 6; ++i) {
            out << std::right << std::setw(15) << m_badWords[i] << ": " << m_replacements[i] << " replacements\n";
        }
	}
}