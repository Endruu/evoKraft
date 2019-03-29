#ifndef __H_DEBUGTRACE__
#define __H_DEBUGTRACE__

#pragma once

#include <iostream>

// debug level 0 - don't print debug data
// debug level 1 - print received game status objects
// debug level 2 - print TCP socket messages
#define DEBUG 0

#if DEBUG > 1
	#define debug std::cout
#else
	class NullBuffer : public std::streambuf
	{
	public:
		int overflow(int c) { return c; }
	};

	NullBuffer null_buffer;
	std::ostream debug(&null_buffer);
#endif // DEBUG > 1

#endif // __H_DEBUGTRACE__
