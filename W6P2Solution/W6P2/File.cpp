#define _CRT_SECURE_NO_WARNINGS

#include "File.h"

namespace seneca {
	File::File(const std::string& name, const std::string& content)
	: m_content(content) {
		m_name = name;
	}

	void File::update_parent_path(const std::string& new_path) {
		m_parent_path = new_path;
	}

	NodeType File::type() const {
		return NodeType::FILE;
	}

	std::string File::path() const {
		return m_parent_path + m_name;
	}

	std::string File::name() const {
		return m_name;
	}

	int File::count() const {
		return -1;
	}

	size_t File::size() const {
		return m_content.size();
	}
}
