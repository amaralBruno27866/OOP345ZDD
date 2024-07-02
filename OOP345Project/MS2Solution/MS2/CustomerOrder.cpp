// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <utility>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities u;
		size_t next_pos = 0;
		bool more = true;

		m_name = u.extractToken(str, next_pos, more);

		if (more) {
			m_product = u.extractToken(str, next_pos, more);
		}

		std::vector<std::string> itemNames;
		while (more) {
			itemNames.push_back(u.extractToken(str, next_pos, more));
		}

		m_cntItem = itemNames.size();
		m_lstItem = new Item * [m_cntItem];

		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(itemNames[i]);
		}

		if(u.getFieldWidth() > CustomerOrder::m_widthField) {
			CustomerOrder::m_widthField = u.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& oth) {
		m_name = oth.m_name;
		m_product = oth.m_product;
		m_cntItem = oth.m_cntItem;
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(oth.m_lstItem[i]->m_itemName);
		}
	}

	CustomerOrder& CustomerOrder::operator=(const CustomerOrder& oth) {
		if(this != &oth) {
			delete[] m_lstItem;
			m_name = oth.m_name;
			m_product = oth.m_product;
			m_cntItem = oth.m_cntItem;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(oth.m_lstItem[i]->m_itemName);
			}
		}
		return *this;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
		: m_name(std::move(other.m_name)), m_product(std::move(other.m_product)),
		m_cntItem(other.m_cntItem), m_lstItem(other.m_lstItem) {
		other.m_lstItem = nullptr;
		other.m_cntItem = 0;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		if (this != &other) {
			delete[] m_lstItem;
			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool isValid = true;
		for (size_t i = 0; i < m_cntItem && isValid; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				isValid = false;
			}
		}

		return isValid;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isValid = true;
		for(size_t i = 0; i < m_cntItem && isValid; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				isValid = false;
			}
		}
		return isValid;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "Filled " << m_name;
					os << ", ";
					os << m_product;
					os << " [";
					os << m_lstItem[i]->m_itemName;
					os << "]" << std::endl;
				}
				else {
					os << "Unable to fill " << m_name;
					os << ", ";
					os << m_product;
					os << " [";
					os << m_lstItem[i]->m_itemName;
					os << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName;
			os << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}

	size_t CustomerOrder::m_widthField = 0;
}
