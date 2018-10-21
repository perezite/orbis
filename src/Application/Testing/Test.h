#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	class Test
	{
	public:
		static void run();

	protected:
		static void testLevel2();

		 static void testLevel3();

	protected:
		static void record();

		static void evaluate(std::string identifier);

		static std::vector<unsigned long long> loadExpectedChecksums(std::string identifier);

		static void addOrUpdateRecordedChecksumsInTestfile(std::string identifier);

		static std::string getFullIdentifier(std::string identifier);

		static std::vector<unsigned long long> getChecksumsFromJson(std::string json);

		static std::string getRecordedChecksumsAsJson();

		static unsigned long long computeFramebufferChecksum();

		static void normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels);

		static void writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height);

	private:
		static unsigned int m_numFramesRecorded;

		static unsigned int m_numFramesToRecord;

		static std::vector<unsigned long long> m_recordedChecksums;

		static bool m_passedOverall;
	};
}