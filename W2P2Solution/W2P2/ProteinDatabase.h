/*/////////////////////////////////////////////////////////////////////////
						  Workshop - #2 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

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
		ProteinDatabase(const ProteinDatabase& pd);
		ProteinDatabase& operator=(const ProteinDatabase& pd);
		~ProteinDatabase();
		void init(const ProteinDatabase& pd);

		ProteinDatabase(ProteinDatabase&& pd) noexcept;
		ProteinDatabase& operator=(ProteinDatabase&& pd) noexcept;

		size_t size() const { return m_numOfSequences; };
		std::string operator[] (size_t index);
	};
}

#endif // !SENECA_PROTEINDATABASE_H
