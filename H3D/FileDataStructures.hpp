#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <stdint.h>
namespace h3d {
/////////////////////////////////////////////////////////////////
//	FileDataStructures
/////////////////////////////////////////////////////////////////
	namespace FileType {
		/////////////////////////////////////////////////////////
		//	AUDIO FILE TYPES
		/////////////////////////////////////////////////////////
		// WAV File Format Structures ///////////////////////////
		namespace WAV {
			#pragma pack(push,WAV_HEADER,1)
			struct _declspec(dllexport) Header {
				char     chunkID[4];
				uint32_t ChunkSize;
				char     riffType[4];
			};
			#pragma pack(pop,WAV_HEADER)
			#pragma pack(push,WAV_FMT,1)
			struct _declspec(dllexport) FMT {
				char     wSignature[4];
				uint32_t wFmtLength;
				uint16_t wFormatTag;
				uint16_t wChannels;
				uint32_t dwSamplesPerSec;
				uint32_t dwAvgBytesPerSec;
				uint16_t wBlockAllign;
				uint16_t wBitsPerSample;
			};
			#pragma pack(pop,WAV_FMT)
		}
		// OFF File Format Structures ///////////////////////////
		namespace OGG {
			#pragma pack(push,OGG_HEADER,1)
			struct _declspec(dllexport) Header {

			};
			#pragma pack(pop,OGG_HEADER)
		}
		/////////////////////////////////////////////////////////
		//	IMAGE FILE TYPES
		/////////////////////////////////////////////////////////
		// BMP File Format Structures ///////////////////////////
		namespace BMP {
			#pragma pack(push,BMP_HEADER,1)
			struct _declspec(dllexport) Header {
				uint16_t bfType;
				uint32_t bfsize;
				uint32_t bfReserved;
				uint32_t bfOffBits;
			};
			#pragma pack(pop,BMP_HEADER)
			#pragma pack(push,BMP_BODY,1)
			struct _declspec(dllexport) Body {
				uint32_t biSize;
				int32_t  biWidth;
				int32_t  biHeight;
				uint16_t biPlanes;
				uint16_t biBitCount;
				uint32_t biCompression;
				uint32_t biSizeImage;
				int32_t  biXPelsPerMeter;
				int32_t  biYPelsPerMeter;
				int32_t  biClrUsed;
				uint32_t biClrImportant;
			};
			#pragma pack(pop,BMP_BODY)
		}
		// KTX File Format Structures ///////////////////////////
		namespace KTX {
			#pragma pack(push,KTX_HEADER,1)
			struct _declspec(dllexport) Header {
				char     identifier[12];
				uint32_t endianness;
				uint32_t glType;
				uint32_t glTypeSize;
				uint32_t glFormat;
				uint32_t glInternalFormat;
				uint32_t glBaseInternalFormat;
				uint32_t pixelWith;
				uint32_t pixelHeight;
				uint32_t pixelDepth;
				uint32_t numberofArrayElements;
				uint32_t numberOfFaces;
				uint32_t numberOfMipmapLevels;
				uint32_t bytesOfKeyValueData;
			};
			#pragma pack(pop,KTX_HEADER)
		}
		// TGA File Format Structures ///////////////////////////
		namespace TGA {
			#pragma pack(push,TGA_HEADER,1)
			struct _declspec(dllexport) Header {
				uint8_t  lengthPicID;
				int8_t   colorTableType;
				int8_t   picType;
				int16_t  tableBegin;
				int16_t  tableLength;
				int8_t   tableEntryBits;
				int16_t  XzeroPoint;
				int16_t  YzeroPoint;
				int16_t  picWidth;
				int16_t  picHeight;
				int8_t   bitCount;
				int8_t   picAtribByte;
			};
			#pragma pack(pop,TGA_HEADER)
			#pragma pack(push,TGA_HEADER_EXTENSION,1)
			struct __declspec(dllexport) HeaderExtension {

			};
			#pragma pack(pop,TGA_HEADER_EXTENSION)
		}
		/////////////////////////////////////////////////////////
	}
/////////////////////////////////////////////////////////////////
}