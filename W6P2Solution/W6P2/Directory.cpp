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
		m_parent_path = new_path;
		for (auto& resource : m_contents) {
			resource->update_parent_path(path());
		}
	}

	NodeType Directory::type() const {
		return NodeType::DIR;
	}

	std::string Directory::path() const {
		return m_parent_path + m_name;
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

		while (it != m_contents.end() && foundResource == nullptr) {
			if ((*it)->name() == name) {
				foundResource = it->get();
			}
			else if (isRecusive && (*it)->type() == NodeType::DIR) {
				Directory* dir = dynamic_cast<Directory*>(it->get());
				if (dir != nullptr) {
					foundResource = dir->find(name, flags);
				}
			}
			++it;
		}

		return foundResource;
	}

	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
		auto it = std::find_if(m_contents.begin(), m_contents.end(), [name](const std::unique_ptr<Resource>& rsc) {
			return rsc->name() == name;
		});

		if(it == m_contents.end()) {
			throw std::runtime_error(name + "does not exist in" + this->name());
		}

		if((*it)->type() == NodeType::DIR && std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end()) {
			throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
		}

		m_contents.erase(it);
	}

	void Directory::display(std::ostream& os, const std::vector<OpFlags>& flags) const {
		os << "Total size: " << size() << " bytes\n";
		for (const auto& resource : m_contents) {
			if (resource->type() == NodeType::DIR) {
				os << "D | " << std::left << std::setw(15) << resource->name() << " | ";
				if (std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end()) {
					os << std::right << std::setw(2) << dynamic_cast<Directory*>(resource.get())->count() << " | " << std::setw(10) << resource->size() << " bytes |\n";
				}
				else {
					os << "\n";
				}
			}
			else if (resource->type() == NodeType::FILE) {
				os << "F | " << std::left << std::setw(15) << resource->name() << " | ";
				if (std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end()) {
					os << "   | " << std::right << std::setw(10) << resource->size() << " bytes |\n";
				}
				else {
					os << "\n";
				}
			}
		}
	}
}
