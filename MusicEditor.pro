#-------------------------------------------------
#
# Project created by QtCreator 2011-12-09T14:44:07
#
#-------------------------------------------------

#QT       += core gui
QT        += phonon
TARGET = MusicEditor
TEMPLATE = app

DEFINES += FPM_DEFAULT \
    HAVE_CONFIG_H \
    HAVE_MPGLIB

INCLUDEPATH += . \
./libsndfile \
./libsndfile/G72x \
./libsndfile/GSM610 \
./lame \
./lame/mpglib


SOURCES += main.cpp\
        mainwindow.cpp \
    libsndfile/xi.c \
    libsndfile/wve.c \
    libsndfile/wav_w64.c \
    libsndfile/wav.c \
    libsndfile/w64.c \
    libsndfile/vox_adpcm.c \
    libsndfile/voc.c \
    libsndfile/ulaw.c \
    libsndfile/txw.c \
    libsndfile/svx.c \
    libsndfile/strings.c \
    libsndfile/sndfile.c \
    libsndfile/sds.c \
    libsndfile/sd2.c \
    libsndfile/rx2.c \
    libsndfile/raw.c \
    libsndfile/pvf.c \
    libsndfile/pcm.c \
    libsndfile/paf.c \
    libsndfile/ogg.c \
    libsndfile/nist.c \
    libsndfile/ms_adpcm.c \
    libsndfile/mat5.c \
    libsndfile/mat4.c \
    libsndfile/macos.c \
    libsndfile/macbinary3.c \
    libsndfile/ircam.c \
    libsndfile/interleave.c \
    libsndfile/ima_adpcm.c \
    libsndfile/htk.c \
    libsndfile/gsm610.c \
    libsndfile/g72x.c \
    libsndfile/float32.c \
    libsndfile/flac.c \
    libsndfile/file_io.c \
    libsndfile/dwvw.c \
    libsndfile/dwd.c \
    libsndfile/double64.c \
    libsndfile/dither.c \
    libsndfile/common.c \
    libsndfile/command.c \
    libsndfile/caf.c \
    libsndfile/broadcast.c \
    libsndfile/avr.c \
    libsndfile/au.c \
    libsndfile/alaw.c \
    libsndfile/aiff.c \
    libsndfile/GSM610/table.c \
    libsndfile/GSM610/short_term.c \
    libsndfile/GSM610/rpe.c \
    libsndfile/GSM610/preprocess.c \
    libsndfile/GSM610/lpc.c \
    libsndfile/GSM610/long_term.c \
    libsndfile/GSM610/gsm_option.c \
    libsndfile/GSM610/gsm_encode.c \
    libsndfile/GSM610/gsm_destroy.c \
    libsndfile/GSM610/gsm_decode.c \
    libsndfile/GSM610/gsm_create.c \
    libsndfile/GSM610/decode.c \
    libsndfile/GSM610/code.c \
    libsndfile/GSM610/add.c \
    libsndfile/G72x/g723_40.c \
    libsndfile/G72x/g723_24.c \
    libsndfile/G72x/g723_16.c \
    libsndfile/G72x/g721.c \
    libsndfile/G72x/g72x_.c \
    libmad/version.c \
    libmad/timer.c \
    libmad/synth.c \
    libmad/stream.c \
    libmad/minimad.c \
    libmad/layer12.c \
    libmad/layer3.c \
    libmad/huffman.c \
    libmad/frame.c \
    libmad/fixed.c \
    libmad/decoder.c \
    libmad/bit.c \
    lame/VbrTag.c \
    lame/vbrquantize.c \
    lame/util.c \
    lame/takehiro.c \
    lame/tables.c \
    lame/set_get.c \
    lame/reservoir.c \
    lame/quantize_pvt.c \
    lame/quantize.c \
    lame/psymodel.c \
    lame/presets.c \
    lame/newmdct.c \
    lame/mpglib_interface.c \
    lame/lame.c \
    lame/id3tag.c \
    lame/gain_analysis.c \
    lame/fft.c \
    lame/encoder.c \
    lame/bitstream.c \
    lame/vector/xmm_quantize_sub.c \
    lame/mpglib/tabinit.c \
    lame/mpglib/layer2.c \
    lame/mpglib/layer1.c \
    lame/mpglib/interface.c \
    lame/mpglib/decode_i386.c \
    lame/mpglib/dct64_i386.c \
    lame/mpglib/layer3_.c \
    lame/mpglib/common_.c \
    lame/version_.c



HEADERS  += mainwindow.h \
    libsndfile/wav_w64.h \
    libsndfile/sndfile.h \
    libsndfile/sfendian.h \
    libsndfile/sfconfig.h \
    libsndfile/sf_unistd.h \
    libsndfile/float_cast.h \
    libsndfile/config.h \
    libsndfile/common.h \
    libsndfile/GSM610/gsm.h \
    libsndfile/GSM610/gsm610_priv.h \
    libsndfile/GSM610/config.h \
    libsndfile/G72x/g72x_priv.h \
    libsndfile/G72x/g72x.h \
    libmad/version.h \
    libmad/timer.h \
    libmad/synth.h \
    libmad/stream.h \
    libmad/mad.h \
    libmad/layer12.h \
    libmad/layer3.h \
    libmad/huffman.h \
    libmad/global.h \
    libmad/frame.h \
    libmad/fixed.h \
    libmad/decoder.h \
    libmad/config.h \
    libmad/bit.h \
    lame/VbrTag.h \
    lame/vbrquantize.h \
    lame/util.h \
    lame/tables.h \
    lame/set_get.h \
    lame/reservoir.h \
    lame/quantize_pvt.h \
    lame/quantize.h \
    lame/psymodel.h \
    lame/newmdct.h \
    lame/machine.h \
    lame/lameerror.h \
    lame/lame-analysis.h \
    lame/lame_global_flags.h \
    lame/l3side.h \
    lame/id3tag.h \
    lame/gain_analysis.h \
    lame/fft.h \
    lame/encoder.h \
    lame/config.h \
    lame/bitstream.h \
    lame/lame.h \
    lame/vector/lame_intrin.h \
    lame/mpglib/tabinit.h \
    lame/mpglib/mpglib.h \
    lame/mpglib/mpg123.h \
    lame/mpglib/layer3.h \
    lame/mpglib/layer2.h \
    lame/mpglib/layer1.h \
    lame/mpglib/l2tables.h \
    lame/mpglib/interface.h \
    lame/mpglib/huffman.h \
    lame/mpglib/decode_i386.h \
    lame/mpglib/dct64_i386.h \
    lame/mpglib/common.h \
    lame/version.h


FORMS    +=

OTHER_FILES += \
    libmad/sf_table.dat \
    libmad/rq_table.dat \
    libmad/qc_table.dat \
    libmad/imdct_s.dat \
    libmad/D.dat




























































































