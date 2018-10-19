#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	class Test
	{
	public:
		static void run();

	private: 
		static void update();

		static long long computeFramebufferChecksum();

		static void normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels);

		static void writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height);
	};
}