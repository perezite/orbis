#include "Test.h"

#include "../Levels/Level2.h"
#include "../Levels/Level3.h"

#include <iostream>

namespace app
{
	unsigned int Test::m_numFramesRecorded = 0;
	unsigned int Test::m_numFramesToRecord = 0;
	std::vector<unsigned long long> Test::m_recordedChecksums;
	bool Test::m_passedOverall;

	void Test::run()
	{
		try
		{
			m_passedOverall = true;
			testLevel2();
			testLevel3();
			
			if (m_passedOverall == false)
				LogUtil::showMessageBox("There were test failures. Check the log for more details", "Test failures");
			else
				LogUtil::showMessageBox("All tests passed", "Tests successful");
		}
		catch (Exception e)
		{
			LogUtil::logMessage("%.1023s", e.what().c_str());

			LogUtil::showMessageBox(e.what(), "Exception");

			#if defined(_DEBUG)
				throw e;
			#endif
		}
	}

	void Test::testLevel2()
	{
		LogUtil::logMessage("Testing Level 2...");
		srand(42);
		m_numFramesRecorded = 0;
		m_numFramesToRecord = 3;
		m_recordedChecksums.clear();
		TimeManager::getInstance()->setFixedUpdate(30);
		OrbisMain::getInstance()->setOnRenderedCallback(record);
		LevelManager::getInstance()->queueLevel(new Level2());
		OrbisMain::getInstance()->run();
		evaluate("level2");
	}

	void Test::testLevel3()
	{
		LogUtil::logMessage("Testing Level 3...");

		srand(42);
		m_numFramesRecorded = 0;
		m_numFramesToRecord = 5;
		m_recordedChecksums.clear();
		TimeManager::getInstance()->setFixedUpdate(30);
		OrbisMain::getInstance()->setOnRenderedCallback(record);
		LevelManager::getInstance()->queueLevel(new Level3());
		OrbisMain::getInstance()->run();
		evaluate("level3");
	}

	void Test::record()
	{
		// we skip the first frame, because at this point the backbuffer either contains random data or the frontbuffer from a previous level
		if (m_numFramesRecorded == 0)
		{
			m_numFramesRecorded = 1;
			return;
		}

		if (m_numFramesRecorded >= m_numFramesToRecord)
			InputManager::getInstance()->setQuitEvent();

		unsigned long long checksum = computeFramebufferChecksum();
		m_recordedChecksums.push_back(checksum);
		LogUtil::logMessage("checksum: %lld", checksum);

		m_numFramesRecorded++;
	}

	void Test::evaluate(std::string identifier)
	{
		std::vector<unsigned long long> expectedChecksums = loadExpectedChecksums(identifier);

		if (expectedChecksums.size() == 0)
		{
			LogUtil::logMessage("[NO DATA]");
			LogUtil::logMessage("No data found in the test-file. Press w to (w)rite the recorded data to the test file now");
			std::string str; std::getline(std::cin, str);
			if (str == "w")
				addOrUpdateRecordedChecksumsInTestfile(identifier);
			else
				m_passedOverall = false;
			return;
		}

		Exception::assert(m_recordedChecksums.size() == expectedChecksums.size(), "number of expected checksums is not equal to number of recorded checksums");

		std::vector<int> mismatches;
		for (unsigned int i = 0; i < m_recordedChecksums.size(); i++)
		{
			if (m_recordedChecksums[i] != expectedChecksums[i])
				mismatches.push_back(i);
		}

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

			m_passedOverall = false;
		}
		else
			LogUtil::logMessage("[PASSED]");
	}

	std::vector<unsigned long long> Test::loadExpectedChecksums(std::string identifier)
	{
		std::string fullIdentifier = getFullIdentifier(identifier);

		std::string text = AssetUtil::loadTextAsset("Testing/ExpectedChecksums.test");
		std::vector<std::string> lines = StringUtil::split(text, "\n");

		std::string line = "";
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

	void Test::addOrUpdateRecordedChecksumsInTestfile(std::string identifier)
	{
		std::string fullIdentifier = getFullIdentifier(identifier);
		std::string text = AssetUtil::loadTextAsset("Testing/ExpectedChecksums.test");

		// remove old data
		std::vector<std::string> lines = StringUtil::split(text, "\n");
		for (unsigned int i = 0; i < lines.size(); i++) {
			if (StringUtil::startsWith(lines[i], fullIdentifier))
			{
				lines.erase(lines.begin() + i);
				break;
			}
		}
		text = StringUtil::join(lines, "\n");

		// write checksums to file
		std::ostringstream os;
		if (text.length() > 0)
			os << std::endl;
		os << fullIdentifier << " = " << getRecordedChecksumsAsJson();
		text = text + os.str();
		AssetUtil::saveTextAsset("Testing/ExpectedChecksums.test", text);
	}

	std::string Test::getFullIdentifier(std::string identifier)
	{
		std::string identiferConfigurationPrefix;
		ORBIS_DEBUG(identiferConfigurationPrefix = "Debug_"; )
		ORBIS_RELEASE(identiferConfigurationPrefix = "Release_"; )
		std::string fullIdentifier = identiferConfigurationPrefix + identifier;

		return fullIdentifier;
	}

	std::vector<unsigned long long> Test::getChecksumsFromJson(std::string json)
	{
		std::string temp = json;
		temp.erase(std::remove(temp.begin(), temp.end(), '{'), temp.end());
		temp.erase(std::remove(temp.begin(), temp.end(), '}'), temp.end());
		temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());

		std::vector<std::string> elems = StringUtil::split(temp, ",");
		std::vector<unsigned long long> result;
		std::istringstream is;
		for (unsigned int i = 0; i < elems.size(); i++)
		{
			unsigned long long number;
			std::istringstream(elems[i]) >> number;
			result.push_back(number);
		}
		return result;
	}

	std::string Test::getRecordedChecksumsAsJson()
	{
		std::ostringstream os;
		os << "{";
		for (unsigned int i = 0; i < m_recordedChecksums.size(); i++)
		{
			os << m_recordedChecksums[i];
			if (i != m_recordedChecksums.size() - 1)
				os << ", ";
		}
			
		os << "}";
		return os.str();
	}

	// Reference: https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
	// Reference: https://stackoverflow.com/questions/16538945/writing-uncompressed-tga-to-file-in-c
	// Note: For reading RGB/BGR values, you must set GL_PACK_ALIGNMENT to 1, because the default pack alignment of 4 means, 
	// that each horizontal line must be a multiple of 4 in size. If you use RGBA or ABGR, it is a multiple of 4 automatically
	// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes
	unsigned long long Test::computeFramebufferChecksum()
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

	void Test::normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels)
	{
		for (unsigned int i = 0; i < num_pixels; i++)
		{
			output_pixels[i * 3] = input_pixels[i * 4 + 2];
			output_pixels[i * 3 + 1] = input_pixels[i * 4 + 1];
			output_pixels[i * 3 + 2] = input_pixels[i * 4];
		}
	}

	void Test::writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height)
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