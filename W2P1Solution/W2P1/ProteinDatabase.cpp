#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include <iostream>

#include "ProteinDatabase.h"
#include "TimedTask.h"

namespace seneca {
	ProteinDatabase::ProteinDatabase() {
		m_sequences = nullptr;
		m_numOfSequences = 0;
	}

	ProteinDatabase::ProteinDatabase(const std::string& fileName) : m_numOfSequences(0) {
		std::ifstream file(fileName);
		std::string line;


		while (getline(file, line)) {
			if (line[0] == '>') {
				m_numOfSequences++;
			}
		}

		m_sequences = new std::string[m_numOfSequences];

		file.clear();
		file.seekg(0);

		size_t i = 0;
		std::string proteinSequence;

		while (getline(file, line)) {
			if (line[0] != '>') {
				proteinSequence += line + '\n';
				if (file.peek() == '>' || file.eof()) {
					if (i < m_numOfSequences) {
						m_sequences[i] = proteinSequence;
					}
					proteinSequence.clear();
					i++;
				}
			}
		}
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& pd) {
		init(pd);
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& pd) {
		if (this != &pd) {
			if (m_sequences != nullptr) {
				delete[] m_sequences;
				m_sequences = nullptr;
			}
			init(pd);
		}

		return *this;
	}

	ProteinDatabase::~ProteinDatabase() {
		delete[] m_sequences;
		m_sequences = nullptr;
	}

	void ProteinDatabase::init(const ProteinDatabase& pd) {
		m_numOfSequences = pd.m_numOfSequences;
		m_sequences = new std::string[pd.m_numOfSequences];
		for (size_t i = 0; i < m_numOfSequences; i++) {
			m_sequences[i] = pd.m_sequences[i];
		}
	}

	std::string ProteinDatabase::operator[](size_t index) {
		std::string result;

		if (index < m_numOfSequences) {
			result = m_sequences[index];
		}
		else {
			result = "";
		}

		return result;
	}
}
