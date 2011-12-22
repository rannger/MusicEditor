#include <qdebug.h>
#include <string.h>
#include <unistd.h>
#include "madfunction.h"

int outputfd=-1;

enum mad_flow input(void *data,
                    struct mad_stream *stream)
{
    struct buffer *buffer = (struct buffer*)data;

    if (!buffer->length)
        return MAD_FLOW_STOP;

    mad_stream_buffer(stream, buffer->start, buffer->length);

    buffer->length = 0;

    return MAD_FLOW_CONTINUE;
}


signed int scale(mad_fixed_t sample)
{
    /* round */
    sample += (1L << (MAD_F_FRACBITS - 16));

    /* clip */
    if (sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;

    /* quantize */
    return sample >> (MAD_F_FRACBITS + 1 - 16);
}



enum mad_flow output(void *data,
                     struct mad_header const *header,
                     struct mad_pcm *pcm)
{
    unsigned int nchannels, nsamples;
    mad_fixed_t const *left_ch, *right_ch;
    unsigned char outputbyte=0;
    /* pcm->samplerate contains the sampling frequency */

    nchannels = pcm->channels;
    nsamples  = pcm->length;
    left_ch   = pcm->samples[0];
    right_ch  = pcm->samples[1];

    while (nsamples--) {
        signed int sample;

        /* output sample(s) in 16-bit signed little-endian PCM */

        sample = scale(*left_ch++);
//        putchar((sample >> 0) & 0xff);
//        putchar((sample >> 8) & 0xff);
        outputbyte=(sample >> 0) & 0xff;
        outputbyte=(sample >> 8) & 0xff;
        if (nchannels == 2) {
            sample = scale(*right_ch++);
//            putchar((sample >> 0) & 0xff);
//            putchar((sample >> 8) & 0xff);
            outputbyte=(sample >> 0) & 0xff;
            outputbyte=(sample >> 8) & 0xff;
        }
  }
    return MAD_FLOW_CONTINUE;
}



enum mad_flow error(void *data,
                    struct mad_stream *stream,
                    struct mad_frame *frame)
{
  struct buffer *buffer = (struct buffer*)data;
  char buff[1024];
  sprintf(buff, "decoding error 0x%04x (%s) at byte offset %u\n",
          stream->error, mad_stream_errorstr(stream),
          stream->this_frame - buffer->start);
  qDebug()<<buff;
  /* return MAD_FLOW_BREAK here to stop decoding (and propagate an error) */

//  if(stream->error)
//      return MAD_FLOW_BREAK;
  return MAD_FLOW_CONTINUE;
}


int decode(unsigned char const *start, unsigned long length)
{
    struct buffer buffer;
    struct mad_decoder decoder;
    int result;

    /* initialize our private message structure */

    buffer.start  = start;
    buffer.length = length;

    /* configure input, output, and error functions */

    mad_decoder_init(&decoder, &buffer,
                    input, 0 /* header */, 0 /* filter */, output,
                    error, 0 /* message */);

    /* start decoding */

    result = mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);

    /* release the decoder */

    mad_decoder_finish(&decoder);

    return result;
}

