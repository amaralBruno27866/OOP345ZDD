// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: August 4th, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities u;
		size_t np = 0;
		bool more = true;

		m_name = u.extractToken(str, np, more);

		if (more) {
			m_product = u.extractToken(str, np, more);
		}

		std::vector<std::string> item;

		while (more) {
			item.push_back(u.extractToken(str, np, more));
		}

		m_cntItem = item.size();
		m_lstItem = new Item * [m_cntItem];

		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(item[i]);
		}

		if (u.getFieldWidth() > CustomerOrder::m_widthField) {
			CustomerOrder::m_widthField = u.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& co) {
		throw std::logic_error("Copy constructor not allowed");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept : m_name(std::move(co.m_name)), m_product(std::move(co.m_product)), m_cntItem(co.m_cntItem), m_lstItem(co.m_lstItem) {
		co.m_lstItem = nullptr;
		co.m_cntItem = 0;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		if (this != &co) {
			m_name = std::move(co.m_name);
			m_product = std::move(co.m_product);
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_cntItem = co.m_cntItem;
			co.m_cntItem = 0;
			m_lstItem = co.m_lstItem;
			co.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool isTrue = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				isTrue = false;
			}
		}
		return isTrue;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool fail = true;
		for(size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				fail = false;
			}
		}
		return fail;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool itemFound = false;
		for (size_t i = 0; i < m_cntItem && !itemFound; i++) {
			if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();

					m_lstItem[i]->m_isFilled = true;
					itemFound = true;

					os << "    Filled " << m_name;
					os << ", ";
					os << m_product;
					os << " [";
					os << m_lstItem[i]->m_itemName;
					os << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name;
					os << ", ";
					os << m_product;
					os << " [";
					os << m_lstItem[i]->m_itemName;
					os << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const	{
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName;
			os << " - ";
			if(m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << "\n";
		}
	}
}
