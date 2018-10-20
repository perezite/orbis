#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	class Test
	{
	public:
		static void run();

	protected:
		static void test1();

		static void test2();

	protected: 
		static void record();

		static long long computeFramebufferChecksum();

		static void normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels);

		static void writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height);

	private:
		static unsigned int m_numFramesRecorded;

		static unsigned int m_numFramesToRecord;
	};
}