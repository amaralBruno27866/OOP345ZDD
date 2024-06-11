#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <iostream>
#include <string>
#include <fstream>

namespace seneca {
    class SpellChecker {
       private:
        std::string m_badWords[6];
        std::string m_goodWords[6];
        size_t m_replacements[6] = { 0 }; // Tracks the number of replacements for each bad word
    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}
#endif // !SENECA_SPELLCHECKER_H
