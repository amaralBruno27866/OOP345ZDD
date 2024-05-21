#ifndef PROTEIN_DATABASE_SENECA
#define PROTEIN_DATABASE_SENECA

#include <fstream>
#include <string>
#include <iostream>

namespace seneca {
	class ProteinDatabase {
	private:
		std::string* m_sequences;
		size_t m_numOfSequences;
	public:
		ProteinDatabase();
		ProteinDatabase(const std::string& fileName);
		~ProteinDatabase();

		size_t size() const { return m_numOfSequences; };
		std::string operator[] (size_t index);
	};
}

#endif // !PROTEIN_DATABASE_SENECA
