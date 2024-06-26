#ifndef SENECA_STATIONS_H
#define SENECA_STATIONS_H

#include <iostream>
#include <string>
#include "Utilities.h"

namespace seneca {
	class Station {
		int m_id;
		std::string m_itemName;
		std::string m_stationDesc;
		size_t m_serialNumber;
		size_t m_quantityInStock;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SENECA_STATIONS_H
