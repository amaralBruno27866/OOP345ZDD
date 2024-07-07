#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include "Directory.h"

namespace seneca {
	Directory::Directory(const std::string& name) {
		m_name = name;
	}

	Directory::~Directory() {
	}

	void Directory::update_parent_path(const std::string& new_path) {
		if (!new_path.empty() && new_path.back() == '/') {
			m_parent_path = new_path.substr(0, new_path.size() - 1);
		}
		else {
			m_parent_path = new_path;
		}

		for (auto& resource : m_contents) {
			resource->update_parent_path(path());
		}
	}

	NodeType Directory::type() const {
		return NodeType::DIR;
	}

	std::string Directory::path() const {
		if (!m_parent_path.empty() && m_parent_path.back() != '/') {
			return m_parent_path + "/" + m_name;
		}
		else {
			return m_parent_path + m_name;
		}
	}

	std::string Directory::name() const {
		return m_name;
	}

	int Directory::count() const {
		return static_cast<int>(m_contents.size());
	}

	size_t Directory::size() const {
		size_t total = 0;
		for (const auto& resource : m_contents) {
			total += resource->size();
		}

		return total;
	}

	Directory& Directory::operator+=(Resource* rsc)	{
		for (const auto& existing_resource : m_contents) {
			if (existing_resource->name() == rsc->name()) {
				throw std::runtime_error("Resource already exists");
			}
		}

		m_contents.emplace_back(rsc);
		rsc->update_parent_path(path());
		return *this;
	}

	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) const {
		Resource* foundResource = nullptr;
		bool isRecusive = std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end();
		auto it = m_contents.begin();
		// std::cout << "m_contents = " << m_contents.size() << "\n";
		while (it != m_contents.end() && foundResource == nullptr) {
			if ((*it)->type() == NodeType::DIR) {
				if ((*it)->name() == name) {
					foundResource = it->get();
				}else if (isRecusive) {
					Directory* dir = dynamic_cast<Directory*>(it->get());
					if (dir != nullptr) {
						foundResource = dir->find(name, flags);
					}
				}
			}
			else if ((*it)->type() == NodeType::FILE) {
				if ((*it)->name() == name) {
					foundResource = it->get();
				}else if (isRecusive) {
					Directory* dir = dynamic_cast<Directory*>(it->get());
					if (dir != nullptr) {
						foundResource = dir->find(name, flags);
					}
				}
			}
			++it;		
		}

		return foundResource;
	}

	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
		auto it = std::find_if(m_contents.begin(), m_contents.end(), [&name](const std::unique_ptr<Resource>& rsc) {
			return rsc->name() == name;
		});

		if (it == m_contents.end()) {
			throw std::runtime_error(name + " does not exist in " + this->name());
		}

		if ((*it)->type() == NodeType::DIR) {
			if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) {
				throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
			}
		}

		// If it's a file or a directory with RECURSIVE flag, remove it
		m_contents.erase(it);
	}

	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
		// Insert the total size of the directory
		os << "Total size: " << size() << " bytes\n";

		// Iterate through each resource in the directory
		for (const auto& resource : m_contents) {
			// Check the type of the resource and print the appropriate prefix
			if (resource->type() == NodeType::DIR) {
				os << "D | ";
				std::string nameWithSlash = resource->name() + "/";
				os << std::left << std::setw(15) << nameWithSlash << " | ";
			}
			else if (resource->type() == NodeType::FILE) {
				os << "F | ";
				os << std::left << std::setw(15) << resource->name() << " | ";
			}

			// Check if the LONG flag is present
			auto it = std::find(flags.begin(), flags.end(), FormatFlags::LONG);
			if (it != flags.end()) {
				// If the resource is a directory and the LONG flag is present
				if (resource->type() == NodeType::DIR) {
					// Dynamic cast to Directory* to access directory-specific methods
					auto dir = dynamic_cast<Directory*>(resource.get());
					// Print the count of resources in the directory, right-aligned within a width of 2
					os << std::right << std::setw(2) << dir->count() << " | ";
				}
				else {
					// If it's a file, just align the next field
					os << "   | ";
				}
				// For both files and directories, print the size, right-aligned within a width of 10
				std::string sizeBytes = std::to_string(resource->size()) + " bytes";
				os << std::right << std::setw(10) << sizeBytes << " |";
			}
			// End the line after printing each resource's information
			os << "\n";
		}
	}
}
