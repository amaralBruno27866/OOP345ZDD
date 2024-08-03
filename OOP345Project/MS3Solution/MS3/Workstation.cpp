// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: August 4th, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Workstation.h"

namespace seneca {
	std::deque<seneca::CustomerOrder> g_pending;
	std::deque<seneca::CustomerOrder> g_completed;
	std::deque<seneca::CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string& str) : Station(str), m_pNextStation(nullptr) {}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool mv = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				CustomerOrder co = std::move(m_orders.front());
				m_orders.pop_front();
				if (m_pNextStation) {
					*m_pNextStation += std::move(co);
				}
				else {
					if (co.isOrderFilled()) {
						g_completed.push_back(std::move(co));
					}
					else {
						g_incomplete.push_back(std::move(co));
					}
					mv = true;
				}
			}
		}
		return mv;
	}

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		os << getItemName() << " --> ";
		if (m_pNextStation) {
			os << m_pNextStation->getItemName();
		}
		else {
			os << "End of Line";
		}
		os << std::endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}
