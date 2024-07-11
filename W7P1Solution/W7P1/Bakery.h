#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

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

		// Custom constructor to initialize members
		BakedGood(BakedType t = BakedType::BREAD, std::string desc = "", int life = 0, int stk = 0, double prc = 0.0);
	};

	class Bakery {
	private:
		std::vector<BakedGood> goods;

	public:
		Bakery(const std::string& filename);
		void showGoods(std::ostream& os) const;
	};

	std::string trim(const std::string& str);
	std::ostream& operator<<(std::ostream& out, const BakedGood& b);
}

#endif // !SENECA_BAKERY_H
