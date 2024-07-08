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
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include "Directory.h"

namespace seneca {
	// Constructor: Initializes a directory with a given name
	Directory::Directory(const std::string& name) {
		m_name = name;
	}

	// Destructor: Currently empty, but defined for potential future use and proper cleanup
	Directory::~Directory() {
	}

	// Updates the parent path of the directory and all its contents recursively
	void Directory::update_parent_path(const std::string& new_path) {
		// Ensure the parent path does not end with a slash, unless it's the root
		if (!new_path.empty() && new_path.back() == '/') {
			m_parent_path = new_path.substr(0, new_path.size() - 1);
		}
		else {
			m_parent_path = new_path;
		}

		// Update the parent path of each resource within the directory
		for (auto& resource : m_contents) {
			resource->update_parent_path(path());
		}
	}

	// Returns the type of the node, which is a directory in this case
	NodeType Directory::type() const {
		return NodeType::DIR;
	}

	// Constructs and returns the full path of the directory
	std::string Directory::path() const {
		// Add a slash between parent path and name if necessary
		if (!m_parent_path.empty() && m_parent_path.back() != '/') {
			return m_parent_path + "/" + m_name;
		}
		else {
			return m_parent_path + m_name;
		}
	}

	// Returns the name of the directory
	std::string Directory::name() const {
		return m_name;
	}

	// Returns the number of resources (files and directories) within the directory
	int Directory::count() const {
		return static_cast<int>(m_contents.size());
	}

	// Calculates and returns the total size of the directory by summing the sizes of its contents
	size_t Directory::size() const {
		size_t total = 0;
		for (const auto& resource : m_contents) {
			total += resource->size();
		}

		return total;
	}

	// Adds a resource to the directory, ensuring no duplicates, and updates the resource's parent path
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

	// Searches for a resource by name within the directory, optionally performing a recursive search
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) const {
		// First, search among the immediate children
		for (const auto& resource : m_contents) {
			if (name.rfind(resource->name(), 0) == 0) {
				return resource.get();
			}
		}

		// If not found and recursive search is enabled, search within subdirectories
		if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end()) {
			for (const auto& resource : m_contents) {
				if (resource->type() == seneca::NodeType::DIR) {
					Directory* dir = static_cast<Directory*>(resource.get());
					Resource* found = dir->find(name, flags);
					if (found) {
						return found;
					}
				}
			}
		}

		return nullptr; // Return nullptr if the resource is not found
	}

	// Removes a resource by name from the directory, with an option to recursively remove directories
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
		// Find the resource by name
		auto it = std::find_if(m_contents.begin(), m_contents.end(), [&name](const std::unique_ptr<Resource>& rsc) {
			return rsc->name() == name;
		});

		// If not found, throw an exception
		if (it == m_contents.end()) {
			throw std::runtime_error(name + " does not exist in " + this->name());
		}

		// If it's a directory and the recursive flag is not set, throw an exception
		if ((*it)->type() == NodeType::DIR) {
			if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) {
				throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
			}
		}

		// Remove the resource
		m_contents.erase(it);
	}

	// Displays the contents of the directory, with options for formatting the output
	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
		// Display the total size of the directory
		os << "Total size: " << size() << " bytes\n";

		// Iterate through each resource and display its information
		for (const auto& resource : m_contents) {
			// Display the type of the resource
			if (resource->type() == NodeType::DIR) {
				os << "D | ";
				std::string name = resource->name();
				// Ensure only one trailing slash is present
				if (name.back() != '/') {
					name += "/";
				}
				os << std::left << std::setw(15) << name << " | ";
			}
			else if (resource->type() == NodeType::FILE) {
				os << "F | ";
				os << std::left << std::setw(15) << resource->name() << " | ";
			}

			// If the LONG format flag is set, display additional information
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
