	./configure \
	--disable-x86asm \
	--prefix=./win32 \
	--cpu=i686 \
	--toolchain=msvc \
	--extra-cflags="-Z7 -Wall" \
	--disable-programs \
	--disable-ffmpeg \
	--disable-ffplay \
	--disable-ffprobe \
	--disable-doc \
	--disable-htmlpages \
	--disable-manpages \
	--disable-podpages \
	--disable-txtpages \
	--disable-avdevice \
	--disable-postproc \
	--disable-avfilter \
\
	--disable-asm       \
	--disable-encoders	\
	--disable-decoders \
	--disable-bsfs \
	--disable-parsers \
	--enable-decoder=ac3 \
	--enable-decoder=eac3 \
	--enable-decoder=aac \
	--enable-decoder=h264 \
	--enable-parser=h264 \
	--enable-decoder=hevc \
	--enable-parser=hevc \
	--enable-debug \
	--enable-shared \

	# \
	# --enable-swscale \
	# --enable-avformat \
	# --enable-swresample \
	# --disable-everything \
	# --enable-decoder=h264 \
	# --enable-parser=h264 \
	# --enable-decoder=hevc \
	# --enable-parser=hevc \
	# --enable-decoder=ac3 \
	# --enable-decoder=eac3 \
	# --enable-decoder=aac \
	# --enable-demuxer=eac3 \
	# --enable-demuxer=flv \
	# --enable-demuxer=hls \
	# --enable-demuxer=mov \
	# --enable-protocol=librtmp \
	# --enable-protocol=rtmp \
	# --enable-protocol=tcp \
	# --enable-protocol=udp \
	# --enable-shared \
	# --disable-debug \

# -w 忽略警告

	# --disable-optimizations \
	# --extra-cflags=-O0 \
	# --disable-yasm \
	# \
	# --disable-swscale \
	# --disable-avformat \
	# --disable-swresample \
	# --disable-everything \
	# --enable-decoder=h264 \
	# --enable-parser=h264 \
	# --enable-decoder=hevc \
	# --enable-parser=hevc \
	# --enable-decoder=ac3 \
	# --enable-decoder=eac3 \
	# --enable-decoder=aac \
	# --enable-demuxer=eac3 \
	# --enable-demuxer=flv \
	# --enable-demuxer=hls \
	# --enable-demuxer=mov \
	# --enable-protocol=librtmp \
	# --enable-protocol=rtmp \
	# --enable-protocol=tcp \
	# --enable-protocol=udp \
	# --enable-shared \
	# --disable-debug \
	# --disable-w32threads \



#全部编译通过
	# ./configure \
	# --disable-x86asm \
	# --prefix=./win32 \
	# --cpu=i686 \
	# --toolchain=msvc \
	# --disable-programs \
	# --disable-ffmpeg \
	# --disable-ffplay \
	# --disable-ffprobe \
	# --disable-doc \
	# --disable-htmlpages \
	# --disable-manpages \
	# --disable-podpages \
	# --disable-txtpages \
	# --disable-avdevice \
	# --disable-postproc \
	# --disable-avfilter \


#全部可选编译avcode
# 	./configure \
# 	--disable-x86asm \
# 	--prefix=./win32 \
# 	--cpu=i686 \
# 	--toolchain=msvc \
# 	--extra-cflags="-Z7 -Wall" \
# 	--disable-programs \
# 	--disable-ffmpeg \
# 	--disable-ffplay \
# 	--disable-ffprobe \
# 	--disable-doc \
# 	--disable-htmlpages \
# 	--disable-manpages \
# 	--disable-podpages \
# 	--disable-txtpages \
# 	--disable-avdevice \
# 	--disable-postproc \
# 	--disable-avfilter \
# \
# 	--disable-encoders	\
# 	--disable-decoders \
# 	--disable-bsfs \
# 	--disable-parsers \
# 	--enable-decoder=ac3 \
# 	--enable-decoder=eac3 \
# 	--enable-decoder=aac \
# 	--enable-decoder=h264 \
# 	--enable-parser=h264 \
# 	--enable-decoder=hevc \
# 	--enable-parser=hevc \



#可选编译avformat
# 	./configure \
# 	--disable-x86asm \
# 	--prefix=./win32 \
# 	--cpu=i686 \
# 	--toolchain=msvc \
# 	--extra-cflags="-Z7 -Wall" \
# 	--disable-programs \
# 	--disable-ffmpeg \
# 	--disable-ffplay \
# 	--disable-ffprobe \
# 	--disable-doc \
# 	--disable-htmlpages \
# 	--disable-manpages \
# 	--disable-podpages \
# 	--disable-txtpages \
# 	--disable-avdevice \
# 	--disable-postproc \
# 	--disable-avfilter \
# \
# 	--disable-muxers \
# 	--disable-demuxers \
# 	--enable-demuxer=flv \
# 	--enable-demuxer=hls \
# 	--enable-demuxer=mov \
# 	--disable-protocols \
# 	--enable-protocol=tcp \



#可选编译avcode avformat
# 	./configure \
# 	--disable-x86asm \
# 	--prefix=./win32 \
# 	--cpu=i686 \
# 	--toolchain=msvc \
# 	--extra-cflags="-Z7 -Wall" \
# 	--disable-programs \
# 	--disable-ffmpeg \
# 	--disable-ffplay \
# 	--disable-ffprobe \
# 	--disable-doc \
# 	--disable-htmlpages \
# 	--disable-manpages \
# 	--disable-podpages \
# 	--disable-txtpages \
# 	--disable-avdevice \
# 	--disable-postproc \
# 	--disable-avfilter \
# \
# 	--disable-muxers \
# 	--disable-demuxers \
# 	--enable-demuxer=flv \
# 	--enable-demuxer=hls \
# 	--enable-demuxer=mov \
# 	--disable-protocols \
# 	--enable-protocol=tcp \
# 	--enable-protocol=udp \
# \
# 	--disable-encoders	\
# 	--disable-decoders \
# 	--disable-bsfs \
# 	--disable-parsers \
# 	--enable-decoder=ac3 \
# 	--enable-decoder=eac3 \
# 	--enable-decoder=aac \
# 	--enable-decoder=h264 \
# 	--enable-parser=h264 \
# 	--enable-decoder=hevc \
# 	--enable-parser=hevc \
