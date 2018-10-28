#include "TestRunner.h"

#include "../Levels/Level2.h"
#include "../Levels/Level3.h"

#include <iostream>

namespace app
{
	unsigned int TestRunner::m_numFramesRecorded = 0;
	unsigned int TestRunner::m_numFramesToRecord = 0;
	std::vector<unsigned long long> TestRunner::m_recordedChecksums;

	bool TestRunner::executeTestcase(Level* level, unsigned int numFrames, std::string testcaseName)
	{
		LogUtil::logMessage(("Running testcase: " + testcaseName).c_str());

		srand(42);
		m_numFramesRecorded = 0;
		m_numFramesToRecord = numFrames;
		m_recordedChecksums.clear();
		TimeManager::instance()->setFixedUpdateTime(30);
		OrbisMain::getInstance()->setOnRenderedCallback(record);
		LevelManager::getInstance()->queueLevel(level);
		OrbisMain::getInstance()->run();
		return evaluate(testcaseName);
	}

	void TestRunner::record()
	{
		// we skip the first frame, because at this point the backbuffer either contains random data or the frontbuffer from a previous level
		if (m_numFramesRecorded == 0) {
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

	bool TestRunner::evaluate(std::string identifier)
	{
		bool success = true;

		std::vector<unsigned long long> expectedChecksums = loadChecksumsFromFile(identifier);

		// handle first run
		if (expectedChecksums.size() == 0)
		{
			if ("u" == InputManager::getInstance()->getConsoleLine("No data found in file. Press (u) to (u)pdate the file with the currently recorded data"))
				expectedChecksums = updateChecksumsInFile(identifier);
		}
		
		// collect mismatches
		std::vector<int> mismatches;
		for(unsigned int i = 0; i < expectedChecksums.size(); i++) {
			if (m_recordedChecksums[i] != expectedChecksums[i])
				mismatches.push_back(i);
		}

		// handle mismatches
		if (mismatches.size() > 0) {
			for (unsigned int i = 0; i < mismatches.size(); i++) {
				unsigned int frameIdx = mismatches[i];
				LogUtil::logMessage("mismatch in frame %d. Expected: %lld, Actual: %lld", frameIdx, expectedChecksums[frameIdx], m_recordedChecksums[frameIdx]);
			}

			if ("u" == InputManager::getInstance()->getConsoleLine("In case, the failures reflect intentional changes, enter (u) to (u)verwrite the current values"))
			{
				expectedChecksums = updateChecksumsInFile(identifier);
				mismatches.clear();
			}
		}

		// show errors
		if (mismatches.size() > 0 || m_recordedChecksums.size() != expectedChecksums.size()) {
			LogUtil::logMessage("[FAILED]");
			LogUtil::logMessage("There where mismatches between the expected checksums and the currently recorded checksums");
			success = false;
		}
		else
			LogUtil::logMessage("[PASSED]");

		return success;
	}

	std::vector<unsigned long long> TestRunner::handleFirstRun(std::string identifier)
	{
		std::vector<unsigned long long> result;

		if ("w" == InputManager::getInstance()->getConsoleLine("No data found in the test-file. Press w to (w)rite the recorded data to the test file now")) {
			updateChecksumsInFile(identifier);
			result = m_recordedChecksums;
		}	

		return result;
	}

	std::vector<unsigned long long> TestRunner::loadChecksumsFromFile(std::string identifier)
	{
		std::string fullIdentifier = getFullIdentifier(identifier);
		std::vector<unsigned long long> result;

		std::string line = AssetUtil::getLineStartingWith("Testing/ExpectedChecksums.test", fullIdentifier);
		if (line != "")
			return getChecksumsFromJson(StringUtil::split(line, " = ")[1]);

		return result;
	}

	std::vector<unsigned long long> TestRunner::updateChecksumsInFile(std::string identifier)
	{
		std::string fullIdentifier = getFullIdentifier(identifier);
		std::string newLine = fullIdentifier + " = " + JsonWriter::toJson(m_recordedChecksums);
		AssetUtil::updateLineStartingWith("Testing/ExpectedChecksums.test", fullIdentifier, newLine);

		return m_recordedChecksums;
	}

	std::string TestRunner::getFullIdentifier(std::string identifier)
	{
		std::string identiferConfigurationPrefix;
		ORBIS_DEBUG(identiferConfigurationPrefix = "Debug_"; )
		ORBIS_RELEASE(identiferConfigurationPrefix = "Release_"; )
		return identiferConfigurationPrefix + identifier;
	}

	std::vector<unsigned long long> TestRunner::getChecksumsFromJson(std::string json)
	{
		std::vector<unsigned long long> result;
		JsonReader reader(json);
		while (reader.hasNextElement())
			result.push_back(reader.getULongLong());
		return result;
	}

	// Reference: https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
	// Reference: https://stackoverflow.com/questions/16538945/writing-uncompressed-tga-to-file-in-c
	// Note: For reading RGB/BGR values, you must set GL_PACK_ALIGNMENT to 1, because the default pack alignment of 4 means, 
	// that each horizontal line must be a multiple of 4 in size. If you use RGBA or ABGR, it is a multiple of 4 automatically
	// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes
	unsigned long long TestRunner::computeFramebufferChecksum()
	{
		Vector2u resolution = VideoManager::getInstance()->getWindow()->getResolution();
		unsigned int w = resolution.x;
		unsigned int h = resolution.y;

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

	void TestRunner::normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels)
	{
		for (unsigned int i = 0; i < num_pixels; i++)
		{
			output_pixels[i * 3] = input_pixels[i * 4 + 2];
			output_pixels[i * 3 + 1] = input_pixels[i * 4 + 1];
			output_pixels[i * 3 + 2] = input_pixels[i * 4];
		}
	}

	void TestRunner::writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height)
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