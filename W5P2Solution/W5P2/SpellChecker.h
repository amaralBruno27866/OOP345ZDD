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

#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <string>
#include <iostream>

namespace seneca {
    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        size_t m_replacements[6] = { 0 };

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const noexcept;
    };
}

#endif // SPELLCHECKER_H
