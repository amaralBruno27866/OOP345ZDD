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
	};
}
#endif // !SENECA_DIRECTORY_H
