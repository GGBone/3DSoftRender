#include "GraphicsPCH.h"
#include "Renderer.h"

using namespace Hikari;


////派生
//
//bool DXBase::LoadContent()
//{
//	return true;
//}
//void DXBase::UnloadContent()
//{
//}
//void DXBase::ShutDown()
//{
//	UnloadContent();
//	if (backBufferTarget) backBufferTarget->Release();
//	if (swapChain) swapChain->Release();
//	if (d3dContext)d3dContext->Release();
//	if (d3dDevice)d3dDevice->Release();
//
//	backBufferTarget = 0;
//	swapChain = 0;
//	d3dContext = 0;
//	d3dDevice = 0;
//}
//float color[4] = { 0, 0, 0, 1 };
//void DXRender::Render(RenderList& renderlist)
//{
//	pSRView->GetResource((ID3D11Resource**)&renderTexture);
//	d3dContext->Map(renderTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mp);
//	drawBuffer = mp.pData;
//	memset(drawBuffer, 0, WIDTH*HEIGHT*4);
//	d3dContext->Unmap(renderTexture, 0);
//
//	d3dContext->Map(renderTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mp);
//	drawBuffer = mp.pData;
//	PolyF4DV1* curr_poly;
//	for (int i = 0; i < renderlist.num_polys; i++)
//	{
//		curr_poly = renderlist.poly_ptrs[i];
//		if (curr_poly == nullptr)
//			continue;
//
//		lineBresenham(drawBuffer, curr_poly->tvlist[0][0], curr_poly->tvlist[0][1], curr_poly->tvlist[1][0], curr_poly->tvlist[1][1], curr_poly->color);
//		lineBresenham(drawBuffer, curr_poly->tvlist[1][0], curr_poly->tvlist[1][1], curr_poly->tvlist[2][0], curr_poly->tvlist[2][1], curr_poly->color);
//		lineBresenham(drawBuffer, curr_poly->tvlist[2][0], curr_poly->tvlist[2][1], curr_poly->tvlist[0][0], curr_poly->tvlist[0][1], curr_poly->color);
//
//	}
//	d3dContext->Unmap(renderTexture, 0);
//	
//	d3dContext->PSSetShaderResources(0, 1, &pSRView);
//	d3dContext->Draw(6, 0);
//	swapChain->Present(0, 0);
//	
//}
//void DXRender::Render(Object4DV1& object)
//{
//	ClearBuffer(color);
//	pSRView->GetResource((ID3D11Resource**)&renderTexture);
//	d3dContext->Map(renderTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mp);
//	drawBuffer = mp.pData;
//	memset(drawBuffer, 0, WIDTH*HEIGHT * 4);
//	d3dContext->Unmap(renderTexture, 0);
//
//	d3dContext->Map(renderTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mp);
//	drawBuffer = mp.pData;
//	for (int i = 0; i < object.num_polys; i++)
//	{ 
//		if (!(object.plist[i].state & POLY4DV1_STATE_ACTIVE) ||
//			(object.plist[i].state & POLY4DV1_STATE_CLIPPED) ||
//			(object.plist[i].state & POLY4DV1_STATE_BACKFACE))
//			continue; // move onto next poly
//		int vertex0 = object.plist[i].vert[0];
//		int vertex1 = object.plist[i].vert[1];
//		int vertex2 = object.plist[i].vert[2];
//
//		DrawClipLine(object.vlist_trans[vertex0][0], object.vlist_trans[vertex0][1], object.vlist_trans[vertex1][0], object.vlist_trans[vertex1][1], 255, drawBuffer);
//		DrawClipLine(object.vlist_trans[vertex1][0], object.vlist_trans[vertex1][1], object.vlist_trans[vertex2][0], object.vlist_trans[vertex2][1], 255, drawBuffer);
//		DrawClipLine(object.vlist_trans[vertex2][0], object.vlist_trans[vertex2][1], object.vlist_trans[vertex0][0], object.vlist_trans[vertex0][1], 255, drawBuffer);
//
//	}
//	d3dContext->Unmap(renderTexture, 0);
//
//	d3dContext->PSSetShaderResources(0, 1, &pSRView);
//	d3dContext->Draw(6, 0);
//	swapChain->Present(0, 0);
//
//}
//void DXRender::ClearBuffer(float color[4])
//{
//	if (d3dContext == 0)
//		return;
//	d3dContext->ClearRenderTargetView(backBufferTarget, color);
//}
//

//DXRender::DXRender() :solidColorVS(0), solidColorPS(0), inputLayout(0), vertexBuffer(0)
//{
//
//}
//DXRender::~DXRender()
//{
//
//}
//void DXRender::Update(float dt)
//{
//
//}
//
//void DXRender::UnloadContent()
//{
//	if (solidColorVS) solidColorVS->Release();
//	if (solidColorPS) solidColorPS->Release();
//	if (inputLayout) inputLayout->Release();
//	if (vertexBuffer) vertexBuffer->Release();
//	solidColorPS = 0;
//	solidColorVS = 0;
//	inputLayout = 0;
//	vertexBuffer = 0;
//}
//#endif
//
//
//
//Vector4D Vector4D::UP = Vector4D(0.0f, 1.0f, 0.0f, 0.0f);
//Vector4D Vector4D::RIGHT = Vector4D(1.0f, 0.0f, 0.0f, 0.0f);
//Vector4D Vector4D::FORWARD = Vector4D(0.0f, 0.0f, 1.0f, 0.0f);
//
//Vector3D Vector3D::UP = Vector3D(0.0f, 1.0f, 0.0f);
//Vector3D Vector3D::RIGHT = Vector3D(1.0f, 0.0f, 0.0f);
//Vector3D Vector3D::FORWARD = Vector3D(0.0f, 0.0f, 1.0f);
////Graphics function
//extern Matrix4X4 OBJECT;
//extern Matrix4X4 PROJECTION;
//
//
//
//void pix(void* render, int x, int y, int color)
//{
//	//hdc = GetDC(hWnd);
//
//	//NewBrush = CreateSolidBrush(Color);
//	*((int*)render + WIDTH*(HEIGHT-y) + x) = color;
//
//	//SetPixel(hdc, x, y, Color);
//	//ReleaseDC(hWnd, hdc);
//}
//
//inline void swap_int(int *a, int*b)
//{
//	*a ^= *b;
//	*b ^= *a;
//	*a ^= *b;
//}
//
//int DrawLine(int x0, int y0, int x1, int y1,int color, void* vb_start)
//{
//	lineBresenham((void*)vb_start, x0, y0, x1, y1, color);
//	return 1;
//}
//int DrawClipLine(int x0, int y0, int x1, int y1, int color, void* dest_buffer)
//{
//	int cxs, cys, cxe, cye;
//	cxs = x0;
//	cys = y0;
//	cxe = x1;
//	cye = y1;
//	if (ClipLine(cxs, cys, cxe, cye))
//		//DrawLine
//		DrawLine(cxs, cys, cxe, cye, color, dest_buffer);
//	return 1;
//}
//int ClipLine(int& x1, int& y1, int& x2, int& y2)
//{
//#define CLIP_FLAGS
//#define CLIP_CODE_C	0x00000000
//#define CLIP_CODE_N 0x00000001
//#define CLIP_CODE_S 0x00000002
//#define CLIP_CODE_W 0x00000004
//#define CLIP_CODE_E 0x00000008
//
//#define CLIP_CODE_NE 0x0000009
//#define CLIP_CODE_SE 0x000000a
//#define CLIP_CODE_NW 0x0000005
//#define CLIP_CODE_SW 0x0000006
//	
//	int xc1 = x1;
//	int xc2 = x2;
//	int yc1 = y1;
//	int yc2 = y2;
//
//	int p1_flags = 0;
//	int p2_flags = 0;
//	
//	int min_clip_x = 0;
//	int max_clip_x = WIDTH - 1;
//	int min_clip_y = 0;
//	int max_clip_y = HEIGHT - 1;
//
//	if (y1 < min_clip_y)
//		p1_flags |= CLIP_CODE_S;
//	else if (y1 > max_clip_y)
//		p1_flags |= CLIP_CODE_N;
//
//	if (x1 < min_clip_x)
//		p1_flags |= CLIP_CODE_W;
//	else if (x1 > max_clip_x)
//		p1_flags |= CLIP_CODE_E;
//
//
//	if (y2 < min_clip_y)
//		p2_flags |= CLIP_CODE_S;
//	else if (y2 > max_clip_y)
//		p2_flags |= CLIP_CODE_N;
//
//	if (x2 < min_clip_x)
//		p2_flags |= CLIP_CODE_W;
//	else if (x2 > max_clip_x)
//		p2_flags |= CLIP_CODE_E;
//
//	//total outside and one direction
//	if (p1_flags & p2_flags)
//		return 0;
//
//	//total inside
//	if (p1_flags == 0 && p2_flags == 0)
//		return 1;
//
//	//one inside the other outside
//	switch (p1_flags)
//	{
//	case CLIP_CODE_C: break;
//	
//	case CLIP_CODE_N:
//	{
//		yc1 = min_clip_y;
//		// be sure the result the follow float number is cut off is valid
//		xc1 = ((min_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//	
//	}break;
//	case CLIP_CODE_S:
//	{
//		yc1 = max_clip_y;
//		// be sure the result the follow float number is cut off is valid
//		xc1 = ((max_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//	}break;
//
//	case CLIP_CODE_W:
//	{
//		xc1 = min_clip_x;
//		yc1 = ((min_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//	}break;
//	case CLIP_CODE_E:
//	{
//		xc1 = max_clip_x;
//		yc1 = ((max_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//	}break;
//
//	case CLIP_CODE_NE:
//	{
//		//the line intersects with ( y = ymin) 
//		yc1 = min_clip_y;
//		xc1 = ((min_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc1<min_clip_x || xc1 > max_clip_x)
//		{
//			xc1 = max_clip_x;
//			yc1 = ((max_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//	case CLIP_CODE_SE:
//	{
//		//the line intersects with ( y = ymax) 
//		yc1 = max_clip_y;
//		xc1 = ((max_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc1<min_clip_x || xc1 > max_clip_x)
//		{
//			xc1 = max_clip_x;
//			yc1 = ((max_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//
//	case CLIP_CODE_NW:
//	{
//		//the line intersects with ( y = ymin) 
//		yc1 = min_clip_y;
//		xc1 = ((min_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc1<min_clip_x || xc1 > max_clip_x)
//		{
//			xc1 = min_clip_x;
//			yc1 = ((min_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//	case CLIP_CODE_SW:
//	{
//		//the line intersects with ( y = ymax) 
//		yc1 = max_clip_y;
//		xc1 = ((max_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc1<min_clip_x || xc1 > max_clip_x)
//		{
//			xc1 = min_clip_x;
//			yc1 = ((min_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//	default:
//		break;
//	}
//
//	switch (p2_flags)
//	{
//	case CLIP_CODE_C: break;
//
//	case CLIP_CODE_N:
//	{
//		yc2 = min_clip_y;
//		// be sure the result the follow float number is cut off is valid
//		xc2 = ((min_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//	}break;
//	case CLIP_CODE_S:
//	{
//		yc2 = max_clip_y;
//		// be sure the result the follow float number is cut off is valid
//		xc2 = ((max_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//	}break;
//
//	case CLIP_CODE_W:
//	{
//		xc2 = min_clip_x;
//		yc2 = ((min_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//	}break;
//	case CLIP_CODE_E:
//	{
//		xc2 = max_clip_x;
//		yc2 = ((max_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//	}break;
//
//	case CLIP_CODE_NE:
//	{
//		//the line intersects with ( y = ymin) 
//		yc2 = min_clip_y;
//		xc2 = ((min_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc2<min_clip_x || xc2 > max_clip_x)
//		{
//			xc2 = max_clip_x;
//			yc2 = ((max_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//	case CLIP_CODE_SE:
//	{
//		//the line intersects with ( y = ymax) 
//		yc2 = max_clip_y;
//		xc2 = ((max_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc2<min_clip_x || xc2 > max_clip_x)
//		{
//			xc2 = max_clip_x;
//			yc2 = ((max_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//
//	case CLIP_CODE_NW:
//	{
//		//the line intersects with ( y = ymin) 
//		yc2 = min_clip_y;
//		xc2 = ((min_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc2<min_clip_x || xc2 > max_clip_x)
//		{
//			xc2 = min_clip_x;
//			yc2 = ((min_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//	case CLIP_CODE_SW:
//	{
//		//the line intersects with ( y = ymax) 
//		yc2 = max_clip_y;
//		xc2 = ((max_clip_y - y1)*(x2 - x1) / (y2 - y1)) + x1 + 0.5;
//
//		//the line intersects with ( x = xmax) 
//		if (xc2<min_clip_x || xc2 > max_clip_x)
//		{
//			xc2 = min_clip_x;
//			yc2 = ((min_clip_x - x1) * (y2 - y1) / (x2 - x1)) + y1 + 0.5;
//		}
//	}break;
//	default:
//		break;
//	}
//
//
//	//bound check
//	if ((xc1 < min_clip_x) || (xc1 > max_clip_x) ||
//		(yc1 < min_clip_y) || (yc1 > max_clip_y) ||
//		(xc2 < min_clip_x) || (xc2 > max_clip_x) ||
//		(yc2 < min_clip_y) || (yc2 > max_clip_y))
//	{
//		return 0;
//	}
//#undef CLIP_FLAGS
//	x1 = xc1;
//	y1 = yc1;
//	x2 = xc2;
//	y2 = yc2;
//	return 1;
//}
//void lineBresenham(void* p, int x0, int y0, int x1, int y1,int Color)
//{
//	int dx = abs(x1 - x0);
//	int dy = abs(y1 - y0);
//	int direction = 0;
//	if (dx < dy)
//	{
//		direction = 1;	//大于45°
//		swap_int(&x1, &y1);
//		swap_int(&x0, &y0);
//		swap_int(&dx, &dy);
//	}
//	int ix = (x1 - x0) > 0 ? 1 : -1;
//	int iy = (y1 - y0) > 0 ? 1 : -1;
//	int p0 = 2 * dy - dx;
//
//	int n2dy = 2 * dy;
//	int n2dydx = (dy - dx) * 2;
//	int x = x0;
//	int y = y0;
//	if (direction)
//	{
//		while (x != x1)
//		{
//			if (p0 < 0)
//			{
//				p0 += n2dy;
//			}
//			else
//			{
//				y += iy;
//				p0 += n2dydx;
//			}
//			pix(p, y, x, Color);
//			x += ix;
//		}
//	}
//	else
//	{
//		pix(p, x, y, Color);
//		while (x != x1)
//		{
//			if (p0 > 0)
//			{
//
//				y += iy;
//				p0 += n2dydx;
//			}
//			else
//			{
//				p0 += n2dy;
//			}
//			pix(p, x, y,Color);
//			x += ix;
//		}
//	}
//
//}
//void DrawCube(HWND& hwnd, HDC& hdc, HBRUSH& hbrush, PAINTSTRUCT& ps, Point3D* vertex, int size)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		if (i == 3)
//		{
//			lineBresenham(hwnd, hdc, hbrush, ps, vertex[i][0], vertex[i][1], vertex[0][0], vertex[0][1]);
//		}
//		else lineBresenham(hwnd, hdc, hbrush, ps, vertex[i][0], vertex[i][1], vertex[i + 1][0], vertex[i + 1][1]);
//	}
//	for (int i = 4; i < 8; i++)
//	{
//		if (i == 7)
//		{
//			lineBresenham(hwnd, hdc, hbrush, ps, vertex[i][0], vertex[i][1], vertex[4][0], vertex[4][1]);
//		}
//		else
//			lineBresenham(hwnd, hdc, hbrush, ps, vertex[i][0], vertex[i][1], vertex[i + 1][0], vertex[i + 1][1]);
//	}
//	for (int i = 0, j = 4; i < 4; i++, j++)
//	{
//		lineBresenham(hwnd, hdc, hbrush, ps, vertex[i][0], vertex[i][1], vertex[j][0], vertex[j][1]);
//	}
//}
//void DrawCircle(HWND& hwnd, HDC& hdc, HBRUSH& hbrush, PAINTSTRUCT& ps, int x0, int y0, int radius)
//{
//	int x = 0;
//	int y = radius;
//	int p0 = 3 - 2 * radius;
//	while (x<y)
//	{
//		SetPixel(hdc, x0 + x, y0 - y, RGB(255, 0, 0));
//		SetPixel(hdc, x0 + y, y0 - x, RGB(255, 0, 0));
//		SetPixel(hdc, x0 - y, y0 + x, RGB(255, 0, 0));
//		SetPixel(hdc, x0 - x, y0 + y, RGB(255, 0, 0));
//
//		SetPixel(hdc, x0 - x, y0 - y, RGB(255, 0, 0));
//		SetPixel(hdc, x0 - y, y0 - x, RGB(255, 0, 0));
//		SetPixel(hdc, x0 + y, y0 + x, RGB(255, 0, 0));
//		SetPixel(hdc, x0 + x, y0 + y, RGB(255, 0, 0));
//		if (p0 < 0)
//		{
//			p0 += 4 * x + 6;
//		}
//		else
//		{
//			y -= 1;
//			p0 += 4 * (x - y) + 10;
//		}
//		x += 1;
//	}
//
//}
//void linerect(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps, int x, int y, int width, int height, COLORREF colorR, COLORREF colorG, COLORREF colorB)
//{
//	hdc = GetDC(hWnd);
//	COLORREF color = RGB(colorR, colorG, colorB);
//	NewBrush = CreateSolidBrush(color);
//	int _width = width + x;
//	int _height = height + y;
//	for (int i = x; i < _width; i++)
//	{
//		for (int j = y; j < _height; j++)
//			SetPixel(hdc, i, j, color);
//	}
//	ReleaseDC(hWnd, hdc);
//}
////Rotate和Translate是对于Object矩阵的变化
//void RotateByAix(int x, int y, int z, float angle)
//{
//	//绕任意轴旋转的时候，先将该轴转到与坐标轴重合，然后旋转，然后乘以逆矩阵再返回去
//	float M[3][3];
//	M[0][0] = x * x * (1 - cos(angle)) + cos(angle);
//	M[0][1] = x * y * (1 - cos(angle)) - z*sin(angle);
//	M[0][2] = x * z * (1 - cos(angle)) + y * sin(angle);
//
//	M[1][0] = y*x*(1 - cos(angle)) + z*sin(angle);
//	M[1][1] = y*y*(1 - cos(angle)) + cos(angle);
//	M[1][2] = y*z*(1 - cos(angle)) - x*sin(angle);
//
//	M[2][0] = x*z*(1 - cos(angle)) - y*sin(angle);
//	M[2][1] = y*z*(1 - cos(angle)) + x*sin(angle);
//	M[2][2] = z*z*(1 - cos(angle)) + cos(angle);
//
//	Matrix4X4 temp;
//	temp = Matrix3X3(&M[0][0]);
//	OBJECT = temp * OBJECT;
//}
//
//void Translate(Vector3D direction, float distance)
//{
//
//	float Object[][4] =
//	{
//		1.0f, 0.0f, 0.0f, direction.Normal()[0] * distance,
//		0.0f, 1.0f, 0.0f, direction.Normal()[1] * distance,
//		0.0f, 0.0f, 1.0f, direction.Normal()[2] * distance,
//		0.0f, 0.0f, 0.0f, 1.0f,
//	};
//	Matrix4X4 temp;
//	temp = Matrix4X4(&Object[0][0]);
//	OBJECT = temp * OBJECT;
//}
//
//void TransformRendList(RenderList& rendlist, Matrix4X4& mt, int coord_select)
//{
//	switch (coord_select)
//	{
//	case TRANSFORM_LOCAL_ONLY:
//
//		PolyF4DV1* curr_poly;
//		for (int i = 0; i < rendlist.num_polys; i++)
//		{
//			curr_poly = rendlist.poly_ptrs[i];
//			if ((curr_poly == NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
//				(curr_poly->state & POLY4DV1_STATE_BACKFACE))
//				continue;
//			for (int i = 0; i < 3; i++)
//			{
//				Point4D presult;
//				presult = mt * curr_poly->vlist[i];
//				curr_poly->vlist[i] = presult;
//			}
//		}
//
//		break;
//	case TRANSFORM_TRANS_ONLY:
//
//
//		break;
//	case TRANSFORM_LOCAL_TO_TRANS:
//
//
//		break;
//	default:
//		break;
//	}
//}
//void Model_To_WorldRendlist(RenderList& rendlist, Point3D& poly_Pos, int coord_select)
//{
//	PolyF4DV1* curr_poly;
//	for (int index = 0; index < rendlist.num_polys; index++)
//	{
//		curr_poly = rendlist.poly_ptrs[index];
//		if (curr_poly == NULL)
//			continue;
//		for (int i = 0; i < 3; i++)
//		{
//			curr_poly[index].tvlist[i] = curr_poly[index].vlist[i];
//			curr_poly[index].tvlist[i] = OBJECT * curr_poly[index].tvlist[i];
//		}		
//	}
//}
//void Model_To_WorldObject(Object4DV1& object)
//{
//	for (int i = 0; i < object.num_vertices; i++)
//	{
//		object.vlist_trans[i] = object.vlist_local[i];
//		object.vlist_trans[i] = OBJECT * object.vlist_trans[i];
//	}
//}
//void ObjectToWorld(Object* obj, int coor_select)
//{
//	const type_info& typeinfo = typeid(obj);
//	Object4DV1* newptr = static_cast<Object4DV1*>(obj);
//	
//	
//	if (newptr == nullptr)
//		return;
//	if (coor_select == TRANSFORM_LOCAL_TO_TRANS)
//	{
//		for (int vertex = 0; vertex < newptr->num_vertices; vertex++)
//		{
//			newptr->vlist_trans[vertex] = newptr->world_pos + newptr->vlist_local[vertex];
//		}
//	}
//	else
//	{
//		for (int vertex = 0; newptr->num_vertices;vertex++)
//		{
//			newptr->vlist_trans[vertex] = newptr->world_pos + newptr->vlist_trans[vertex];
//		}
//	}
//}
//
//void WorldToView(Point3D* point, int size)
//{
//	//平移观察坐标原点到世界坐标原点
//	//进行旋转，分别让xview ,yview,zview对应为世界坐标的x,y,z
//	//p0为观察原点 
//	/*
//	//u,v,n是uvn轴的分量
//	M(WC,VC) = R * T
//	*/
//
//
//}
//
//
//void NDC2DC(RenderList& rendlist, int width, int height, float pr, float pe, float pb, float pt, float pf, float pn)
//{
//	float dc[][4] =
//	{
//		width*(pr - pe) / 2.0f, 0.0f, 0.0f, width*(pr + pe) / 2.0f,
//		0.0f, height*(pb - pt) / 2.0f, 0, height*(2.0f - pt - pb) / 2.0f,
//		0, 0, pf - pn, pn,
//		0, 0, 0, 1
//	};
//	Matrix4X4 d(&dc[0][0]);
//	PolyF4DV1* curr_poly;
//	for (int i = 0; i < rendlist.num_polys; i++)
//	{
//		curr_poly = rendlist.poly_ptrs[i];
//		if (curr_poly == nullptr)
//			continue;
//		for (int index = 0; index < 3; index++)
//		{
//			curr_poly->tvlist[index] = d* Point3D(curr_poly->tvlist[index][0],curr_poly->tvlist[index][1],1.0f);
//		}
//	}
//}
//
//
//
//void NDC2DC(Object* object, int width, int height, float pr, float pe, float pb, float pt, float pf, float pn)
//{
//	float dc[][4] =
//	{
//		width*(pr - pe) / 2.0f, 0.0f, 0.0f, width*(pr + pe) / 2.0f,
//		0.0f, height*(pb - pt) / 2.0f, 0, height*(2.0f - pt - pb) / 2.0f,
//		0, 0, pf - pn, pn,
//		0, 0, 0, 1
//	};
//	Matrix4X4 d(&dc[0][0]);
//	Object4DV1* curr_poly = static_cast<Object4DV1*>(object);
//
//		for (int j = 0; j < curr_poly->num_vertices; j++)
//		{
//			curr_poly->vlist_trans[j] = d * Point3D(curr_poly->vlist_trans[j][0], curr_poly->vlist_trans[j][1], 1.0f);
//		}
//	
//}
////这里指定的裁剪窗口转换后的坐标是世界坐标系下-1~1
//void Ortho(Vector3D& p, float znear, float zfar, float xmax, float xmin, float ymax, float ymin)
//{
//	float PROJECTION_M[4][4];
//	PROJECTION_M[0][0] = 2.0f / (xmax - xmin);
//	PROJECTION_M[1][1] = 2.0f / (ymax - ymin);
//	PROJECTION_M[2][2] = -2.0f / (znear - zfar);
//	PROJECTION_M[0][3] = -(xmax + xmin) / (xmax - xmin);
//	PROJECTION_M[1][3] = -(ymax + ymin) / (ymax - ymin);
//	PROJECTION_M[2][3] = (znear + zfar) / (znear - zfar);
//	PROJECTION_M[3][3] = 1;
//
//	PROJECTION = Matrix4X4(&PROJECTION_M[0][0]);
//	PROJECTION * p;
//}
//void LoadIdentity()
//{
//	OBJECT.setIdentity();
//}
//enum Cell{ POINT_TYPE,LINE_TYPE, TRIANGLE_TYPE };
//typedef struct tagEDGE
//{
//	double xi;
//	double dx;
//	int ymax;
//}EDGE;
//int RenderList::Insert_PolyF4DV1_RenderList(PolyF4DV1& poly)
//{
//	if (num_polys >= RENDERLIST4DV1_MAX_POLYS)
//		return 0;
//	poly_ptrs[num_polys] = &(poly_data[num_polys]);
//	
//	memcpy_s((void*)&poly_data[num_polys], sizeof(poly_data[0]), (void*)&poly, sizeof(poly));
//
//	if (num_polys == 0)
//	{
//		poly_data[0].next = NULL;
//		poly_data[0].prev = NULL;
//	}
//	else
//	{
//		poly_data[num_polys].next = NULL;
//		poly_data[num_polys].prev = &poly_data[num_polys - 1];
//	}
//	num_polys++;
//	return 1;
//	//polyPoint_vector.insert(polyPoint_vector.end()-1 ,&poly);
//}
//void InitTable(std::vector<std::list<EDGE>>& slNet, const void* data, int ymin, int ymax)
//{
//	EDGE e;
//	for (int i = 0; i < 3; i++)
//	{
//
//	}
//
//}
//void lineScan(Cell a, void* data)//需要传递一个包含所有图元的容器，然后在其中遍历，并取出图元的类型，例如点，线，三角等，然后将它的数据部分取出，进行插值
//{
//	Point3D p1;
//	Point3D p2;
//	Point3D p3;
//
//	float vmin;
//	float vmax;
//	float temp;
//	vmin = p3[2] < (temp = (p1[2] < p2[2]) ? p1[2] : p2[2]) ? p3[2] : temp;
//	vmax = p3[2] > (temp = (p1[2] > p2[2]) ? p1[2] : p2[2]) ? p3[2] : temp;
//	std::vector<std::list<EDGE>> s(vmax - vmin + 1);
//	if (a = POINT_TYPE)
//	{
//
//	}
//	else if (a = LINE_TYPE)
//	{
//
//	}
//	else if (a = TRIANGLE_TYPE)
//	{
//		//data里面包含有定点位置，法线，颜色，正切值，uv坐标等
//		//对于所有的属性都需要插值计算
//
//	}
//}
//
//
//void culling(Point3D p1, Point3D p2, Point3D p3, Point3D E)
//{
//	if ((E - p1) * (p2 - p1).cross(p3 - p1) > 0)
//	{
//		//面向观察者
//	}
//	//or 
//	float M[][4] =
//	{
//		p1[1],
//		p1[2],
//		p1[3]
//	};
//
//}
//
//USHORT(*RGB16Bit)(int r, int g, int b) = NULL;
//DWORD start_clock_count = 0;
//
//DWORD Get_Clock(void)
//{
//	return (GetTickCount());
//}
//DWORD Start_Clock(void)
//{
//	return (start_clock_count = Get_Clock());
//}
//DWORD Wait_Clock(DWORD count)
//{
//	while ((Get_Clock() - start_clock_count) < count);
//	return (Get_Clock());
//}
//USHORT RGB16BIT565(int r,int g,int b)
//{
//	r >>= 3; g >>= 2; b >>= 3;
//	return _RGB16BIT565((r), (g), (b));
//}
//
//USHORT RGB16BIT555(int r, int g, int b)
//{
//	r >>= 3; g >>= 3; b >>= 3;
//	return _RGB16BIT555((r), (g), (b));
//}
////const Rtti& Object4DV1::GetRttiType()const
////{
////	return TYPE;
////}
////
////Object* Object4DV1::GetObjectByName(const std::string& name)
////{
////	return this;
////}
////void Object4DV1::GetAllObjectsByName(const std::string& name, std::vector<Object*>& objects)
////{
////
////}
//int Load_Object_PLG(Object4DV1* obj, char* filename, Vector4D& scale, Vector4D& pos, Vector4D& rot)
//{
//	FILE * fp = nullptr;
//	char buffer[256];
//	char* token_string;
//	memset(obj, 0, sizeof(Object4DV1));
//	obj->state = OBJECT4DV1_STATE_ACTIVE | OBJECT4DV1_STATE_VISIBLE;
//	obj->world_pos = pos;
//	if (!(fp = fopen(filename, "r")))
//	{
//		return 0;
//	}
//	
//	if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
//	{
//		return 0;
//	}
//	sscanf(token_string, "%s %d %d", obj->name, &obj->num_vertices, &obj->num_polys);
//	for (int vertex = 0; vertex < obj->num_vertices;vertex++)
//	{
//		if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
//		{
//			return 0;
//		}
//		sscanf(token_string, "%f %f %f", &obj->vlist_local[vertex][0],
//			&obj->vlist_local[vertex][1],
//			&obj->vlist_local[vertex][2]);
//		obj->vlist_local[vertex][3] = 1;
//		obj->vlist_local[vertex][0] *= scale[0];
//		obj->vlist_local[vertex][1] *= scale[1];
//		obj->vlist_local[vertex][2] *= scale[2];
//	
//	}
//	Compute_Object4DV1_Radius(obj);
//	int poly_surface_desc = 0;
//	int poly_num_verts = 0;
//	char temp_string[8];
//	//Assemble the primitive
//	for (int poly = 0; poly < obj->num_polys; poly++)
//	{
//		if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
//		{
//			return 0;
//		}
//		sscanf(token_string, "%s %d %d %d %d", temp_string, &poly_num_verts, &obj->plist[poly].vert[0],
//			&obj->plist[poly].vert[1], &obj->plist[poly].vert[2]);
//		if (temp_string[0] == '0' && toupper(temp_string[1] == 'x'))
//			sscanf(temp_string, "%x", &poly_surface_desc);
//		else
//			poly_surface_desc = atoi(temp_string);
//
//		obj->plist[poly].vlist = obj->vlist_local;
//
//		if ((poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG))
//		{
//			//SET_BIT(obj->plist[poly].attr, POLY3DV1_ATTR_2SIDED);
//			int red = ((poly_surface_desc & 0x0f00) >> 8);
//			int green = (poly_surface_desc & 0x00f0) >> 4;
//			int blue = (poly_surface_desc & 0x000f);
//			
//			obj->plist[poly].color = RGB16Bit(red, green, blue);
//
//		}
//		else
//		{
//			//8bit Color Now has beed Dispatch
//		}
//		int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);
//		//Set Shade Attr
//		obj->plist[poly].state = POLY4DV1_STATE_ACTIVE; 
//	}
//	fclose(fp);
//	return 1;
//}

void Hikari::Renderer::Initialize(int width, int height, Texture::Format colorFormat, Texture::Format depthStencilFormat, int numMultisamples)
{
	mWidth = width;
	mHeight = height;
	mColorFormat = colorFormat;
	mDepthStencilFormat = depthStencilFormat;
	mNumMultisamples = numMultisamples;

	
}

void Hikari::Renderer::Terminate()
{
}

inline int Hikari::Renderer::GetWidth() const
{
	return mWidth;
}

inline int Hikari::Renderer::GetHeight() const
{
	return mHeight;
}

inline Texture::Format Hikari::Renderer::GetColorFormat() const
{
	return mColorFormat;
}

inline Texture::Format Hikari::Renderer::GetDepthStencilFormat() const
{
	return mDepthStencilFormat;
}

inline int Hikari::Renderer::GetNumMultisamples() const
{
	return mNumMultisamples;
}

void Hikari::Renderer::Bind(const VertexFormat* vFormat)
{
	
}

void Hikari::Renderer::BindAll(const VertexFormat * vformat)
{
}

void Hikari::Renderer::Unbind(const VertexFormat * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const VertexFormat * vFormat)
{
}

void Hikari::Renderer::Enable(const VertexFormat * vFormat)
{
}

void Hikari::Renderer::Disable(const VertexFormat * vFormat)
{
}

void Hikari::Renderer::Bind(const VertexBuffer * vFormat)
{
}

void Hikari::Renderer::BindAll(const VertexBuffer * vformat)
{
}

void Hikari::Renderer::Unbind(const VertexBuffer * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const VertexBuffer * vFormat)
{
}

void Hikari::Renderer::Enable(const VertexBuffer * vFormat)
{
}

void Hikari::Renderer::Disable(const VertexBuffer * vFormat)
{
}

void * Hikari::Renderer::Lock(const VertexBuffer * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const VertexBuffer * vbBuffer)
{
}

void Hikari::Renderer::Update(const VertexBuffer * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const VertexBuffer * vbuffer)
{
}

void Hikari::Renderer::Bind(const IndexBuffer * vFormat)
{
}

void Hikari::Renderer::BindAll(const IndexBuffer * vformat)
{
}

void Hikari::Renderer::Unbind(const IndexBuffer * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const IndexBuffer * vFormat)
{
}

void Hikari::Renderer::Enable(const IndexBuffer * vFormat)
{
}

void Hikari::Renderer::Disable(const IndexBuffer * vFormat)
{
}

void * Hikari::Renderer::Lock(const IndexBuffer * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const IndexBuffer * vbBuffer)
{
}

void Hikari::Renderer::Update(const IndexBuffer * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const IndexBuffer * vbuffer)
{
}

void Hikari::Renderer::Bind(const Texture1D * vFormat)
{
}

void Hikari::Renderer::BindAll(const Texture1D * vformat)
{
}

void Hikari::Renderer::Unbind(const Texture1D * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const Texture1D * vFormat)
{
}

void Hikari::Renderer::Enable(const Texture1D * vFormat)
{
}

void Hikari::Renderer::Disable(const Texture1D * vFormat)
{
}

void * Hikari::Renderer::Lock(const Texture1D * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const Texture1D * vbBuffer)
{
}

void Hikari::Renderer::Update(const Texture1D * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const Texture1D * vbuffer)
{
}

void Hikari::Renderer::Bind(const Texture2D * vFormat)
{
}

void Hikari::Renderer::BindAll(const Texture2D * vformat)
{
}

void Hikari::Renderer::Unbind(const Texture2D * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const Texture2D * vFormat)
{
}

void Hikari::Renderer::Enable(const Texture2D * vFormat)
{
}

void Hikari::Renderer::Disable(const Texture2D * vFormat)
{
}

void * Hikari::Renderer::Lock(const Texture2D * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const Texture2D * vbBuffer)
{
}

void Hikari::Renderer::Update(const Texture2D * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const Texture2D * vbuffer)
{
}

void Hikari::Renderer::Bind(const Texture3D * vFormat)
{
}

void Hikari::Renderer::BindAll(const Texture3D * vformat)
{
}

void Hikari::Renderer::Unbind(const Texture3D * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const Texture3D * vFormat)
{
}

void Hikari::Renderer::Enable(const Texture3D * vFormat)
{
}

void Hikari::Renderer::Disable(const Texture3D * vFormat)
{
}

void * Hikari::Renderer::Lock(const Texture3D * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const Texture3D * vbBuffer)
{
}

void Hikari::Renderer::Update(const Texture3D * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const Texture3D * vbuffer)
{
}

void Hikari::Renderer::Bind(const RenderTarget * vFormat)
{
}

void Hikari::Renderer::BindAll(const RenderTarget * vformat)
{
}

void Hikari::Renderer::Unbind(const RenderTarget * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const RenderTarget * vFormat)
{
}

void Hikari::Renderer::Draw(const VisibleSet & visibleSet, GlobalEffect * globalEffect)
{
}


void Hikari::Renderer::Draw(const Visual * visual, const VisualEffectInstance * instance)
{
}

inline Camera * Hikari::Renderer::GetCamera()
{
	return nullptr;
}

inline const HMatrix & Hikari::Renderer::GetViewMatrix() const
{
	// TODO: 在此处插入 return 语句
}

inline const HMatrix & Hikari::Renderer::GetProjectionMatrix() const
{
	// TODO: 在此处插入 return 语句
}

inline const HMatrix & Hikari::Renderer::GetPostProjectionMatrix() const
{
	// TODO: 在此处插入 return 语句
}

bool Hikari::Renderer::GetPickRay(int x, int y, APoint & origin, AVector & direction) const
{
	return false;
}

inline void Hikari::Renderer::SetClearColor(const Float4 & color)
{
}

inline const Float4 & Hikari::Renderer::GetClearColor() const
{
	// TODO: 在此处插入 return 语句
}

inline void Hikari::Renderer::SetClearDepth(float clearDepth)
{
}

inline float Hikari::Renderer::GetClearDepth() const
{
	return 0.0f;
}

inline void Hikari::Renderer::SetClearStencil(unsigned int clearStencil)
{
}

inline unsigned int Hikari::Renderer::GetClearStencil() const
{
	return 0;
}

inline void Hikari::Renderer::GetColorMask(bool & allowRed, bool & allowGreen, bool & allowBlue, bool & allowAlpha) const
{
}

inline void Hikari::Renderer::SetOverrideAlphaState(const AlphaState * alphaState)
{
}

inline void Hikari::Renderer::SetOverrideCullState(const CullState * cullState)
{
}

inline void Hikari::Renderer::SetOverrideDepthState(const DepthState * depthState)
{
}

inline void Hikari::Renderer::SetOverrideOffsetState(const OffsetState * offsetState)
{
}

inline void Hikari::Renderer::SetOverrideStencilState(const StencilState * stencilState)
{
}

inline void Hikari::Renderer::SetOverrideWireState(const WireState * wireState)
{
}

inline const AlphaState * Hikari::Renderer::GetOverrideAlphaState() const
{
	return nullptr;
}

inline const CullState * Hikari::Renderer::GetOverrideCullState() const
{
	return nullptr;
}




void Hikari::Renderer::Draw(const Visual * visual)
{
	//DrawPrimitive(visual);
}
Hikari::Renderer::Renderer(RendererData* data)
{
	mData = data;
	mWidth = data->mWidth;
	mHeight = data->mHeight;
}

inline bool Hikari::Renderer::InTexture2DMap(const Texture2D * texture)
{
	return false;
}
void Hikari::Renderer::Bind(const VertexShader * vFormat)
{
}

void Hikari::Renderer::Unbind(const VertexShader * vFormat)
{
}

void Hikari::Renderer::Enable(const VertexShader * vFormat)
{
}

void Hikari::Renderer::Disable(const VertexShader * vFormat)
{
}

void Hikari::Renderer::Bind(const PixelShader * vFormat)
{
}

void Hikari::Renderer::Unbind(const PixelShader * vFormat)
{
}

void Hikari::Renderer::Enable(const PixelShader * vFormat)
{
}

void Hikari::Renderer::Disable(const PixelShader * vFormat)
{
}

void Hikari::Renderer::Update(const PixelShader * vbuffer)
{
}
