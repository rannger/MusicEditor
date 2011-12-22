#ifndef CONFIG_H
#define CONFIG_H
#include <_mingw.h>
/* Define to enable diagnostic debugging support. */
/* #undef DEBUG */

/* Define to enable experimental code. */
/* #undef EXPERIMENTAL */
/* Set to 1 if the compile is GNU GCC. */

#define COMPILER_IS_GCC 1

/* Target processor clips on negative float to int conversion. */
#define CPU_CLIPS_NEGATIVE 1

/* Target processor clips on positive float to int conversion. */
#define CPU_CLIPS_POSITIVE 0

/* Target processor is big endian. */
#define CPU_IS_BIG_ENDIAN 0

/* Target processor is little endian. */
#define CPU_IS_LITTLE_ENDIAN 1

/* Set to 1 to enable experimental code. */
#define ENABLE_EXPERIMENTAL_CODE 0

/* Major version of GCC or 3 otherwise. */
#define GCC_MAJOR_VERSION 4

/* Define to 1 if you have the `calloc' function. */
#define HAVE_CALLOC 1

/* Define to 1 if you have the `ceil' function. */
#define HAVE_CEIL 1

/* Set to 1 if S_IRGRP is defined. */
#define HAVE_DECL_S_IRGRP 0

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1



/* Set to 1 if the compile supports the struct hack. */
#define HAVE_FLEXIBLE_ARRAY 1

/* Define to 1 if you have the `floor' function. */
#define HAVE_FLOOR 1

/* Define to 1 if you have the `fmod' function. */
#define HAVE_FMOD 1

/* Define to 1 if you have the `free' function. */
#define HAVE_FREE 1

/* Define to 1 if you have the `fstat' function. */
#define HAVE_FSTAT 1

/* Define to 1 if you have the `fsync' function. */
/* #undef HAVE_FSYNC */

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `gmtime' function. */
#define HAVE_GMTIME 1

/* Define to 1 if you have the `gmtime_r' function. */
/* #undef HAVE_GMTIME_R */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define if you have C99's lrint function. */
#define HAVE_LRINT 1

/* Define if you have C99's lrintf function. */
#define HAVE_LRINTF 1

/* Define to 1 if you have the `lseek' function. */
#define HAVE_LSEEK 1

/* Define to 1 if you have the `malloc' function. */
#define HAVE_MALLOC 1


/* Define to 1 if you have the `open' function. */
#define HAVE_OPEN 1

/* Define to 1 if you have the `pread' function. */
/* #undef HAVE_PREAD */

/* Define to 1 if you have the `pwrite' function. */
/* #undef HAVE_PWRITE */

/* Define to 1 if you have the `read' function. */
#define HAVE_READ 1

/* Define to 1 if you have the `realloc' function. */
#define HAVE_REALLOC 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Set to 1 if you have libsqlite3. */
#define HAVE_SQLITE3 0

/* Define to 1 if the system has the type `ssize_t'. */
#define HAVE_SSIZE_T 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
/* #undef HAVE_SYS_WAIT_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `write' function. */
#define HAVE_WRITE 1

/* Set to 1 if compiling for MacOSX */
#define OS_IS_MACOSX 0

/* Set to 1 if compiling for Win32 */

#ifdef __MINGW_H
#define OS_IS_WIN32 1
#else
#define OS_IS_WIN32 0
#endif


/* Set to maximum allowed value of sf_count_t type. */
#define SF_COUNT_MAX 0x7FFFFFFFFFFFFFFFLL

/* The size of a `double', as computed by sizeof. */
#define SIZEOF_DOUBLE (sizeof(double))

/* The size of a `float', as computed by sizeof. */
#define SIZEOF_FLOAT (sizeof(float))

/* The size of a `int64_t', as computed by sizeof. */
#define SIZEOF_INT64_T 8

/* The size of a `loff_t', as computed by sizeof. */
/* #undef SIZEOF_LOFF_T */

/* The size of a `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG (8)

/* The size of a `off64_t', as computed by sizeof. */
/* #undef SIZEOF_OFF64_T */

/* The size of a `off_t', as computed by sizeof. */
#define SIZEOF_OFF_T (4)

/* Set to sizeof (long) if unknown. */
#define SIZEOF_SF_COUNT_T (4)

/* The size of a `short', as computed by sizeof. */
#define SIZEOF_SHORT (sizeof(short))

/* The size of a `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T (sizeof(size_t))

/* The size of a `ssize_t', as computed by sizeof. */
#define SIZEOF_SSIZE_T (sizeof(ssize_t))

/* The size of a `void*', as computed by sizeof. */
#define SIZEOF_VOIDP (sizeof(void*))

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Set to long if unknown. */
#define TYPEOF_SF_COUNT_T __int64

/* Set to 1 to use the native windows API */

//#ifdef __MINGW_H

//#else
//#define USE_WINDOWS_API 0
//#endif
#define USE_WINDOWS_API 0

/* Define to 1 if you have the `pipe' function. */
/* #undef HAVE_PIPE */

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
/* #undef HAVE_SYS_WAIT_H */

/* Name of package */
#define PACKAGE "musiceditor"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "support@underbit.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Music Editor"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Music Editor 0.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "musiceditor"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.1"

///* The size of a `int', as computed by sizeof. */
//#define SIZEOF_INT (sizeof(int))

///* The size of a `long', as computed by sizeof. */
//#define SIZEOF_LONG (sizeof(long))

///* The size of a `long long', as computed by sizeof. */
//#define SIZEOF_LONG_LONG 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.15.1b"

#ifndef __cplusplus
/* #undef inline */
#endif

#endif // CONFIG_H
