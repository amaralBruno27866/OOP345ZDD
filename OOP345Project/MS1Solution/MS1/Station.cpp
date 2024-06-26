#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"

namespace seneca {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station(const std::string& record) {
		Utilities u;
		size_t next_pos = 0;
		bool more = true;

		std::string token;

		m_itemName = u.extractToken(record, next_pos, more);
		m_serialNumber = std::stoi(u.extractToken(record, next_pos, more));
		m_quantityInStock = std::stoi(u.extractToken(record, next_pos, more));

		if (more) {
			std::string desc = u.extractToken(record, next_pos, more);
			m_stationDesc = desc;
			m_widthField = std::max(m_widthField, u.getFieldWidth());
		}

		m_id = ++id_generator;
	}

	const std::string& Station::getItemName() const {
		return m_itemName;
	}

	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		return m_quantityInStock;
	}

	void Station::updateQuantity() {
		if (m_quantityInStock > 0) {
			--m_quantityInStock;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << std::setw(3) << std::setfill('0') << m_id;
		os << " | ";
		os << std::left << std::setw(14) << std::setfill(' ') << m_itemName;
		os << " | ";
		os << std::setw(6) << std::setfill('0') << m_serialNumber;
		os << " | ";
		if (full) {
			os << std::right << std::setw(4) << std::setfill(' ') << m_quantityInStock;
			os << " | ";
			os << m_stationDesc;
		}
		os << std::endl;
	}
}
