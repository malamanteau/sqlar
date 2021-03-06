#pragma once

#include <string>
#include <memory>
#include <array>
#include <vector>
#include <cstdint>

#include "../../HandyCpp/Handy.hpp"
#include "../../HandyCpp/HandyExtended.hpp"

namespace SQLarLib
{
	// Unlike the official "sqlar" utility, this API does not support encryption extentions for SQLite (aka "see").
	struct FileArchive
	{
		ADDPRIVATE_STRUCT_NOCOPY

		enum class Mode : uint32_t
		{
			Create,         // Create a new archive and then open. Fail is file already exists.
			Create_Replace, // Create a new archive and then open. Delete and replace if the file already exists.
			Open_Create,    // Open existing archive, or if the file doesn't already exist--creates a new one and opens it.
			Open,           // Open existing archive, or fail if the file doesn't already exist.
			OpenReadOnly    // Open existing archive, or fail if the file doesn't already exist. DO NOT ALLOW WRITE OPERATIONS.
		};

		static Handy::ResultV<FileArchive *> Open(std::filesystem::path filepath_in, Mode mode);
		static void                          AbortRollback(FileArchive * fa);

		Handy::Result                        Get   (std::string key, std::vector<uint8_t>       & buffer);
		Handy::Result                        Put   (std::string key, std::vector<uint8_t> const & buffer, bool compressed = false);
		Handy::Result                        Put   (std::string key, void * buffer, size_t numBytes,      bool compressed = false);
		bool                                 Has   (std::string key);
		Handy::Result                        Delete(std::string key);

		std::vector<std::string>             KeyNames();

		void                                 PrintKeyNames();
		void                                 PrintKeyInfos();

		virtual ~FileArchive();

	private: 
		FileArchive();
	};

}
