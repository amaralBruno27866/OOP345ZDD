// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: August 4th, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include "LineManager.h"

namespace seneca {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::ifstream inputFile(file);
		if (!inputFile) {
			throw std::runtime_error("Unable to open file");
		}

		std::string record;
		while (std::getline(inputFile, record)) {
			size_t delimiterPos = record.find('|');
			std::string currentStationName{};
			std::string nextStationName{};

			if (delimiterPos == std::string::npos) {
				currentStationName = record;
			}
			else {
				currentStationName = record.substr(0, delimiterPos);
				nextStationName = record.substr(delimiterPos + 1);
			}

			auto currentStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
				return ws->getItemName() == currentStationName;
			});

			auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
				return ws->getItemName() == nextStationName;
			});

			if (currentStation != stations.end()) {
				m_activeLine.push_back(*currentStation);
				if (nextStation != stations.end()) {
					(*currentStation)->setNextStation(*nextStation);
				}
			}
		}

		m_firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
			return std::none_of(stations.begin(), stations.end(), [&](Workstation* otherws) {
				return otherws->getNextStation() == ws;
				});
			});

		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations() {
		std::vector<Workstation*> reorderdLine;
		Workstation* currentStation = m_firstStation;

		while (currentStation) {
			reorderdLine.push_back(currentStation);
			currentStation = currentStation->getNextStation();
		}

		m_activeLine = reorderdLine;
	}

	bool LineManager::run(std::ostream& os) {
		static size_t iterationCount = 0;
		os << "Line Manager Iteration: " << ++iterationCount << std::endl;

		if (!g_pending.empty()) {
			CustomerOrder co = std::move(g_pending.front());
			g_pending.pop_front();
			*m_firstStation += std::move(co);
		}

		for(auto& station : m_activeLine) {
			station->fill(os);
		}

		for(auto& station : m_activeLine) {
			station->attemptToMoveOrder();
		}

		return ((g_incomplete.size() + g_completed.size()) == m_cntCustomerOrder);
	}

	void LineManager::display(std::ostream& os) const {
		for (const auto& station : m_activeLine) {
			station->display(os);
		}
	}
}
