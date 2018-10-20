#include "Test.h"

#include "../Levels/Level2.h"
#include "../Levels/Level3.h"

#include <iostream>

namespace app
{
	unsigned int Test::m_numFramesRecorded = 0;
	unsigned int Test::m_numFramesToRecord = 0;
	std::vector<unsigned long long> Test::m_recordedChecksums;
	bool Test::m_overallPassed;

	void Test::run()
	{
		try
		{
			m_overallPassed = true;
			test1();
			test2();
			std::cin.get();
			
			if (m_overallPassed == false)
				LogUtil::showMessageBox("There were test failures. Check the log for more details!", "Test failures");
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

	void Test::test1()
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
		evaluate({ 278996400, 269567714, 269567714 });
	}

	void Test::test2()
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
		evaluate({ 269567714, 213569647, 213592135, 213601057, 213619058 });
	}

	void Test::record()
	{
		if (m_numFramesRecorded >= m_numFramesToRecord - 1)
			InputManager::getInstance()->setQuitEvent();

		long long checksum = computeFramebufferChecksum();
		m_recordedChecksums.push_back(checksum);
		LogUtil::logMessage("checksum: %lld", checksum);

		m_numFramesRecorded++;
	}

	void Test::evaluate(std::vector<unsigned long long> expectedChecksums)
	{
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
			m_overallPassed = false;
		}
		else
			LogUtil::logMessage("[PASSED]");
	}

	// Reference: https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
	// Reference: https://stackoverflow.com/questions/16538945/writing-uncompressed-tga-to-file-in-c
	// Note: For reading RGB/BGR values, you must set GL_PACK_ALIGNMENT to 1, because the default pack alignment of 4 means, 
	// that each horizontal line must be a multiple of 4 in size. If you use RGBA or ABGR, it is a multiple of 4 automatically
	// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes
	long long Test::computeFramebufferChecksum()
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