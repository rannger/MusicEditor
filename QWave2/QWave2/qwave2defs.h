#ifndef _qwave2defs_h_
#define _qwave2defs_h_

#define MAXCACHEPAGES 120

#ifdef __FreeBSD__
#define nearbyint rint
#endif

#if defined(__GNUC__) && __GNUC__ < 3
#define and &&
#define or ||
#define nearbyint rint
#define trunc rint
#endif

#ifdef _MSC_VER
#define and &&
#define or ||
#define nearbyint(x) (double)((x)>=0?int((x)+.5):int((x)-.5))
#define trunc(x) (double)((int)(x))
#endif 

#ifdef _MSC_VER
#ifdef QWAVE_MAKE_DLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif
						 
#endif

