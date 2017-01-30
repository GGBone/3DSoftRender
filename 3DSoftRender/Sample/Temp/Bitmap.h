#ifndef BITMAP_H
#define BITMAP_H
#include <gl\freeglut.h>
#include <iostream>
using namespace std;
namespace BITMAP_M
{
	class BitMap
	{
	private:
		
		FILE * pFile;
		void* d_data;

		unsigned short int bit;
		typedef struct tagBITMAP_FILE
		{
			BITMAPFILEHEADER bitmapheader;
			BITMAPINFOHEADER bitmapinfoheader;
			PALETTEENTRY palette[256];
			UCHAR* buffer;
			
		}BITMAP_FILE;
		
		bool Init(char* filename);
	public:
		BitMap(char* filename);
		void GetData(BITMAP_FILE* d_bitmap);
		~BitMap();
		static BITMAP_FILE bitmapfile;
		GLint width, height;

	};

}
#endif