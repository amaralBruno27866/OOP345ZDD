/*/////////////////////////////////////////////////////////////////////////
				  Workshop - #6 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include "Bakery.h"

namespace seneca {
	Bakery::Bakery(const std::string& filename) {
		std::ifstream file(filename);
		if (!file) throw std::runtime_error("File cannot be opened.");

		std::string line;
		while (std::getline(file, line)) {
			BakedGood good;

			std::string typeStr = trim(line.substr(0, 8));
			good.type = (typeStr == "Bread") ? BakedType::BREAD : BakedType::PASTERY;
			good.description = trim(line.substr(8, 20));
			good.shelfLife = std::stoi(trim(line.substr(28, 14)));
			good.stock = std::stoi(trim(line.substr(42, 8)));
			good.price = std::stod(trim(line.substr(50, 6)));

			goods.push_back(good);
		}
	}

	void Bakery::showGoods(std::ostream& os) const {
		std::for_each(goods.begin(), goods.end(), [&os](const BakedGood& good) {
			os << good << "\n";
		});

		auto totalStock = std::accumulate(goods.begin(), goods.end(), 0, [](int total, const BakedGood& good) {
			return total + good.stock;
		});

		auto totalPrice = std::accumulate(goods.begin(), goods.end(), 0.0, [](double total, const BakedGood& good) {
			return total += good.price;
		});

		os << "Total stock: " << totalStock << "\n";
		os << "Total price: " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
	}

	void Bakery::sortBakery(const std::string& field) {
		auto func = [field](const BakedGood& g1, const BakedGood& g2) {
			bool ret{ false };

			if (field == "Description") {
				ret = g1.description < g2.description;
			}
			else if (field == "Shelf") {
				ret = g1.shelfLife < g2.shelfLife;
			}
			else if (field == "Stock") {
				ret = g1.stock < g2.stock;
			}
			else if (field == "Price") {
				ret = g1.price < g2.price;
			}

			return ret;
			};

		std::sort(goods.begin(), goods.end(), func);
	}

	std::vector<BakedGood> Bakery::combine(const Bakery& other) {
		std::vector<BakedGood> combined = goods;
		combined.insert(combined.end(), other.goods.begin(), other.goods.end());
		std::sort(combined.begin(), combined.end(), [](const BakedGood& a, const BakedGood& b) {
			return a.price < b.price;
		});
		return combined;
	}

	bool Bakery::inStock(const std::string& description, BakedType type) const {
		return std::any_of(goods.begin(), goods.end(), [&description, &type](const BakedGood& good) {
			return good.description == description && good.type == type && good.stock > 0;
		});
	}

	std::list<BakedGood> Bakery::outOfStock(BakedType type) const	{
		std::list<BakedGood> outOfStockItems;
		std::copy_if(goods.begin(), goods.end(), std::back_inserter(outOfStockItems), [&type](const BakedGood& good) {
			return good.type == type && good.stock == 0;
		});
		return outOfStockItems;
	}

	std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
		out << "* " << std::left << std::setw(10) << ((b.type == BakedType::BREAD) ? "Bread" : "Pastry");
		out << " * " << std::left << std::setw(20) << b.description;
		out << " * " << std::left << std::setw(5) << b.shelfLife;
		out << " * " << std::left << std::setw(5) << b.stock;
		out << " * " << std::right << std::setw(8) << std::fixed << std::setprecision(2) << b.price;
		out << " * ";

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
