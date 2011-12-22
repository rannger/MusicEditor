#ifndef MADFUNCTION_H
#define MADFUNCTION_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
#ifndef __MINGW_H
#include <sys/mman.h>
#endif
# include "libmad/mad.h"

struct buffer {
  unsigned char const *start;
  unsigned long length;
};

enum mad_flow input(void *data,
                    struct mad_stream *stream);
signed int scale(mad_fixed_t sample);

enum mad_flow output(void *data,
                     struct mad_header const *header,
                     struct mad_pcm *pcm,
                     unsigned char* outputBuffer[]);

enum mad_flow error(void *data,
                    struct mad_stream *stream,
                    struct mad_frame *frame);

int decode(unsigned char const *start, unsigned long length);
#endif // MADFUNCTION_H
