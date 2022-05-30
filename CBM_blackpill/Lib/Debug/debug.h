#ifndef DEBUG_H_
#define DEBUG_H_

#define DBG_IO RS485_MODUBUS.io

#define ENABLE_DEBUG 1

#ifndef DEBUG_C_
	extern char debug_level;
#endif

#define DBL_QUIET 	-1
#define DBL_WARN	0
#define DBL_INFO	1
#define DBL_VERBOSE	2
#define DBL_DEBUG	3

#define DBL_DEFAULT DBL_DEBUG


#ifdef ENABLE_DEBUG

	// Define normal function prototypes

	void print_debug(const char *module, const char *text);
	void printf_debug(const char *module, const char *text, ...);

#else

	// Define empty inline functions

	inline void print_debug(const char *module, const char *text)
	{
		return;
	}

	inline void printf_debug(const char *module, const char *text, ...)
	{
		return;
	}

#endif

#endif /* DEBUG_H_ */
