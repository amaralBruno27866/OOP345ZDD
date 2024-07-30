#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: 2024-07-30
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca{
	extern std::deque<seneca::CustomerOrder> g_pending;
	extern std::deque<seneca::CustomerOrder> g_completed;
	extern std::deque<seneca::CustomerOrder> g_incomplete;

	class Workstation : public Station {
	private:
		std::deque<seneca::CustomerOrder> m_orders;
		Workstation* m_pNextStation;

	public:
		Workstation(const std::string& str);

		// Delete copy constructor and copy assignment operator
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;

		// Delete move constructor and move assignment operator
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}

#endif // !SENECA_WORKSTATION_H
