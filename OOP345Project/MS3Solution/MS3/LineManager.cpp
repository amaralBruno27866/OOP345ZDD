#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <algorithm>
#include <iostream>
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
			std::string currentStationName = record.substr(0, delimiterPos);
			std::string nextStationName = record.substr(delimiterPos + 1);

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
}