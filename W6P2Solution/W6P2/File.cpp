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

#include "File.h"

namespace seneca {
	// Constructor: Initializes a file with a given name and content
	File::File(const std::string& name, const std::string& content)
	: m_content(content) {
		m_name = name;
	}

	// Updates the parent path of the file
	void File::update_parent_path(const std::string& new_path) {
		// m_parent_path = new_path;
		if (!new_path.empty() && new_path.back() == '/') {
			m_parent_path = new_path.substr(0, new_path.size() - 1);
		}
		else {
			m_parent_path = new_path;
		}
	}

	// Returns the type of the node, which is a file in this case
	NodeType File::type() const {
		return NodeType::FILE;
	}

	// Constructs and returns the full path of the file
	std::string File::path() const {
		// return m_parent_path + m_name;
		if (!m_parent_path.empty() && m_parent_path.back() != '/') {
			return m_parent_path + "/" + m_name;
		}
		else {
			return m_parent_path + m_name;
		}
	}

	// Returns the name of the file
	std::string File::name() const {
		return m_name;
	}

	// Returns the count of the file, which is always -1
	int File::count() const {
		return -1;
	}

	// Returns the size of the file
	size_t File::size() const {
		return m_content.size();
	}
}
