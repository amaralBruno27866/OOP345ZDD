#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Bakery.h"

namespace seneca {
	Bakery::Bakery(const std::string& filename) {
		std::ifstream file(filename);
		if (!file) throw std::runtime_error("File cannot be opened.");

		std::string line;
		while (std::getline(file, line)) {
			BakedGood good;

			// Parse BakedType
			std::string typeStr = trim(line.substr(0, 8));
			good.type = (typeStr == "Bread") ? BakedType::BREAD : BakedType::PASTERY;

			// Parse Description
			good.description = trim(line.substr(8, 20));

			// Parse ShelfLife
			good.shelfLife = std::stoi(trim(line.substr(28, 14)));

			// Parse Stock
			good.stock = std::stoi(trim(line.substr(42, 8)));

			// Parse Price
			good.price = std::stod(trim(line.substr(50, 6)));

			goods.push_back(good);
		}
	}

	void Bakery::showGoods(std::ostream& os) const {
		std::for_each(goods.begin(), goods.end(), [&os](const BakedGood& good) {
			os << good;
			});
	}

	std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
		// Use the trim function to clean up the description before printing
		std::string trimmedDescription = trim(b.description);

		out << "* " << std::left << std::setw(10) << ((b.type == BakedType::BREAD) ? "Bread" : "Pastery");
		out << " * " << std::left << std::setw(20) << trimmedDescription;
		out << " * " << std::left << std::setw(5) << b.shelfLife;
		out << " * " << std::left << std::setw(5) << b.stock;
		out << " * " << std::right << std::setw(8) << std::setprecision(2) << std::fixed << b.price;
		out << " *";
		out << std::endl;
		return out;
	}

	std::string trim(const std::string& str) {
		size_t first = str.find_first_not_of(" \t");
		if (first == std::string::npos) return "";
		size_t last = str.find_last_not_of(" \t");
		return str.substr(first, (last - first + 1));
	}

	BakedGood::BakedGood(BakedType t, std::string desc, int life, int stk, double prc)
		: type(t), description(std::move(desc)), shelfLife(life), stock(stk), price(prc) {}
}
