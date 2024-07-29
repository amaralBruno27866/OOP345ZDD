#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

extern std::deque<seneca::CustomerOrder> g_pending;
extern std::deque<seneca::CustomerOrder> g_completed;
extern std::deque<seneca::CustomerOrder> g_incomplete;

namespace seneca{
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
