#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
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
	}

	Filesystem::~Filesystem() {
	}

	Filesystem& Filesystem::operator+=(Resource*) {
		// TODO: insert return statement here
	}

	Filesystem::Filesystem(Filesystem&& fls) noexcept {
	}

	Filesystem& Filesystem::operator=(Filesystem&& fls) noexcept {
		// TODO: insert return statement here
	}

	Directory* Filesystem::change_directory(const std::string& dirName) {
		return nullptr;
	}

	Directory* Filesystem::get_current_directory() const {
		return nullptr;
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
