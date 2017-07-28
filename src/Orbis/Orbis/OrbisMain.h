#pragma once

#if defined WIN32 
	#define ORBIS_MAIN() int main(int argc, char* args[])
#elif defined __ANDROID__
	#define ORBIS_MAIN() extern "C" int android_main(int argc, char *args[])
#else
	#error Operating system not supported
#endif