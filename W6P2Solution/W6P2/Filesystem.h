#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include <string>
#include <stdexcept>
#include "Directory.h"
#include "Resource.h"

namespace seneca {
	class Filesystem {
	private:
		Directory* m_root;
		Directory* m_current;

		std::vector<std::string> splitPath(const std::string& path);
	public:
		Filesystem(const std::string& filename, const std::string& rootName = "");
		~Filesystem();
		Filesystem(const Filesystem& fls) = delete;
		Filesystem& operator=(const Filesystem& fls) = delete;
		Filesystem& operator+=(Resource*);
		Filesystem(Filesystem&& fls) noexcept;
		Filesystem& operator=(Filesystem&& fls) noexcept;
		Directory* change_directory(const std::string& dirName = " ");
		Directory* get_current_directory() const;

		void addDirectory(const std::string& dirPath);
		void addFile(const std::string& filePath, const std::string& fileContents);

		std::string trim(const std::string& str);
	};
}

#endif // !SENECA_FILESYSTEM_H
