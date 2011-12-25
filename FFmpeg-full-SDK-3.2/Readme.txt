                                  ffmpeg FULL SDK V3.2
                                       （2008-04-12）



--------------------------------------------------------------------------------

    继ffmpeg工程组（http://www.ffmpeg.com.cn）2006年5月5日发布ffmpeg+x264 SDK V1.0版本，2006年9月25日发布V2.0版本之后，2007年8月21日发布V3.0版本，有很长的时间没有发布过新的SDK版本，ffmpeg的SVN版本号也由V3.0版本时的r10087更新到了目前的r12790，这期间ffmpeg的功能与稳定性都完善了很多，部分编码器的性能也有了较大幅度的提升，在很多热心的朋友强烈要求下，ffmpeg工程组再次发布FFMPEG FULL SDK V3.2，此次发布的SDK依旧为Full SDK，我们尽可能的集成更多的编解码器，需要注意的是，新版本的SDK中的ffmpeg.exe程序所支持的指令与V3.0所支持的指令有了较大的不同，具体可使用指令“ffmpeg.exe --help”获得更多的帮助。

    该SDK的编译配置如下：
./configure --prefix=d:/OmniCoder/svn_build --enable-memalign-hack --enable-shared --disable-static --disable-encod
er=snow --disable-decoder=ac3 --disable-decoder=vorbis --disable-encoder=vorbis --disable-vhook --enable-ffplay --disabl
e-ffserver --disable-mpegaudio-hp --enable-pthreads --enable-liba52 --enable-nonfree --enable-libamr-nb --enable-libamr-
wb --enable-libfaac --enable-libfaad --enable-libmp3lame --enable-libgsm --enable-libtheora --enable-libvorbis --enable-
libx264 --enable-libxvid --enable-avisynth --enable-gpl --enable-swscale --enable-avfilter --enable-avfilter-lavf --enab
le-demuxer=vfwcap --enable-demuxer=rm --extra-cflags=-I/usr/local/include -I/usr/local/include/SDL --extra-ldflags=-L/us
r/local/lib --extra-libs=-lpthreadGC2

  libavutil version: 49.6.0
  libavcodec version: 51.54.0
  libavformat version: 52.13.0
  libavdevice version: 52.0.0
  libavfilter version: 0.0.0
  built on Apr 12 2008 22:21:14, gcc: 4.3.0

Note:
output_example.exe, tools/cws2fws.exe, tools/pktdumper.exe, tools/qt-faststart.exe, tools/trasher.exe are also compiled

H264 decoding/encoding should be ehanced huge in this version if you have multi-core CPUs
x264 encoding will use multi-cores automically in this version

eg:
ffmpeg -i input.avi -threads 2 -vcodec libx264 -b 500K -bufsize 500K  -minrate 500K -maxrate 500K -rc_eq "blurCplx^(1-qComp)" -qmin 2 -qmax 51 output.mp4

Addins:
1) how to make a mp4 streamable with Adobe Flash Player?
You can use the following command to make a mp4/mov/3gp file<encoded with H264+AAC> streaming feature which is compatible with the latest Adobe Flash Player
eg:
 qt-faststart.exe input.mp4 output.mp4
 
Now,output.mp4 can be rendered instantly by Flash Player

2) VFW camera capture
The following command will use your default camera device to preview&grap picture,and encode the picture to mpeg4

ffmpeg -f vfwcap -s 320x240 -r 25 -i 0 -b 400K -vcodec mpeg4 new.mp4

    SDK的使用方法可参考ffmpeg项目中的output_example.c和libavcodec目录下的apiexample.c以及ffmpeg.c等例程源代码。

    我们将继续发布更强大、更稳定的ffmpeg SDK，请继续关注ffmpeg工程组（http://www.ffmpeg.com.cn）

文件：
    压缩包内包含三个目录：“include”、“lib”和“bin”三个目录，其中“include”目录包含了该SDK所需要用到的所有头文件，通常的情况下，只需要在你的工程中加入“#include "libavcodec/avcodec.h"”等头文件的包含即可；“lib”目录包含了连接工程时所需要的.lib库文件，“bin”目录包含了运行程序所需要的.dll动态库文件和其它可执行程序，在使用该SDK进行开发时，需要将.lib库文件加入工程中。
    压缩包内的“bin”目录中还包含了“ffmpeg.exe”可执行文件，“ffmpeg.exe”是ffmpeg工程中的一个项目，主要用于视频文件的转换、截图等操作，是一款非常强大的应用程序，在ffmpeg的工程中可以找到它的源代码。

版本：
    ffmpeg：V0.4.9 pre1 (SVN update:2008-04-12 SVN r12790)

源代码：
    该SDK并不提供ffmpeg的全部源代码，如果需要，可以通过如下地址提供的多种方式获取：
    http://www.ffmpeg.com.cn/index.php/%E8%8E%B7%E5%8F%96ffmpeg%E6%BA%90%E4%BB%A3%E7%A0%81


疑问：
    如果在使用过程中遇到疑难问题，可以通过如下方式得到相关的技术支持：
    ffmpeg工程组：http://www.ffmpeg.com.cn
    ffmpeg工程组（论坛）：http://bbs.chinavideo.org
    ffmpeg工程组QQ群：6939161，27548839
    GoogleGroups：http://groups.google.com/group/smartAV


感谢：
    该SDK最终由ffmpeg工程组成员Fastreaming编译，有任何问题大家可以通过下面的方式与之联系：
--
Skype: fastreaming
GTalk:  fastreaming
MSN:   dev@fastreaming.com
Mail:    codec@fastreaming.com
******We are here just for you******


                        中华视频网：  http://www.chinavideo.org
                        ffmpeg工程组：http://www.ffmpeg.com.cn
                        佰锐科技： http://www.bairuitech.com
                                  2008年4月12日