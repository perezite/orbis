#include "TestUtil.h"

#include "../Levels/Level2.h"
#include "../Levels/Level3.h"

#include <iostream>

namespace app
{
	unsigned int TestUtil::m_numFramesRecorded = 0;
	unsigned int TestUtil::m_numFramesToRecord = 0;
	std::vector<unsigned long long> TestUtil::m_recordedChecksums;
	bool TestUtil::m_passedOverall;

	bool TestUtil::execute(Level * level, unsigned int numFrames, std::string testcaseName)
	{
		LogUtil::logMessage(("Running testcase: " + testcaseName).c_str());

		srand(42);
		m_numFramesRecorded = 0;
		m_numFramesToRecord = numFrames;
		m_recordedChecksums.clear();
		TimeManager::getInstance()->setFixedUpdate(30);
		OrbisMain::getInstance()->setOnRenderedCallback(record);
		LevelManager::getInstance()->queueLevel(level);
		OrbisMain::getInstance()->run();
		return evaluate(testcaseName);
	}

	void TestUtil::record()
	{
		// we skip the first frame, because at this point the backbuffer either contains random data or the frontbuffer from a previous level
		if (m_numFramesRecorded == 0)
		{
			m_numFramesRecorded++;
			return;
		}

		if (m_numFramesRecorded >= m_numFramesToRecord)
			InputManager::getInstance()->setQuitEvent();

		unsigned long long checksum = computeFramebufferChecksum();
		m_recordedChecksums.push_back(checksum);
		LogUtil::logMessage("checksum: %lld", checksum);

		m_numFramesRecorded++;
	}

	bool TestUtil::evaluate(std::string identifier)
	{
		bool success = true;

		std::vector<unsigned long long> expectedChecksums = loadExpectedChecksums(identifier);
		
		if (expectedChecksums.size() == 0)
			expectedChecksums = handleNewTestcase(identifier);

		// get mismatches
		Exception::assert(m_recordedChecksums.size() == expectedChecksums.size(), "number of expected checksums is not equal to number of recorded checksums");
		std::vector<int> mismatches;
		for (unsigned int i = 0; i < m_recordedChecksums.size(); i++)
		{
			if (m_recordedChecksums[i] != expectedChecksums[i])
				mismatches.push_back(i);
		}

		// handle mismatches
		if (mismatches.size() > 0)
		{
			LogUtil::logMessage("[FAILED]");
			for (unsigned int i = 0; i < mismatches.size(); i++)
			{
				unsigned int frameIdx = mismatches[i];
				LogUtil::logMessage("mismatch in frame %d. Expected: %lld, Actual: %lld", frameIdx, expectedChecksums[frameIdx], m_recordedChecksums[frameIdx]);
			}

			LogUtil::logMessage("In case, the failures reflect intentional changes, enter (o) to (o)verwrite the current values");
			std::string str; std::getline(std::cin, str);
			if (str == "o")
				addOrUpdateRecordedChecksumsInTestfile(identifier);
			else
				success = false;
		}
		else
			LogUtil::logMessage("[PASSED]");

		return success;
	}

	std::vector<unsigned long long> TestUtil::handleNewTestcase(std::string identifier)
	{
		std::vector<unsigned long long> result;

		LogUtil::logMessage("No data found in the test-file. Press w to (w)rite the recorded data to the test file now");
		std::string str; std::getline(std::cin, str);
		if (str == "w")
		{
			addOrUpdateRecordedChecksumsInTestfile(identifier);
			result = m_recordedChecksums;
		}	
		else
			m_passedOverall = false;

		return result;
	}

	std::vector<unsigned long long> TestUtil::loadExpectedChecksums(std::string identifier)
	{
		std::string fullIdentifier = getFullIdentifier(identifier);

		std::vector<std::string> lines = AssetUtil::loadTextAssetLines("Testing/ExpectedChecksums.test");

		std::string line;
		for (unsigned int i = 0; i < lines.size(); i++)
			if (StringUtil::startsWith(lines[i], fullIdentifier))
				line = lines[i];

		std::vector<unsigned long long> result;
		if (line != "")
		{
			std::string json = StringUtil::split(line, " = ")[1];
			result = getChecksumsFromJson(json);
		}

		return result;
	}

	void TestUtil::addOrUpdateRecordedChecksumsInTestfile(std::string identifier)
	{
		std::string fullIdentifier = getFullIdentifier(identifier);
		std::vector<std::string> lines = AssetUtil::loadTextAssetLines("Testing/ExpectedChecksums.test");

		// remove line with old data
		for (unsigned int i = 0; i < lines.size(); i++) {
			if (StringUtil::startsWith(lines[i], fullIdentifier))
			{
				lines.erase(lines.begin() + i);
				break;
			}
		}

		// write new data
		std::ostringstream os;
		std::string text = StringUtil::join(lines, "\n");
		os << text << (text.length() > 0 ? "\n" : "") << fullIdentifier << " = " << getRecordedChecksumsAsJson();
		AssetUtil::saveTextAsset("Testing/ExpectedChecksums.test", os.str());
	}

	std::string TestUtil::getFullIdentifier(std::string identifier)
	{
		std::string identiferConfigurationPrefix;
		ORBIS_DEBUG(identiferConfigurationPrefix = "Debug_"; )
		ORBIS_RELEASE(identiferConfigurationPrefix = "Release_"; )
		return identiferConfigurationPrefix + identifier;
	}

	std::vector<unsigned long long> TestUtil::getChecksumsFromJson(std::string json)
	{
		std::vector<unsigned long long> result;
		std::string temp = StringUtil::remove(json, { " ", "{", "}" });
		std::vector<std::string> elems = StringUtil::split(temp, ",");

		std::istringstream is;
		unsigned long long number;
		for (unsigned int i = 0; i < elems.size(); i++)
		{
			std::istringstream(elems[i]) >> number;
			result.push_back(number);
		}
		return result;
	}

	std::string TestUtil::getRecordedChecksumsAsJson()
	{
		return "{" + StringUtil::join(m_recordedChecksums, ", ") + "}";
	}

	// Reference: https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
	// Reference: https://stackoverflow.com/questions/16538945/writing-uncompressed-tga-to-file-in-c
	// Note: For reading RGB/BGR values, you must set GL_PACK_ALIGNMENT to 1, because the default pack alignment of 4 means, 
	// that each horizontal line must be a multiple of 4 in size. If you use RGBA or ABGR, it is a multiple of 4 automatically
	// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes
	unsigned long long TestUtil::computeFramebufferChecksum()
	{
		Vector2D resolution = VideoManager::getInstance()->getWindow()->getResolution();
		unsigned int w = (unsigned int)resolution.x;
		unsigned int h = (unsigned int)resolution.y;

		GLubyte* pixels = new GLubyte[4 * w * h];
		GLubyte* normed_pixels = new GLubyte[3 * w * h];

		// read
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		normalizeChannels(normed_pixels, pixels, w * h);

		// compute checksum
		unsigned long long check = 0;
		for (unsigned int i = 0; i < 4 * w * h; i++)
			check += (unsigned int)pixels[i];

		// cleanup
		delete[] normed_pixels;
		delete[] pixels;

		return check;
	}

	void TestUtil::normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels)
	{
		for (unsigned int i = 0; i < num_pixels; i++)
		{
			output_pixels[i * 3] = input_pixels[i * 4 + 2];
			output_pixels[i * 3 + 1] = input_pixels[i * 4 + 1];
			output_pixels[i * 3 + 2] = input_pixels[i * 4];
		}
	}

	void TestUtil::writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height)
	{
		#ifdef __WIN32__
		short TGAhead[] = { 0, 2, 0, 0, 0, 0, (short)width, (short)height, 24 };
		// FILE *out = fopen("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Windows\\test.tga", "wb");
		FILE* out;
		errno_t err = fopen_s(&out, "D:\\Indie\\Development\\Simulo\\orbis\\bin\\Windows\\test.tga", "wb");
		fwrite(&TGAhead, sizeof(TGAhead), 1, out);
		fwrite(normalized_pixels, 3 * width * height, 1, out);
		fclose(out);
		#endif
	}
}