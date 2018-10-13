#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Core/LogUtil.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Libraries/SDL.h"
#include "../Engine/Settings.h"

#include "../../Base/Base.h"
using namespace base;

namespace 
{
	void normalizeChannels(unsigned char* output_pixels, unsigned char* input_pixels, unsigned int num_pixels)
	{
		for (unsigned int i = 0; i < num_pixels; i++)
		{
			output_pixels[i * 3] = input_pixels[i * 4 + 2];
			output_pixels[i * 3 + 1] = input_pixels[i * 4 + 1];
			output_pixels[i * 3 + 2] = input_pixels[i * 4];
		}
	}

	// Reference: https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
	// Reference: https://stackoverflow.com/questions/16538945/writing-uncompressed-tga-to-file-in-c
	// Note: For reading RGB/BGR values, you must set GL_PACK_ALIGNMENT to 1, because the default pack alignment of 4 means, 
	// that each horizontal line must be a multiple of 4 in size. If you use RGBA or ABGR, it is a multiple of 4 automatically
	// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes
	// 
	void dumpScreen()
	{
		const int W = 10;
		const int H = 10;

		FILE   *out = fopen("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Windows\\test.tga", "wb");
		unsigned char   pixels[4 * W * H];
		unsigned char   normed_pixels[3 * W * H];
		short  TGAhead[] = { 0, 2, 0, 0, 0, 0, W, H, 24 };

		glReadPixels(200, 300, W, H, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		normalizeChannels(normed_pixels, pixels, W * H);
		fwrite(&TGAhead, sizeof(TGAhead), 1, out);
		fwrite(normed_pixels, 3 * W * H, 1, out);
		fclose(out);

		/*const int W = 11;
		const int H = 11;

		FILE   *out = fopen("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Windows\\test.tga", "wb");
		char   pixel_data[3 * W * H];
		short  TGAhead[] = { 0, 2, 0, 0, 0, 0, W, H, 24 };

 		glReadPixels(200, 300, W, H, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);
		fwrite(&TGAhead, sizeof(TGAhead), 1, out);
		fwrite(pixel_data, 3 * W * H, 1, out);
		fclose(out);*/
		
		/*const int W = 100;
		const int H = 100;

		unsigned char pixels[4 * W * H];
		unsigned char pixelsWithoutAlpha[3 * W * H];
		short TGAhead[] = { 0, 2, 0, 0, 0, 0, W, H, 24};

		glReadPixels(200, 300, W, H, GL_BGR, GL_UNSIGNED_BYTE, &(pixelsWithoutAlpha[0]));		// GLES only accepts GL_RGBA/GL_UNSIGNED_BYTE, see: http://docs.gl/es2/glReadPixels
		// normalizeChannels(pixelsWithoutAlpha, pixels, W * H);	

		// temp
		//unsigned int temp[3 * W * H];
		//for (unsigned int i = 0; i < (3 * W*H); i++)
		//	temp[i] = pixels[i];

		#ifdef __WIN32__
			FILE *out = fopen("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Windows\\test.tga", "wb");
			fwrite(&TGAhead, sizeof(TGAhead), 1, out);
			fwrite(pixelsWithoutAlpha, 3 * W * H, 1, out);
			fclose(out);
		#endif
		*/
	}
}

namespace orb
{
	OrbisMain* OrbisMain::getInstance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::run()
	{
		LevelManager* level = LevelManager::getInstance();
		InputManager* input = InputManager::getInstance();

		m_startTicks = TimeManager::getInstance()->getTicks();
		m_numFrames = 0;

		while (true)
		{
			input->update();
			if (input->hasQuitEvent())
				break;

			level->update();
			level->render();

			static int counter = 0;
			counter++;
			if (counter == 4)
			{
				dumpScreen();
			}

			#if defined(ORBIS_LOG_PERFORMANCE)
				logPerformance();
			#endif
		}

		level->clear();
	}

	void OrbisMain::logPerformance()
	{
		m_numFrames++;
		if (TimeManager::getInstance()->getTicks() - m_startTicks > 1000)
		{
			// track current performance
			float currentPerformance = 1000.0f / float(m_numFrames);
			m_startTicks += 1000;
			m_numFrames = 0;

			// track performance
			m_samples.push_back(currentPerformance);
			float median = MathUtil::median(m_samples);
			
			LogUtil::logMessage("current: %f ms, median: %f ms, samples: %d", currentPerformance, median, m_samples.size());
		}
	}
}