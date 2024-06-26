#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	CustomerOrder::CustomerOrder() {
	}

	CustomerOrder::CustomerOrder(const std::string& str) {
	}

	CustomerOrder::CustomerOrder(const CustomerOrder&& str) noexcept {
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& str) noexcept {
		// TODO: insert return statement here
	}

	CustomerOrder::~CustomerOrder() {
	}

	bool CustomerOrder::isOrderFilled() const {
		return false;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		return false;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	}

	void CustomerOrder::display(std::ostream& os) const {
	}
}
