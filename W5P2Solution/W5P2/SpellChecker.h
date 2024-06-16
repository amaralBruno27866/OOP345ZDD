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
