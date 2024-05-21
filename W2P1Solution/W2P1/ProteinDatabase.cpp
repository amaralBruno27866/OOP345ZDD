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
			if (line[0] != '>') {
				m_numOfSequences++;
			}
		}

		m_sequences = new std::string[m_numOfSequences];

		file.clear();

		file.seekg(0);

		size_t i = 0;

		while (getline(file, line)) {
			if (line[0] != '>' && (line.length() == 60 || (line.length() < 60 && file.peek() == '>'))) {
				if (i < m_numOfSequences) {
					m_sequences[i] = line;
					i++;
				}
			}
		}
	}

	ProteinDatabase::~ProteinDatabase() {
		delete[] m_sequences;
		m_sequences = nullptr;
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
