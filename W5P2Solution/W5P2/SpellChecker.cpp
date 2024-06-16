/*/////////////////////////////////////////////////////////////////////////
                  Workshop - #5 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include "SpellChecker.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept> // For std::runtime_error

namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Bad file name!");
        std::string line;
        for (size_t i = 0; i < 6 && std::getline(file, line); ++i) {
            auto pos = line.find(' ');
            m_badWords[i] = line.substr(0, pos);
            // Find the start of the good word
            auto start = line.find_first_not_of(' ', pos);
            // Find the end of the good word
            auto end = line.find_last_not_of(' ');
            m_goodWords[i] = line.substr(start, end - start + 1);
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

    void SpellChecker::showStatistics(std::ostream& out) const noexcept {
        out << "Spellchecker Statistics\n";
        for (size_t i = 0; i < 6; ++i) {
            out << std::right << std::setw(15) << m_badWords[i] << ": " << m_replacements[i] << " replacements\n";
        }
    }
}