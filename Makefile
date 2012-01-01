#############################################################################
# Makefile for building: MusicEditor
# Generated by qmake (2.01a) (Qt 4.7.0) on: ?? 1? 2 02:40:34 2012
# Project:  MusicEditor.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile MusicEditor.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DUNIX -DQT_PHONON_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/phonon -I/usr/include/qt4 -I/usr/include/qwt-qt4 -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include -I/usr/include/qt4/phonon_compat -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -L /usr/lib/ -lqwt-qt4 -L/usr/lib -lswscale -lavutil -lavformat -lavfilter -lavcodec -lavdevice -lphonon -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		ffmpeg.cpp \
		meaudiodecoder.cpp \
		meauidoencoder.cpp moc_mainwindow.cpp
OBJECTS       = main.o \
		mainwindow.o \
		ffmpeg.o \
		meaudiodecoder.o \
		meauidoencoder.o \
		moc_mainwindow.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		MusicEditor.pro
QMAKE_TARGET  = MusicEditor
DESTDIR       = 
TARGET        = MusicEditor

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: MusicEditor.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile MusicEditor.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile MusicEditor.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/MusicEditor1.0.0 || $(MKDIR) .tmp/MusicEditor1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/MusicEditor1.0.0/ && $(COPY_FILE) --parents OtherClass/ffmpeg.h mainwindow.h meaudiodecoder.h meauidoencoder.h .tmp/MusicEditor1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp ffmpeg.cpp meaudiodecoder.cpp meauidoencoder.cpp .tmp/MusicEditor1.0.0/ && (cd `dirname .tmp/MusicEditor1.0.0` && $(TAR) MusicEditor1.0.0.tar MusicEditor1.0.0 && $(COMPRESS) MusicEditor1.0.0.tar) && $(MOVE) `dirname .tmp/MusicEditor1.0.0`/MusicEditor1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/MusicEditor1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp
moc_mainwindow.cpp: /usr/include/phonon/audiooutput.h \
		/usr/include/phonon/phonon_export.h \
		/usr/include/phonon/abstractaudiooutput.h \
		/usr/include/phonon/phonondefs.h \
		/usr/include/phonon/medianode.h \
		/usr/include/phonon/path.h \
		/usr/include/phonon/objectdescription.h \
		/usr/include/phonon/phononnamespace.h \
		/usr/include/phonon/seekslider.h \
		/usr/include/phonon/mediaobject.h \
		/usr/include/phonon/mediasource.h \
		/usr/include/phonon/volumeslider.h \
		/usr/include/phonon/backendcapabilities.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		/usr/include/phonon/audiooutput.h \
		/usr/include/phonon/phonon_export.h \
		/usr/include/phonon/abstractaudiooutput.h \
		/usr/include/phonon/phonondefs.h \
		/usr/include/phonon/medianode.h \
		/usr/include/phonon/path.h \
		/usr/include/phonon/objectdescription.h \
		/usr/include/phonon/phononnamespace.h \
		/usr/include/phonon/seekslider.h \
		/usr/include/phonon/mediaobject.h \
		/usr/include/phonon/mediasource.h \
		/usr/include/phonon/volumeslider.h \
		/usr/include/phonon/backendcapabilities.h \
		OtherClass/ffmpeg.h \
		/usr/include/stdint.h \
		/usr/include/features.h \
		/usr/include/bits/predefs.h \
		/usr/include/sys/cdefs.h \
		/usr/include/bits/wordsize.h \
		/usr/include/gnu/stubs.h \
		/usr/include/gnu/stubs-32.h \
		/usr/include/bits/wchar.h \
		/usr/include/libavformat/avformat.h \
		/usr/include/time.h \
		/usr/include/bits/time.h \
		/usr/include/bits/types.h \
		/usr/include/bits/typesizes.h \
		/usr/include/xlocale.h \
		/usr/include/stdio.h \
		/usr/include/libio.h \
		/usr/include/_G_config.h \
		/usr/include/wchar.h \
		/usr/include/wctype.h \
		/usr/include/endian.h \
		/usr/include/bits/endian.h \
		/usr/include/bits/byteswap.h \
		/usr/include/bits/wchar2.h \
		/usr/include/bits/wchar-ldbl.h \
		/usr/include/gconv.h \
		/usr/include/bits/stdio-lock.h \
		/usr/include/bits/libc-lock.h \
		/usr/include/pthread.h \
		/usr/include/sched.h \
		/usr/include/bits/sched.h \
		/usr/include/bits/pthreadtypes.h \
		/usr/include/bits/setjmp.h \
		/usr/include/errno.h \
		/usr/include/bits/errno.h \
		/usr/include/linux/errno.h \
		/usr/include/asm/errno.h \
		/usr/include/asm-generic/errno.h \
		/usr/include/asm-generic/errno-base.h \
		/usr/include/gnu/option-groups.h \
		/usr/include/bits/libio-ldbl.h \
		/usr/include/bits/stdio_lim.h \
		/usr/include/bits/sys_errlist.h \
		/usr/include/getopt.h \
		/usr/include/ctype.h \
		/usr/include/bits/stdio.h \
		/usr/include/bits/stdio2.h \
		/usr/include/bits/stdio-ldbl.h \
		/usr/include/libavcodec/avcodec.h \
		/usr/include/libavutil/avutil.h \
		/usr/include/libavutil/common.h \
		/usr/include/inttypes.h \
		/usr/include/limits.h \
		/usr/include/bits/posix1_lim.h \
		/usr/include/bits/local_lim.h \
		/usr/include/linux/limits.h \
		/usr/include/bits/posix2_lim.h \
		/usr/include/bits/xopen_lim.h \
		/usr/include/math.h \
		/usr/include/bits/huge_val.h \
		/usr/include/bits/huge_valf.h \
		/usr/include/bits/huge_vall.h \
		/usr/include/bits/inf.h \
		/usr/include/bits/nan.h \
		/usr/include/bits/mathdef.h \
		/usr/include/bits/mathcalls.h \
		/usr/include/bits/mathinline.h \
		/usr/include/stdlib.h \
		/usr/include/bits/waitflags.h \
		/usr/include/bits/waitstatus.h \
		/usr/include/sys/types.h \
		/usr/include/sys/select.h \
		/usr/include/bits/select.h \
		/usr/include/bits/sigset.h \
		/usr/include/sys/sysmacros.h \
		/usr/include/alloca.h \
		/usr/include/bits/stdlib.h \
		/usr/include/bits/stdlib-ldbl.h \
		/usr/include/string.h \
		/usr/include/bits/string.h \
		/usr/include/bits/string2.h \
		/usr/include/bits/string3.h \
		/usr/include/libavutil/attributes.h \
		/usr/include/libavutil/mem.h \
		/usr/include/libavutil/error.h \
		/usr/include/libavutil/mathematics.h \
		/usr/include/libavutil/rational.h \
		/usr/include/libavutil/intfloat_readwrite.h \
		/usr/include/libavutil/log.h \
		/usr/include/libavutil/pixfmt.h \
		/usr/include/libavutil/avconfig.h \
		/usr/include/libavformat/avio.h \
		/usr/include/libavutil/fifo.h \
		/usr/include/libavutil/avstring.h \
		/usr/include/libavutil/adler32.h \
		/usr/include/libavutil/base64.h \
		/usr/include/libavutil/crc.h \
		/usr/include/libavdevice/avdevice.h \
		/usr/include/libavcodec/opt.h \
		/usr/include/libswscale/swscale.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp OtherClass/ffmpeg.h \
		/usr/include/stdint.h \
		/usr/include/features.h \
		/usr/include/bits/predefs.h \
		/usr/include/sys/cdefs.h \
		/usr/include/bits/wordsize.h \
		/usr/include/gnu/stubs.h \
		/usr/include/gnu/stubs-32.h \
		/usr/include/bits/wchar.h \
		/usr/include/libavformat/avformat.h \
		/usr/include/time.h \
		/usr/include/bits/time.h \
		/usr/include/bits/types.h \
		/usr/include/bits/typesizes.h \
		/usr/include/xlocale.h \
		/usr/include/stdio.h \
		/usr/include/libio.h \
		/usr/include/_G_config.h \
		/usr/include/wchar.h \
		/usr/include/wctype.h \
		/usr/include/endian.h \
		/usr/include/bits/endian.h \
		/usr/include/bits/byteswap.h \
		/usr/include/bits/wchar2.h \
		/usr/include/bits/wchar-ldbl.h \
		/usr/include/gconv.h \
		/usr/include/bits/stdio-lock.h \
		/usr/include/bits/libc-lock.h \
		/usr/include/pthread.h \
		/usr/include/sched.h \
		/usr/include/bits/sched.h \
		/usr/include/bits/pthreadtypes.h \
		/usr/include/bits/setjmp.h \
		/usr/include/errno.h \
		/usr/include/bits/errno.h \
		/usr/include/linux/errno.h \
		/usr/include/asm/errno.h \
		/usr/include/asm-generic/errno.h \
		/usr/include/asm-generic/errno-base.h \
		/usr/include/gnu/option-groups.h \
		/usr/include/bits/libio-ldbl.h \
		/usr/include/bits/stdio_lim.h \
		/usr/include/bits/sys_errlist.h \
		/usr/include/getopt.h \
		/usr/include/ctype.h \
		/usr/include/bits/stdio.h \
		/usr/include/bits/stdio2.h \
		/usr/include/bits/stdio-ldbl.h \
		/usr/include/libavcodec/avcodec.h \
		/usr/include/libavutil/avutil.h \
		/usr/include/libavutil/common.h \
		/usr/include/inttypes.h \
		/usr/include/limits.h \
		/usr/include/bits/posix1_lim.h \
		/usr/include/bits/local_lim.h \
		/usr/include/linux/limits.h \
		/usr/include/bits/posix2_lim.h \
		/usr/include/bits/xopen_lim.h \
		/usr/include/math.h \
		/usr/include/bits/huge_val.h \
		/usr/include/bits/huge_valf.h \
		/usr/include/bits/huge_vall.h \
		/usr/include/bits/inf.h \
		/usr/include/bits/nan.h \
		/usr/include/bits/mathdef.h \
		/usr/include/bits/mathcalls.h \
		/usr/include/bits/mathinline.h \
		/usr/include/stdlib.h \
		/usr/include/bits/waitflags.h \
		/usr/include/bits/waitstatus.h \
		/usr/include/sys/types.h \
		/usr/include/sys/select.h \
		/usr/include/bits/select.h \
		/usr/include/bits/sigset.h \
		/usr/include/sys/sysmacros.h \
		/usr/include/alloca.h \
		/usr/include/bits/stdlib.h \
		/usr/include/bits/stdlib-ldbl.h \
		/usr/include/string.h \
		/usr/include/bits/string.h \
		/usr/include/bits/string2.h \
		/usr/include/bits/string3.h \
		/usr/include/libavutil/attributes.h \
		/usr/include/libavutil/mem.h \
		/usr/include/libavutil/error.h \
		/usr/include/libavutil/mathematics.h \
		/usr/include/libavutil/rational.h \
		/usr/include/libavutil/intfloat_readwrite.h \
		/usr/include/libavutil/log.h \
		/usr/include/libavutil/pixfmt.h \
		/usr/include/libavutil/avconfig.h \
		/usr/include/libavformat/avio.h \
		/usr/include/libavutil/fifo.h \
		/usr/include/libavutil/avstring.h \
		/usr/include/libavutil/adler32.h \
		/usr/include/libavutil/base64.h \
		/usr/include/libavutil/crc.h \
		/usr/include/libavdevice/avdevice.h \
		/usr/include/libavcodec/opt.h \
		/usr/include/libswscale/swscale.h \
		mainwindow.h \
		/usr/include/phonon/audiooutput.h \
		/usr/include/phonon/phonon_export.h \
		/usr/include/phonon/abstractaudiooutput.h \
		/usr/include/phonon/phonondefs.h \
		/usr/include/phonon/medianode.h \
		/usr/include/phonon/path.h \
		/usr/include/phonon/objectdescription.h \
		/usr/include/phonon/phononnamespace.h \
		/usr/include/phonon/seekslider.h \
		/usr/include/phonon/mediaobject.h \
		/usr/include/phonon/mediasource.h \
		/usr/include/phonon/volumeslider.h \
		/usr/include/phonon/backendcapabilities.h \
		meaudiodecoder.h \
		meauidoencoder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

ffmpeg.o: ffmpeg.cpp OtherClass/ffmpeg.h \
		/usr/include/stdint.h \
		/usr/include/features.h \
		/usr/include/bits/predefs.h \
		/usr/include/sys/cdefs.h \
		/usr/include/bits/wordsize.h \
		/usr/include/gnu/stubs.h \
		/usr/include/gnu/stubs-32.h \
		/usr/include/bits/wchar.h \
		/usr/include/libavformat/avformat.h \
		/usr/include/time.h \
		/usr/include/bits/time.h \
		/usr/include/bits/types.h \
		/usr/include/bits/typesizes.h \
		/usr/include/xlocale.h \
		/usr/include/stdio.h \
		/usr/include/libio.h \
		/usr/include/_G_config.h \
		/usr/include/wchar.h \
		/usr/include/wctype.h \
		/usr/include/endian.h \
		/usr/include/bits/endian.h \
		/usr/include/bits/byteswap.h \
		/usr/include/bits/wchar2.h \
		/usr/include/bits/wchar-ldbl.h \
		/usr/include/gconv.h \
		/usr/include/bits/stdio-lock.h \
		/usr/include/bits/libc-lock.h \
		/usr/include/pthread.h \
		/usr/include/sched.h \
		/usr/include/bits/sched.h \
		/usr/include/bits/pthreadtypes.h \
		/usr/include/bits/setjmp.h \
		/usr/include/errno.h \
		/usr/include/bits/errno.h \
		/usr/include/linux/errno.h \
		/usr/include/asm/errno.h \
		/usr/include/asm-generic/errno.h \
		/usr/include/asm-generic/errno-base.h \
		/usr/include/gnu/option-groups.h \
		/usr/include/bits/libio-ldbl.h \
		/usr/include/bits/stdio_lim.h \
		/usr/include/bits/sys_errlist.h \
		/usr/include/getopt.h \
		/usr/include/ctype.h \
		/usr/include/bits/stdio.h \
		/usr/include/bits/stdio2.h \
		/usr/include/bits/stdio-ldbl.h \
		/usr/include/libavcodec/avcodec.h \
		/usr/include/libavutil/avutil.h \
		/usr/include/libavutil/common.h \
		/usr/include/inttypes.h \
		/usr/include/limits.h \
		/usr/include/bits/posix1_lim.h \
		/usr/include/bits/local_lim.h \
		/usr/include/linux/limits.h \
		/usr/include/bits/posix2_lim.h \
		/usr/include/bits/xopen_lim.h \
		/usr/include/math.h \
		/usr/include/bits/huge_val.h \
		/usr/include/bits/huge_valf.h \
		/usr/include/bits/huge_vall.h \
		/usr/include/bits/inf.h \
		/usr/include/bits/nan.h \
		/usr/include/bits/mathdef.h \
		/usr/include/bits/mathcalls.h \
		/usr/include/bits/mathinline.h \
		/usr/include/stdlib.h \
		/usr/include/bits/waitflags.h \
		/usr/include/bits/waitstatus.h \
		/usr/include/sys/types.h \
		/usr/include/sys/select.h \
		/usr/include/bits/select.h \
		/usr/include/bits/sigset.h \
		/usr/include/sys/sysmacros.h \
		/usr/include/alloca.h \
		/usr/include/bits/stdlib.h \
		/usr/include/bits/stdlib-ldbl.h \
		/usr/include/string.h \
		/usr/include/bits/string.h \
		/usr/include/bits/string2.h \
		/usr/include/bits/string3.h \
		/usr/include/libavutil/attributes.h \
		/usr/include/libavutil/mem.h \
		/usr/include/libavutil/error.h \
		/usr/include/libavutil/mathematics.h \
		/usr/include/libavutil/rational.h \
		/usr/include/libavutil/intfloat_readwrite.h \
		/usr/include/libavutil/log.h \
		/usr/include/libavutil/pixfmt.h \
		/usr/include/libavutil/avconfig.h \
		/usr/include/libavformat/avio.h \
		/usr/include/libavutil/fifo.h \
		/usr/include/libavutil/avstring.h \
		/usr/include/libavutil/adler32.h \
		/usr/include/libavutil/base64.h \
		/usr/include/libavutil/crc.h \
		/usr/include/libavdevice/avdevice.h \
		/usr/include/libavcodec/opt.h \
		/usr/include/libswscale/swscale.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ffmpeg.o ffmpeg.cpp

meaudiodecoder.o: meaudiodecoder.cpp meaudiodecoder.h \
		OtherClass/ffmpeg.h \
		/usr/include/stdint.h \
		/usr/include/features.h \
		/usr/include/bits/predefs.h \
		/usr/include/sys/cdefs.h \
		/usr/include/bits/wordsize.h \
		/usr/include/gnu/stubs.h \
		/usr/include/gnu/stubs-32.h \
		/usr/include/bits/wchar.h \
		/usr/include/libavformat/avformat.h \
		/usr/include/time.h \
		/usr/include/bits/time.h \
		/usr/include/bits/types.h \
		/usr/include/bits/typesizes.h \
		/usr/include/xlocale.h \
		/usr/include/stdio.h \
		/usr/include/libio.h \
		/usr/include/_G_config.h \
		/usr/include/wchar.h \
		/usr/include/wctype.h \
		/usr/include/endian.h \
		/usr/include/bits/endian.h \
		/usr/include/bits/byteswap.h \
		/usr/include/bits/wchar2.h \
		/usr/include/bits/wchar-ldbl.h \
		/usr/include/gconv.h \
		/usr/include/bits/stdio-lock.h \
		/usr/include/bits/libc-lock.h \
		/usr/include/pthread.h \
		/usr/include/sched.h \
		/usr/include/bits/sched.h \
		/usr/include/bits/pthreadtypes.h \
		/usr/include/bits/setjmp.h \
		/usr/include/errno.h \
		/usr/include/bits/errno.h \
		/usr/include/linux/errno.h \
		/usr/include/asm/errno.h \
		/usr/include/asm-generic/errno.h \
		/usr/include/asm-generic/errno-base.h \
		/usr/include/gnu/option-groups.h \
		/usr/include/bits/libio-ldbl.h \
		/usr/include/bits/stdio_lim.h \
		/usr/include/bits/sys_errlist.h \
		/usr/include/getopt.h \
		/usr/include/ctype.h \
		/usr/include/bits/stdio.h \
		/usr/include/bits/stdio2.h \
		/usr/include/bits/stdio-ldbl.h \
		/usr/include/libavcodec/avcodec.h \
		/usr/include/libavutil/avutil.h \
		/usr/include/libavutil/common.h \
		/usr/include/inttypes.h \
		/usr/include/limits.h \
		/usr/include/bits/posix1_lim.h \
		/usr/include/bits/local_lim.h \
		/usr/include/linux/limits.h \
		/usr/include/bits/posix2_lim.h \
		/usr/include/bits/xopen_lim.h \
		/usr/include/math.h \
		/usr/include/bits/huge_val.h \
		/usr/include/bits/huge_valf.h \
		/usr/include/bits/huge_vall.h \
		/usr/include/bits/inf.h \
		/usr/include/bits/nan.h \
		/usr/include/bits/mathdef.h \
		/usr/include/bits/mathcalls.h \
		/usr/include/bits/mathinline.h \
		/usr/include/stdlib.h \
		/usr/include/bits/waitflags.h \
		/usr/include/bits/waitstatus.h \
		/usr/include/sys/types.h \
		/usr/include/sys/select.h \
		/usr/include/bits/select.h \
		/usr/include/bits/sigset.h \
		/usr/include/sys/sysmacros.h \
		/usr/include/alloca.h \
		/usr/include/bits/stdlib.h \
		/usr/include/bits/stdlib-ldbl.h \
		/usr/include/string.h \
		/usr/include/bits/string.h \
		/usr/include/bits/string2.h \
		/usr/include/bits/string3.h \
		/usr/include/libavutil/attributes.h \
		/usr/include/libavutil/mem.h \
		/usr/include/libavutil/error.h \
		/usr/include/libavutil/mathematics.h \
		/usr/include/libavutil/rational.h \
		/usr/include/libavutil/intfloat_readwrite.h \
		/usr/include/libavutil/log.h \
		/usr/include/libavutil/pixfmt.h \
		/usr/include/libavutil/avconfig.h \
		/usr/include/libavformat/avio.h \
		/usr/include/libavutil/fifo.h \
		/usr/include/libavutil/avstring.h \
		/usr/include/libavutil/adler32.h \
		/usr/include/libavutil/base64.h \
		/usr/include/libavutil/crc.h \
		/usr/include/libavdevice/avdevice.h \
		/usr/include/libavcodec/opt.h \
		/usr/include/libswscale/swscale.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o meaudiodecoder.o meaudiodecoder.cpp

meauidoencoder.o: meauidoencoder.cpp meauidoencoder.h \
		OtherClass/ffmpeg.h \
		/usr/include/stdint.h \
		/usr/include/features.h \
		/usr/include/bits/predefs.h \
		/usr/include/sys/cdefs.h \
		/usr/include/bits/wordsize.h \
		/usr/include/gnu/stubs.h \
		/usr/include/gnu/stubs-32.h \
		/usr/include/bits/wchar.h \
		/usr/include/libavformat/avformat.h \
		/usr/include/time.h \
		/usr/include/bits/time.h \
		/usr/include/bits/types.h \
		/usr/include/bits/typesizes.h \
		/usr/include/xlocale.h \
		/usr/include/stdio.h \
		/usr/include/libio.h \
		/usr/include/_G_config.h \
		/usr/include/wchar.h \
		/usr/include/wctype.h \
		/usr/include/endian.h \
		/usr/include/bits/endian.h \
		/usr/include/bits/byteswap.h \
		/usr/include/bits/wchar2.h \
		/usr/include/bits/wchar-ldbl.h \
		/usr/include/gconv.h \
		/usr/include/bits/stdio-lock.h \
		/usr/include/bits/libc-lock.h \
		/usr/include/pthread.h \
		/usr/include/sched.h \
		/usr/include/bits/sched.h \
		/usr/include/bits/pthreadtypes.h \
		/usr/include/bits/setjmp.h \
		/usr/include/errno.h \
		/usr/include/bits/errno.h \
		/usr/include/linux/errno.h \
		/usr/include/asm/errno.h \
		/usr/include/asm-generic/errno.h \
		/usr/include/asm-generic/errno-base.h \
		/usr/include/gnu/option-groups.h \
		/usr/include/bits/libio-ldbl.h \
		/usr/include/bits/stdio_lim.h \
		/usr/include/bits/sys_errlist.h \
		/usr/include/getopt.h \
		/usr/include/ctype.h \
		/usr/include/bits/stdio.h \
		/usr/include/bits/stdio2.h \
		/usr/include/bits/stdio-ldbl.h \
		/usr/include/libavcodec/avcodec.h \
		/usr/include/libavutil/avutil.h \
		/usr/include/libavutil/common.h \
		/usr/include/inttypes.h \
		/usr/include/limits.h \
		/usr/include/bits/posix1_lim.h \
		/usr/include/bits/local_lim.h \
		/usr/include/linux/limits.h \
		/usr/include/bits/posix2_lim.h \
		/usr/include/bits/xopen_lim.h \
		/usr/include/math.h \
		/usr/include/bits/huge_val.h \
		/usr/include/bits/huge_valf.h \
		/usr/include/bits/huge_vall.h \
		/usr/include/bits/inf.h \
		/usr/include/bits/nan.h \
		/usr/include/bits/mathdef.h \
		/usr/include/bits/mathcalls.h \
		/usr/include/bits/mathinline.h \
		/usr/include/stdlib.h \
		/usr/include/bits/waitflags.h \
		/usr/include/bits/waitstatus.h \
		/usr/include/sys/types.h \
		/usr/include/sys/select.h \
		/usr/include/bits/select.h \
		/usr/include/bits/sigset.h \
		/usr/include/sys/sysmacros.h \
		/usr/include/alloca.h \
		/usr/include/bits/stdlib.h \
		/usr/include/bits/stdlib-ldbl.h \
		/usr/include/string.h \
		/usr/include/bits/string.h \
		/usr/include/bits/string2.h \
		/usr/include/bits/string3.h \
		/usr/include/libavutil/attributes.h \
		/usr/include/libavutil/mem.h \
		/usr/include/libavutil/error.h \
		/usr/include/libavutil/mathematics.h \
		/usr/include/libavutil/rational.h \
		/usr/include/libavutil/intfloat_readwrite.h \
		/usr/include/libavutil/log.h \
		/usr/include/libavutil/pixfmt.h \
		/usr/include/libavutil/avconfig.h \
		/usr/include/libavformat/avio.h \
		/usr/include/libavutil/fifo.h \
		/usr/include/libavutil/avstring.h \
		/usr/include/libavutil/adler32.h \
		/usr/include/libavutil/base64.h \
		/usr/include/libavutil/crc.h \
		/usr/include/libavdevice/avdevice.h \
		/usr/include/libavcodec/opt.h \
		/usr/include/libswscale/swscale.h \
		meaudiodecoder.h \
		/usr/include/assert.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o meauidoencoder.o meauidoencoder.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

