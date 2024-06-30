#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include <iostream>
#include <string>
#include "Resource.h"

namespace seneca {
	class File : public Resource {
		std::string m_content;
	public:
		File(const std::string& name, const std::string& content = " ");
		void update_parent_path(const std::string& new_path) override;
		NodeType type() const override;
		std::string path() const override;
		std::string name() const override;
		int count() const override;
		size_t size() const override;
	};
}
#endif // !SENECA_FILE_H
