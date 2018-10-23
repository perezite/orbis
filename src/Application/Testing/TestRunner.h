#include "../../Orbis/Orbis.h"
using namespace orb;

#include <string>

namespace app
{
	class TestRunner
	{
	public:
		static bool executeTestcase(Level* level, unsigned int numFrames, std::string testcaseName);

	protected:

		static void record();

		static bool evaluate(std::string identifier);

		static std::vector<unsigned long long> handleFirstRun(std::string identifier);

		static std::vector<unsigned long long> loadChecksumsFromFile(std::string identifier);

		static std::vector<unsigned long long> updateChecksumsInFile(std::string identifier);

		static std::string getFullIdentifier(std::string identifier);

		static std::vector<unsigned long long> getChecksumsFromJson(std::string json);

		static unsigned long long computeFramebufferChecksum();

		static void normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels);

		static void writePixelsToFile(GLubyte* normalized_pixels, unsigned short width, unsigned short height);

	private:
		static unsigned int m_numFramesRecorded;

		static unsigned int m_numFramesToRecord;

		static std::vector<unsigned long long> m_recordedChecksums;
	};
}