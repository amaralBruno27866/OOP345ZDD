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
		Directory* change_directory(const std::string& dirName = "");
		Directory* get_current_directory() const;

		void addDirectory(const std::string& dirPath);
		void addFile(const std::string& filePath, const std::string& fileContents);

		std::string trim(const std::string& str);
	};
}

#endif // !SENECA_FILESYSTEM_H
