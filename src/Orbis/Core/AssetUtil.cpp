#include "AssetUtil.h"

#include "../Libraries/SDL.h"

#include "../../Base/Base.h"
using namespace base;

namespace
{
	std::string GetAssetFolderPath()
	{
		#ifdef WIN32
			return EnvironmentUtil::combinePath({ EnvironmentUtil::getExecutableDirectoryPath(), "..", "Assets" });
		#endif
		
		#ifdef __ANDROID__
			return "";
		#endif
	}
}

namespace orb
{
	std::string AssetUtil::assetPathToFilePath(std::string assetPath)
	{
		return EnvironmentUtil::combinePath({ GetAssetFolderPath(), assetPath });
	}

	void AssetUtil::saveTextAsset(std::string assetPath, std::string text)
	{
		std::string filePath = assetPathToFilePath(assetPath);

		SDL_RWops *writer = SDL_RWFromFile_Checked(filePath.c_str(), "w");
		size_t len = SDL_strlen(text.c_str());

		SDL_RWwrite(writer, text.c_str(), 1, len);
		SDL_RWclose(writer);
	}

	std::string AssetUtil::loadTextAsset(std::string assetPath)
	{
		std::string filePath = assetPathToFilePath(assetPath);

		// setup
		SDL_RWops* reader = SDL_RWFromFile_Checked(filePath.c_str(), "r");
		Sint64 fileSize = SDL_RWsize(reader);
		char* data = (char*)malloc((size_t)fileSize + 1);

		Sint64 totalSize = 0;
		Sint64 lastSize = 0;

		// read
		do
		{
			lastSize = SDL_RWread(reader, &data[totalSize], sizeof(char), (size_t)(fileSize - totalSize));
			totalSize += lastSize;
		} while (totalSize < fileSize && lastSize != 0);
		data[totalSize] = '\0';
		SDL_RWclose(reader);

		// check
		Exception::assert(totalSize == fileSize, "Could not load file '" + assetPath + "'");

		return data;
	}

	std::vector<std::string> AssetUtil::loadTextAssetLines(std::string assetPath)
	{
		std::vector<std::string> result;
		std::string text = loadTextAsset(assetPath);
		std::vector<std::string> lines = StringUtil::split(text, "\n");

		for (unsigned int i = 0; i < lines.size(); i++)
				result.push_back(lines[i]);

		return result;
	}


	bool AssetUtil::textAssetExists(std::string assetPath)
	{
		std::string filePath = assetPathToFilePath(assetPath);
		SDL_RWops* reader = SDL_RWFromFile(filePath.c_str(), "r");
		bool exists = reader != NULL;

		SDL_RWclose(reader);
		return exists;
	}

	std::string AssetUtil::getLineStartingWith(std::string assetPath, std::string startString)
	{
		std::vector<std::string> lines = AssetUtil::loadTextAssetLines(assetPath);

		// find line starting with identifier
		std::string line;
		for (unsigned int i = 0; i < lines.size(); i++)
			if (StringUtil::startsWith(lines[i], startString))
				line = lines[i];

		return line;
	}

	void AssetUtil::updateLineStartingWith(std::string assetPath, std::string startString, std::string newContent)
	{
		std::vector<std::string> lines = AssetUtil::loadTextAssetLines("Testing/ExpectedChecksums.test");

		// remove line with old data
		for (unsigned int i = 0; i < lines.size(); i++) {
			if (StringUtil::startsWith(lines[i], startString)) {
				lines.erase(lines.begin() + i);
				break;
			}
		}

		// write new data
		std::ostringstream os;
		std::string text = StringUtil::join(lines, "\n");
		os << text << (text.length() > 0 ? "\n" : "") << newContent;
		AssetUtil::saveTextAsset("Testing/ExpectedChecksums.test", os.str());
	}


}