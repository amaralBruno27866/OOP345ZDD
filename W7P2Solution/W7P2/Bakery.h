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

#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <list>

namespace seneca {
	enum class BakedType {
		BREAD, PASTERY
	};

	struct BakedGood {
		BakedType type;
		std::string description;
		int shelfLife;
		int stock;
		double price;

		BakedGood(BakedType t = BakedType::BREAD, std::string desc = {}, int life = {}, int stk = {}, double prc = {});
	};

	class Bakery {
	private:
		std::vector<BakedGood> goods;

	public:
		Bakery(const std::string& filename);
		void showGoods(std::ostream& os) const;

		void sortBakery(const std::string& field);
		std::vector<BakedGood> combine(const Bakery& other);
		bool inStock(const std::string& description, BakedType type) const;
		std::list<BakedGood> outOfStock(BakedType type) const;
	};

	std::string trim(const std::string& str);
	std::ostream& operator<<(std::ostream& out, const BakedGood& b);
}

#endif // !SENECA_BAKERY_H
