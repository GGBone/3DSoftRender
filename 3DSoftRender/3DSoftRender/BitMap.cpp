#include "Bitmap.h"
#include <iostream>
using namespace std;
using namespace BITMAP_M;
BitMap::tagBITMAP_FILE BitMap::bitmapfile;
BitMap::BitMap(char* filename)
{
	Init(filename);
}
bool BitMap::Init(char* filename)
{
	if (filename == NULL)
		return false;
	fopen_s(&pFile,filename, "r");
	fseek(pFile, 0x0000, SEEK_SET);
	fread(&bitmapfile.bitmapheader.bfType, sizeof(WORD), 1, pFile);

	fseek(pFile, 0x0002, SEEK_SET);
	fread(&bitmapfile.bitmapheader.bfSize, sizeof(DWORD), 1, pFile);

	fseek(pFile, 0x0006, SEEK_SET);
	fread(&bitmapfile.bitmapheader.bfReserved1, sizeof(WORD), 1, pFile);

	fseek(pFile, 0x0008, SEEK_SET);
	fread(&bitmapfile.bitmapheader.bfReserved2, sizeof(WORD), 1, pFile);
	
	fseek(pFile, 0x000A, SEEK_SET);
	fread(&bitmapfile.bitmapheader.bfOffBits, sizeof(DWORD), 1, pFile);

	fseek(pFile, 0x000E, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biSize, sizeof(DWORD), 1, pFile);


	fseek(pFile, 0x0012, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biWidth, sizeof(LONG), 1, pFile);

	fseek(pFile, 0x0016, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biHeight, sizeof(LONG), 1, pFile);

	fseek(pFile, 0x001A, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biPlanes, sizeof(WORD), 1, pFile);

	fseek(pFile, 0X001C, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biBitCount, sizeof(WORD), 1, pFile);

	fseek(pFile, 0x001E, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biCompression, sizeof(DWORD), 1, pFile);

	fseek(pFile, 0x0022, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biSizeImage, sizeof(DWORD), 1, pFile);

	fseek(pFile, 0x0026, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biXPelsPerMeter, sizeof(LONG), 1, pFile);

	fseek(pFile, 0x002A, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biYPelsPerMeter, sizeof(LONG), 1, pFile);

	fseek(pFile, 0x002E, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biClrUsed, sizeof(DWORD), 1, pFile);

	fseek(pFile, 0x0032, SEEK_SET);
	fread(&bitmapfile.bitmapinfoheader.biClrImportant, sizeof(DWORD), 1, pFile);

	//if(bitcount < 24)
	//处理调色板
	//TODO
	//else
	//处理颜色
	fseek(pFile, 0x0036, SEEK_SET);
	

	width = bitmapfile.bitmapinfoheader.biWidth;
	height = bitmapfile.bitmapinfoheader.biHeight;
	bit = bitmapfile.bitmapinfoheader.biBitCount;
	int LineLength = width * 3;
	while (LineLength % 4 !=0)
		++LineLength;
	width = LineLength;
	int byteSize = LineLength * height;
	bitmapfile.buffer = new GLubyte[byteSize];
	fread(bitmapfile.buffer, byteSize * sizeof(UCHAR), 1, pFile);
	
	try
	{
		fclose(pFile);
	}
	catch (exception e)
	{

	}
	return true;
}

BitMap::~BitMap()
{

}