#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <fstream>
#include <iomanip>
#include "SpellChecker.h"

namespace seneca {
	SpellChecker::SpellChecker(const char* filename) {
		std::ifstream file(filename);
		if (!file) {
			throw "Bad file name!";
		}

		std::string line;
		size_t index = 0;

		while (getline(file, line) && index < 6) {
			std::istringstream iss(line);
			iss >> m_badWords[index] >> m_goodWords[index];
			index++;
		}
	}

	void SpellChecker::operator()(std::string& text) {
		for (size_t i = 0; i < 6; i++) {
			size_t pos = text.find(m_badWords[i]);
			while (pos != std::string::npos) {
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
				m_replacements[i]++;
				pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const {
		for (size_t i = 0; i < 6; i++) {
			out << std::right << std::setw(15) << m_badWords[i];
			out << ": ";
			out << m_replacements[i];
			out << " replacements";
			out << std::endl;
		}
	}
}
