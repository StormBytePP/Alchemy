#pragma once

#include <StormByte/platform.h>

#ifdef WINDOWS
	#ifdef Alchemy_EXPORTS
		#define ALCHEMY_PUBLIC	__declspec(dllexport)
  	#else
      	#define ALCHEMY_PUBLIC	__declspec(dllimport)
  	#endif
  	#define ALCHEMY_PRIVATE
#else
    #define ALCHEMY_PUBLIC		__attribute__ ((visibility ("default")))
    #define ALCHEMY_PRIVATE		__attribute__ ((visibility ("hidden")))
#endif
