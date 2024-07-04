#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include "File.h"
#include "Filesystem.h"

namespace seneca {
	std::vector<std::string> Filesystem::splitPath(const std::string& path) {
		std::vector<std::string> result;
		std::stringstream ss(path);
		std::string item;
		while (std::getline(ss, item, '/')) {
			if (!item.empty()) {
				result.push_back(item);
			}
		}
		return result;
	}

	Filesystem::Filesystem(const std::string& filename, const std::string& rootName) {
		m_root = new Directory(rootName.empty() ? "/" : rootName);
		m_current = m_root;
	}

	Filesystem::~Filesystem() {
		delete m_root;
	}

	Filesystem& Filesystem::operator+=(Resource* resource) {
		if (m_current) {
			*m_current += resource;
		}
		return *this;
	}

	Filesystem::Filesystem(Filesystem&& fls) noexcept : m_root(fls.m_root), m_current(fls.m_current) {
		fls.m_root = nullptr;
		fls.m_current = nullptr;
	}

	Filesystem& Filesystem::operator=(Filesystem&& fls) noexcept {
		if (this != &fls) {
			delete m_root; // Clean up current resources
			m_root = fls.m_root;
			m_current = fls.m_current;
			fls.m_root = nullptr;
			fls.m_current = nullptr;
		}
		return *this;
	}

	Directory* Filesystem::change_directory(const std::string& dirName) {
		if (dirName.empty()) {
			m_current = m_root;
		}
		else {
			Resource* found = m_current->find(dirName, {});
			if (!found) {
				throw std::invalid_argument("Directory not found: " + dirName);
			}
			if (found->type() != seneca::NodeType::DIR) {
				throw std::invalid_argument("Not a directory: " + dirName);
			}
			m_current = static_cast<Directory*>(found);
		}
		return m_current;
	}

	Directory* Filesystem::get_current_directory() const {
		return m_current;
	}

	void Filesystem::addDirectory(const std::string& dirPath) {
		auto components = splitPath(dirPath);
		Directory* current = m_root;
		for (const auto& dirName : components) {
			Resource* found = current->find(dirName, {});
			if (found && found->type() == seneca::NodeType::DIR) {
				current = static_cast<Directory*>(found);
			}
			else {
				auto newDir = new Directory(dirName);
				*current += newDir;
				current = newDir;
			}
		}
	}

	void Filesystem::addFile(const std::string& filePath, const std::string& fileContents) {
		auto components = splitPath(filePath);
		std::string fileName = components.back();
		components.pop_back();

		Directory* current = m_root;
		for (const auto& dirName : components) {
			Resource* found = current->find(dirName, {});
			if (found && found->type() == seneca::NodeType::DIR) {
				current = static_cast<Directory*>(found);
			}
			else {
				auto newDir = new Directory(dirName);
				*current += newDir;
				current = newDir;
			}
		}

		auto newFile = new File(fileName, fileContents);
		*current += newFile;
	}
}
