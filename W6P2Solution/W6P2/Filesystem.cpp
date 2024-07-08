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
		std::ifstream file(filename);
		if (!file) {
			throw std::invalid_argument("File not found or cannot be opened: " + filename);
		}
		m_root = new Directory(rootName.empty() ? "/" : trim(rootName));
		m_current = m_root;

		std::string line;
		while (getline(file, line)) {
			// Trim whitespace from the entire line and skip empty lines
			line = trim(line);
			if (line.empty()) continue;

			// Determine if the line represents a file or a directory
			if (line.back() == '/') {
				// It's a directory
				addDirectory(trim(line));
			}
			else {
				// It's a file, split the line into path and content
				size_t separatorPos = line.find('|');
				std::string filePath = trim(line.substr(0, separatorPos));
				std::string fileContent = (separatorPos != std::string::npos) ? trim(line.substr(separatorPos + 1)) : "";
				addFile(filePath, fileContent);
			}
		}
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
			m_current = m_root; // Change to root if no directory name is provided
		}
		else {
			auto components = splitPath(dirName);
			Directory* newCurrent = m_root; // Start from the root directory

			for (const auto& component : components) {
				Resource* found = newCurrent->find(component, {});
				if (!found) {
					throw std::invalid_argument("Cannot change directory! " + component + " not found!");
				}
				if (found->type() != seneca::NodeType::DIR) {
					throw std::invalid_argument("Cannot change directory! " + component + " is not a directory!");
				}
				newCurrent = static_cast<Directory*>(found); // Update the current directory
			}
			m_current = newCurrent; // Successfully changed the directory
		}

		return m_current; // Return the new current directory
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
				// Directory exists, navigate into it
				current = static_cast<Directory*>(found);
			}
			else {
				// Directory doesn't exist, create and navigate into it
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

	std::string Filesystem::trim(const std::string& str) {
		size_t first = str.find_first_not_of(" \t");
		if (first == std::string::npos) return "";
		size_t last = str.find_last_not_of(" \t");
		return str.substr(first, (last - first + 1));
	}
}
