// ffmpeg_avformat.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
};
#define AC3_OR_EAC3_SYNCWORD_0B	0x0B
#define AC3_OR_EAC3_SYNCWORD_77	0x77
#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio
AVFormatContext *ifmt_ctx = NULL;
int g_AudioStreamIndex = -1;
int openinputfile(const char* filename);
int audio5_1(char* tmpUrl);
void ac3_parse_header(AVPacket &pkt);
bool parse_ac3_or_eac3_header(uint8_t* pBuffer, int bufferSize);
typedef enum {
	MV3_EAC3_FRAME_TYPE_INDEPENDENT = 0,
	MV3_EAC3_FRAME_TYPE_DEPENDENT,
	MV3_EAC3_FRAME_TYPE_AC3_CONVERT,
	MV3_EAC3_FRAME_TYPE_RESERVED
} MV3_EAC3FrameType;


int main()
{

	audio5_1(0);
	return 0;

}

int openinputfile(const char* filename)
{
	int ret = 0;
	//open the input  
	if ((ret = avformat_open_input(&ifmt_ctx, filename, NULL, NULL)) < 0)
	{
		printf("can not open input");
		return ret;
	}
	if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)))
	{
		printf("can not find input stream info");
		return ret;
	}


	AVCodecContext	*pCodecCtx = ifmt_ctx->streams[1]->codec;
	int channels = pCodecCtx->channels;

	av_dump_format(ifmt_ctx, 0, filename, false);
	//AV_CODEC_ID_AAC
	//open the decoder  
	for (int i = 0; i < ifmt_ctx->nb_streams; i++)
	{
		if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			g_AudioStreamIndex = i;
			ret = avcodec_open2(ifmt_ctx->streams[i]->codec,
				avcodec_find_decoder(ifmt_ctx->streams[i]->codec->codec_id), NULL);

			int channels = ifmt_ctx->streams[i]->codec->channels;

			if (ret < 0)
			{
				printf("can not open decoder");
				return ret;
			}

		}
		else if (ifmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			ret = avcodec_open2(ifmt_ctx->streams[i]->codec,
				avcodec_find_decoder(ifmt_ctx->streams[i]->codec->codec_id), NULL);
		}
	}

	return 0;
}

int audio5_1(char* tmpUrl)
{
	AVPacket pkt_in, pkt_out;
	AVFrame *frame = NULL;
	unsigned int stream_index;
	avcodec_register_all();
	char* url = "IMAX_Countdown_Sonic_Anthem_believe_1080p_DTS5.1.m1kv";		//ac3
																				//url = "G:\\1\\Jurassic.World.Fallen.Kingdom.2018.1080p.WEB-DL.DD5.1.H264-FGT.mkv";	//ac3
																				//url = "JL空间 4K片段5.1.mp4";		//aac
																				//url = "[杜比高清演示片] 全景声Dolby Atmos_5.1_7.1.m2ts";
																				//url = "00501.m2ts";
																				//url = "[杜比高清演示片] 全景声Dolby Atmos.track_4353.ac3";
																				//url = "IMAX_Countdown_SS_A_1080p.mp4";
	url = "[杜比高清演示片] 全景声Dolby Atmos.m2ts";
	//url = "[杜比高清演示片] 全景声Dolby Atmos.track_4352.ac3";
	//url = "DTS_X_7_1_4_Callout_(Lossless)_(UHD-DWEU).mkv";
	//url = "../audio/Atmos_71.m2ts";
	//url = "../flv/7_1声道，华为MediaPad_10_FHD杜比音效测试视频.mp4";




	//url = "../audio/1080i_10000_H264_CBR_AAC.ts";
	//url = "http://172.28.107.61/abnormal_video/ffmpeg/Brazil------2(3)-AAC.ts";
	url = "http://202.99.114.93:80/00000000/Umai:MOVI/19145362@BESTV.SMG.SMG/282497.8000.ts";
	url = "http://172.28.100.124:8080/sdh/mp4/direnjie.mp4";
	//url = "http://172.28.107.61/172_17_228_6_video/EAC3_6/4K-%e6%8c%87%e7%8e%af%e7%8e%8b3%e7%8e%8b%e8%80%85%e5%bd%92%e6%9d%a5-%e5%8e%9f%e5%a3%b0%e7%89%88.ts";
	//audio_deccodec_main(url);
	//return 0;
	//url = "http://172.28.104.75/video/testVideo/freetv_aac_latm_1aac.ts";
	//url = "http://172.28.100.124:8080/sdh/ts/yiren_h265_4k.ts";
	url = "http://172.28.107.61/172_17_228_6_video/EAC3_8/TFBOYS_4k_Atmos_H265_%e6%9d%9c%e6%af%94_%e9%80%82%e5%90%88%e5%81%9a%e8%b4%a8%e9%87%8f%e5%af%b9%e6%af%94%e6%b5%8b%e8%af%95.ts";
	url = "http://172.28.100.124:8080/sdh/ts/TFBOYS_4k_Atmos_H265_7.1_eac3.ts";

	url = "http://172.28.104.75/video/testVideo/mpegts+h264+ac3++skyoneHD_h264_sample2.ts";
	//url = "http://172.28.104.75/video/testVideo/freetv_aac_latm_1aac.ts";
	//url = "http://172.28.107.161/172_17_228_6_video/AC3_6/codes/H265/1209424607-level5-H265.ts";
	url = "http://172.28.100.124:8080/sdh/aac_ac3_eac3/Atmos_71.m2ts";
	if (openinputfile(url) < 0)
	{
		printf("failed to open input file");
		goto end;
	}


	//printf("enter any key to stop\n");
	//getchar();
	//return 0;
	AVCodecContext	*pCodecCtx = ifmt_ctx->streams[g_AudioStreamIndex]->codec;
	int channels = pCodecCtx->channels;

	char tmpName[100];
	sprintf_s(tmpName, "%s_%d_%dchannel.pcm", "test",
		pCodecCtx->sample_rate, pCodecCtx->channels);
	char* tmpFileName = "audio.pcm";
	//p = fopen("audio.dat", "w+b");

	int size = av_get_bytes_per_sample(pCodecCtx->sample_fmt);
	int i = 0;
	int count = 0;


	int out_channels = 6;
	struct SwrContext *au_convert_ctx = 0;
	au_convert_ctx = swr_alloc();

	int64_t in_channel_layout = av_get_default_channel_layout(out_channels);


	//Out Audio Param

	uint64_t out_channel_layout = av_get_default_channel_layout(out_channels);
	//nb_samples: AAC-1024 MP3-1152
	int out_nb_samples = 1536;
	//int out_nb_samples = 1024;
	AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;


	au_convert_ctx = swr_alloc_set_opts(au_convert_ctx,
		out_channel_layout, out_sample_fmt, pCodecCtx->sample_rate,
		in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate,
		0, NULL);
	swr_init(au_convert_ctx);


	//AV_CODEC_ID_TRUEHD
	uint8_t	*out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
	memset(out_buffer, 0, MAX_AUDIO_FRAME_SIZE * 2);
	int ret = -1;
	int got_frame = -1;

	static int count_1 = 0;
	while (1)
	{
		count_1++;
		if (count_1 == 2)
		{
			int a = 0;
		}
		if (av_read_frame(ifmt_ctx, &pkt_in) < 0)
		{
			break;
		}
		pkt_out.data = NULL;
		pkt_out.size = 0;
		av_init_packet(&pkt_out);

		if (g_AudioStreamIndex == pkt_in.stream_index)
		{

			stream_index = pkt_in.stream_index;
			frame = av_frame_alloc();


			//int index = 2;
			//while (index < pkt_in.size)
			//{

			//	if (pkt_in.data[index] == 0xB && pkt_in.data[index + 1] == 0x77)
			//	{
			//		break;
			//	}

			//	index++;
			//}

			//uint8_t a = pkt_in.data[0];
			//uint8_t b = pkt_in.data[1];
			//parse_ac3_or_eac3(pkt_in);
			//ac3_parse_header(pkt_in);

			//if (count_1 < 2)
			//{
			//	//pkt_in.size = 1690;
			//	count_1++;
			//	continue;

			//}
			//ac3_parse_header(pkt_in);
			//pkt_in.data += 924;
			//ac3_parse_header(pkt_in);

			//AC3_EAC3_info info;
			//parse_ac3_or_eac3_header(pkt_in.data, pkt_in.size);


			ret = avcodec_decode_audio4(ifmt_ctx->streams[stream_index]->codec, frame, &got_frame, &pkt_in);

			//ret = avcodec_decode_audio4(ifmt_ctx->streams[stream_index]->codec, frame, &got_frame, &pkt_in);
			//count_1++;
			int size1 = ifmt_ctx->streams[g_AudioStreamIndex]->codec->frame_size;
			////fwrite(pkt_in.data, 1, pkt_in.size, p);
			////break;
			//if (ret < 0)
			//{
			//	
			//	av_frame_free(&frame);
			//	printf("decoding audio stream failed\n");
			//	break;
			//}
			//if (count_1 == 4000)
			//{
			//	break;
			//}
			//count_1++;


			if (got_frame)
			{
				//fwrite(pkt_in.data, 1, pkt_in.size, p);
				int out_nb_sample = swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)frame->data, frame->nb_samples);
				int outbufferSize = 0;

				av_samples_get_buffer_size(&outbufferSize, out_channels, out_nb_sample, out_sample_fmt, 1);

				//fwrite(out_buffer, 1, outbufferSize, p);

				int i = 1;



				//ifmt_ctx->streams[stream_index]->codec->frame_size = frame->nb_samples;
				//for (int i = 0; i < ifmt_ctx->streams[stream_index]->codec->frame_size; i++)
				//{
				//	fwrite(frame->data[0] + i * size, 1, size, p);
				//	fwrite(frame->data[1] + i * size, 1, size, p);
				//	fwrite(frame->data[2] + i * size, 1, size, p);
				//	fwrite(frame->data[3] + i * size, 1, size, p);
				//	fwrite(frame->data[4] + i * size, 1, size, p);
				//	fwrite(frame->data[5] + i * size, 1, size, p);
				//	fwrite(frame->data[6] + i * size, 1, size, p);
				//	fwrite(frame->data[7] + i * size, 1, size, p);

				//}
			}
			else
			{
				int i = 1;
			}




			if (got_frame)
			{

				/*bool is_sample_fmt_16 = true;

				if (is_sample_fmt_16)
				{
				int out_nb_sample = swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)frame->data, frame->nb_samples);
				int outbufferSize = 0;
				int out_channels = pCodecCtx->channels;
				av_samples_get_buffer_size(&outbufferSize, out_channels, out_nb_sample, out_sample_fmt, 1);

				fwrite(out_buffer, 1, outbufferSize, p);

				}
				else
				{
				if (frame->data[0] && frame->data[1])
				{
				i++;
				ifmt_ctx->streams[stream_index]->codec->frame_size = frame->nb_samples;
				for (int i = 0; i < ifmt_ctx->streams[stream_index]->codec->frame_size; i++)
				{
				fwrite(frame->data[0] + i * size, 1, size, p);
				fwrite(frame->data[1] + i * size, 1, size, p);
				fwrite(frame->data[2] + i * size, 1, size, p);
				fwrite(frame->data[3] + i * size, 1, size, p);
				fwrite(frame->data[4] + i * size, 1, size, p);
				fwrite(frame->data[5] + i * size, 1, size, p);
				fwrite(frame->data[6] + i * size, 1, size, p);
				fwrite(frame->data[7] + i * size, 1, size, p);
				}
				}
				else if (frame->data[0])
				{
				fwrite(frame->data[0], 1, frame->linesize[0], p);
				}
				}*/

			}
		}
		else if (0 == pkt_in.stream_index)
		{

			//
			//if (pkt_in.flags == 1)
			//{
			//	int i = count_1;
			//}
			//count_1++;
			//ret = avcodec_decode_video2(ifmt_ctx->streams[pkt_in.stream_index]->codec, frame, &got_frame, &pkt_in);
			//int a0 = pkt_in.data[0];
			//int a1 = pkt_in.data[1];
			//int a2 = pkt_in.data[2];
			//int a3 = pkt_in.data[3];
			//int a4 = pkt_in.data[4];

			//if (count_1 == 2)
			//{
			//	FILE *p1 = NULL;
			//	p1 = fopen("videoFirstFrame.bat", "w+b");
			//	fwrite(pkt_in.data, 1, pkt_in.size, p1);
			//	fclose(p1);
			//}
			//count_1++;
			//if (got_frame)
			//{

			//	//printf("video  count = %d , pts =%d  \n",, frame->pts);
			//}

			//if (got_frame)
			//{
			//}
			//avcodec_decode_video2

		}

	}
	//fclose(p);
end:
	avformat_close_input(&ifmt_ctx);



	printf("enter any key to stop\n");
	//getchar();
	return 0;
}
const uint8_t ff_ac3_channels_tab[8] = {
	2, 1, 2, 3, 3, 4, 4, 5
};


const uint16_t avpriv_ac3_channel_layout_tab[8] = {
	AV_CH_LAYOUT_STEREO,
	AV_CH_LAYOUT_MONO,
	AV_CH_LAYOUT_STEREO,
	AV_CH_LAYOUT_SURROUND,
	AV_CH_LAYOUT_2_1,
	AV_CH_LAYOUT_4POINT0,
	AV_CH_LAYOUT_2_2,
	AV_CH_LAYOUT_5POINT0
};


const uint16_t ac3_sample_rate_tab[3] =
{
	48000,
	44100,
	32000
};

const uint8_t  ac3_channels_tab[8] = { 2,1,2,3,3,4,4,5 };

const uint16_t ac3_frame_size_tab[38][3] = {
	{ 64,   69,   96 },
	{ 64,   70,   96 },
	{ 80,   87,   120 },
	{ 80,   88,   120 },
	{ 96,   104,  144 },
	{ 96,   105,  144 },
	{ 112,  121,  168 },
	{ 112,  122,  168 },
	{ 128,  139,  192 },
	{ 128,  140,  192 },
	{ 160,  174,  240 },
	{ 160,  175,  240 },
	{ 192,  208,  288 },
	{ 192,  209,  288 },
	{ 224,  243,  336 },
	{ 224,  244,  336 },
	{ 256,  278,  384 },
	{ 256,  279,  384 },
	{ 320,  348,  480 },
	{ 320,  349,  480 },
	{ 384,  417,  576 },
	{ 384,  418,  576 },
	{ 448,  487,  672 },
	{ 448,  488,  672 },
	{ 512,  557,  768 },
	{ 512,  558,  768 },
	{ 640,  696,  960 },
	{ 640,  697,  960 },
	{ 768,  835,  1152 },
	{ 768,  836,  1152 },
	{ 896,  975,  1344 },
	{ 896,  976,  1344 },
	{ 1024, 1114, 1536 },
	{ 1024, 1115, 1536 },
	{ 1152, 1253, 1728 },
	{ 1152, 1254, 1728 },
	{ 1280, 1393, 1920 },
	{ 1280, 1394, 1920 },
};


bool parse_ac3_or_eac3_header(uint8_t* pBuffer, int bufferSize)
{

	if (!(pBuffer[0] == AC3_OR_EAC3_SYNCWORD_0B && pBuffer[1] == AC3_OR_EAC3_SYNCWORD_77))
	{
		return false;
	}


	int channels = 0;
	int sample_rate = 0;
	uint16_t frame_size = 0;
	uint8_t	frame_type = MV3_EAC3_FRAME_TYPE_INDEPENDENT;



	uint8_t bsi_bsid = pBuffer[5];
	bsi_bsid = bsi_bsid >> 3;

	if (bsi_bsid > 16)
	{
		return false;
	}


	if (bsi_bsid <= 10)
	{
		/* Normal AC-3 */

		uint8_t sr_code = pBuffer[4] & 0xC0;	 //2 bits
		sr_code >>= 6;
		if (sr_code == 3)
		{
			return false;
		}


		uint8_t frame_size_code = pBuffer[4] & 0x3F;	//6 bits
		if (frame_size_code > 37)
		{
			return false;
		}


		// MUInt8 a05_5bit = pbufferRef[5] & 0xF8;
		// a05_5bit = a05_5bit >> 3;

		// MUInt8 a05_3bit = pbufferRef[5] & 0xF8;


		uint8_t channel_mode = pBuffer[6] & 0xE0;
		channel_mode = channel_mode >> 5;

		uint8_t lfe_on = pBuffer[7] & 0x4;
		lfe_on = lfe_on >> 3;

		channels = lfe_on + ac3_channels_tab[channel_mode];

		uint8_t sr_shift = bsi_bsid > 8 ? bsi_bsid : 8;
		sr_shift -= 8;

		frame_size = ac3_frame_size_tab[frame_size_code][sr_code] * 2;

		frame_type = MV3_EAC3_FRAME_TYPE_AC3_CONVERT;
	}
	else
	{
		/* Enhanced AC-3 */
		//MInt32 TYPE_RESERVED = 3;


		uint8_t byte = pBuffer[2];
		frame_type = byte & 0xC0;
		frame_type >>= 6;
		if (frame_type == 3)
		{
			return false;
		}

		//frame_size field
		frame_size = byte & 0x7;
		frame_size <<= 8;
		byte = pBuffer[3];

		frame_size |= byte;

		frame_size = (frame_size + 1) << 1;

		if (frame_size < 7)
		{
			return false;
		}

		uint8_t src_code = pBuffer[4] & 0xC0;
		if (src_code == 3)
		{
			uint8_t src_code2 = (pBuffer[4] & 0x30) >> 2;
			if (src_code2 == 3)
			{
				return false;
			}

			sample_rate = ac3_sample_rate_tab[src_code2] / 2;

		}
		else
		{
			sample_rate = ac3_sample_rate_tab[src_code];
		}

		uint8_t channel_mode = pBuffer[4];

		channel_mode &= 0x0E;
		channel_mode >>= 1;

		uint8_t lfe_on = pBuffer[4] & 0x1;

		channels = ac3_channels_tab[channel_mode] + lfe_on;
	}


	return true;

}


typedef enum {
	MV_AC3_CHMODE_DUALMONO = 0,
	MV_AC3_CHMODE_MONO,
	MV_AC3_CHMODE_STEREO,
	MV_AC3_CHMODE_3F,
	MV_AC3_CHMODE_2F1R,
	MV_AC3_CHMODE_3F1R,
	MV_AC3_CHMODE_2F2R,
	MV_AC3_CHMODE_3F2R
} MV_AC3ChannelMode;

void ac3_parse_header(AVPacket &pkt)
{
	//pkt.data += 924;
	int channels = 0;

	int index = 0;
	int i = 0;
	for (i = 0; i < pkt.size; ++i)
	{
		if (pkt.data[i] == 0xB && pkt.data[i + 1] == 0x77)
		{

			break;
		}
	}


	uint8_t* pBuffer = pkt.data + i;

	uint8_t type_0B = pBuffer[0];
	uint8_t type_77 = pBuffer[1];
	int sample_rate = 0;
	if (type_0B != 0xB || type_77 != 0x77)
	{
		return;
	}

	uint8_t bsi_bsid = pBuffer[5];
	printf("enter any key to stop\n");
	bsi_bsid = bsi_bsid >> 3;
	if (bsi_bsid > 16)
	{
		return;
	}


	if (bsi_bsid <= 10)
	{
		/* Normal AC-3 */
		//bsi_bsid 0~8 标明是AC3


		uint8_t tmp = 0;

		uint8_t byte = pBuffer[4];
		uint8_t sr_code = pBuffer[4] & 0xC0;		//2 bits
		sr_code >>= 6;
		if (sr_code == 3)
		{
			return;
		}

		uint8_t frame_size_code = pBuffer[4] & 0x3F;	//6 bits
		if (frame_size_code > 37)
		{
			return;
		}

		uint8_t channel_mode = pBuffer[6] & 0xE0;
		channel_mode = channel_mode >> 5;

		int skipBits = 0;
		if (channel_mode == MV_AC3_CHMODE_STEREO) {
			skipBits = 2;
		}
		else {
			if ((channel_mode & 1) && channel_mode != MV_AC3_CHMODE_MONO)
			{
				skipBits = 2;
			}

			if (channel_mode & 4)
			{
				skipBits += 2;
			}

		}

		skipBits += 6 * 8 + 3;

		uint8_t lfe_on = pBuffer[skipBits >> 3];
		lfe_on <<= skipBits & 7;
		lfe_on >>= 8 - 1;


		uint8_t channels = lfe_on + ff_ac3_channels_tab[channel_mode];

		uint8_t sr_shift = bsi_bsid > 8 ? bsi_bsid : 8;
		sr_shift -= 8;

		sample_rate = ac3_sample_rate_tab[sr_code] >> sr_shift;

		int frame_size = ac3_frame_size_tab[frame_size_code][sr_code] * 2;
		int test = 0;
	}
	else
	{
		/* Enhanced AC-3 */
		//bsi_bsid 11-16 标明是EAC3
		int TYPE_RESERVED = 3;
		int AC3_HEADER_SIZE = 7;
		int8_t numblkscod = 0;


		uint8_t byte = pBuffer[2];
		uint8_t frame_type = byte & 0xC0;
		frame_type >>= 6;
		if (frame_type == TYPE_RESERVED)
		{
			return;
		}

		//frame_size field
		uint16_t frame_size = byte & 0x7;
		frame_size <<= 8;
		byte = pBuffer[3];

		frame_size |= byte;

		frame_size = (frame_size + 1) << 1;

		if (frame_size < AC3_HEADER_SIZE)
		{
			return;
		}

		uint8_t src_code = pBuffer[4] & 0xC0;
		if (src_code == 3)
		{
			uint8_t src_code2 = (pBuffer[4] & 0x30) >> 2;
			if (src_code2 == 3)
			{
				return;
			}

			int sample_rate = ac3_sample_rate_tab[src_code2] / 2;

		}
		else
		{
			sample_rate = ac3_sample_rate_tab[src_code];

			numblkscod = pBuffer[4] & 0x30;
			numblkscod >>= 4;


		}

		uint8_t channel_mode = pBuffer[4];

		channel_mode &= 0x0E;
		channel_mode >>= 1;

		uint8_t lfe_on = pBuffer[4] & 0x1;


		channels = ac3_channels_tab[channel_mode] + lfe_on;
	}

	int a = 1;
}



