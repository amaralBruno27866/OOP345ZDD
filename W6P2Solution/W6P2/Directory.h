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

#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include <vector>
#include <memory>
#include "Resource.h"

namespace seneca {
	class Directory : public Resource {
		std::vector<std::unique_ptr<Resource>> m_contents;
	public:
		Directory(const std::string& name);
		virtual ~Directory();

		void update_parent_path(const std::string& new_path) override;
		NodeType type() const override;
		std::string path() const override;
		std::string name() const override;
		int count() const override;
		size_t size() const override;

		Directory& operator+=(Resource* rsc);
		Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {}) const;

		// Copy and move operations are not allowed
		Directory(const Directory&) = delete;
		Directory& operator=(const Directory&) = delete;
		Directory(Directory&&) = delete;
		Directory& operator=(Directory&&) = delete;

		// Update Directory Module
		void remove(const std::string& name, const std::vector<OpFlags>& flags = {});
		void display(std::ostream& os, const std::vector<FormatFlags>& flags = {}) const;
	};
}
#endif // !SENECA_DIRECTORY_H
