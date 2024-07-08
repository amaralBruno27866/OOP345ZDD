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
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include "File.h"
#include "Filesystem.h"

namespace seneca {
	// Splits a given path into its components based on '/' delimiter
	std::vector<std::string> Filesystem::splitPath(const std::string& path) {
		std::vector<std::string> result;
		std::stringstream ss(path);
		std::string item;
		while (std::getline(ss, item, '/')) {
			if (!item.empty()) {
				result.push_back(item); // Add non-empty components to the result
			}
		}
		return result;
	}

	// Constructor: Initializes the filesystem with a given filename and root directory name
	Filesystem::Filesystem(const std::string& filename, const std::string& rootName) {
		std::ifstream file(filename);
		if (!file) {
			throw std::invalid_argument("File not found or cannot be opened: " + filename);
		}
		m_root = new Directory(rootName.empty() ? "/" : trim(rootName)); // Create the root directory
		m_current = m_root; // Start from the root directory

		std::string line;
		while (getline(file, line)) {
			// Trim whitespace from the entire line and skip empty lines
			line = trim(line); // Trim whitespace from the entire line
			if (line.empty()) continue; // Skip empty lines

			// Determine if the line represents a file or a directory
			if (line.back() == '/') {
				// It's a directory
				addDirectory(trim(line)); // Add the directory to the filesystem
			}
			else {
				// It's a file, split the line into path and content
				size_t separatorPos = line.find('|');
				std::string filePath = trim(line.substr(0, separatorPos));
				std::string fileContent = (separatorPos != std::string::npos) ? trim(line.substr(separatorPos + 1)) : "";
				addFile(filePath, fileContent); // Add the file to the filesystem
			}
		}
	}

	// Destructor: Cleans up the root directory and all its contents
	Filesystem::~Filesystem() {
		delete m_root; // Clean up the root directory and all its contents
	}

	// Overloaded operator+=: Adds a resource to the current directory
	Filesystem& Filesystem::operator+=(Resource* resource) {
		if (m_current) {
			*m_current += resource; // Add the resource to the current directory
		}
		return *this;
	}

	// Move constructor: Moves the resources from the source filesystem to the new filesystem
	Filesystem::Filesystem(Filesystem&& fls) noexcept : m_root(fls.m_root), m_current(fls.m_current) {
		fls.m_root = nullptr;
		fls.m_current = nullptr;
	}

	// Move assignment operator: Moves the resources from the source filesystem to the current filesystem
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

	// Changes the current directory to the specified directory name
	Directory* Filesystem::change_directory(const std::string& dirName) {
		if (dirName.empty()) {
			m_current = m_root; // Change to root if no directory name is provided
		}
		else {
			auto components = splitPath(dirName);
			Directory* newCurrent = m_root; // Start from the root directory

			// Navigate through the directory components to find the new current directory
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

	// Returns the current directory
	Directory* Filesystem::get_current_directory() const {
		return m_current;
	}

	// Adds a directory to the filesystem based on the given directory path
	void Filesystem::addDirectory(const std::string& dirPath) {
		auto components = splitPath(dirPath); // Split the directory path into components
		Directory* current = m_root; // Start from the root directory

		// Navigate through the directory components to add the new directory
		for (const auto& dirName : components) {
			// Find the directory in the current directory
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

	// Adds a file to the filesystem based on the given file path and contents
	void Filesystem::addFile(const std::string& filePath, const std::string& fileContents) {
		auto components = splitPath(filePath); // Split the file path into components
		std::string fileName = components.back(); // Extract the file name
		components.pop_back(); // Remove the file name from the components

		// Navigate through the directory components to find the directory to add the file
		Directory* current = m_root;
		// Start from the root directory
		for (const auto& dirName : components) {
			// Find the directory in the current directory
			Resource* found = current->find(dirName, {});
			// Directory exists, navigate into it
			if (found && found->type() == seneca::NodeType::DIR) {
				current = static_cast<Directory*>(found);
			}
			else {
				auto newDir = new Directory(dirName);
				*current += newDir;
				current = newDir;
			}
		}

		// Add the file to the directory
		auto newFile = new File(fileName, fileContents);
		*current += newFile; // Add the file to the directory
	}

	// Trims leading and trailing whitespace from a given string
	std::string Filesystem::trim(const std::string& str) {
		size_t first = str.find_first_not_of(" \t"); // Find the first non-whitespace character
		if (first == std::string::npos) return ""; // Return an empty string if no non-whitespace character is found
		size_t last = str.find_last_not_of(" \t"); // Find the last non-whitespace character
		return str.substr(first, (last - first + 1)); // Return the trimmed string
	}
}
