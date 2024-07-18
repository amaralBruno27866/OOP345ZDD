#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <memory>

namespace seneca {
	enum class Err_Status {
		Err_Success,
		Err_NotFound,
		Err_OutOfMemory,
	};

	class Database {
	private:
		static std::shared_ptr<Database> instance;
		std::string keys[20];
		std::string values[20];
		std::string filename;
		int entryCount = 0;

		Database(const std::string& filename);
	public:
		static std::shared_ptr<Database> getInstance(const std::string& filename);
		Err_Status GetValue(const std::string& key, std::string& value);
		Err_Status SetValue(const std::string& key, const std::string& value);
		~Database();
	};
}

#endif // !SENECA_DATABASE_H
