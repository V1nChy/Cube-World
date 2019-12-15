#include"GameOutput.h"
#include"Gameframe.h"
#include <atlimage.h>

cShaderData* GameOutput::m_pShaderID=NULL;
GameOutput::GameOutput()
{
	m_pPrimiID = NULL;
}
GameOutput::~GameOutput()
{
	map<string, cShaderData*>::iterator i;
	for (i = mShaderMap.begin(); i != mShaderMap.end(); i++)
	{
		delete i->second;
	}
	mShaderMap.clear();

	map<string, cPrimitive*>::iterator j;
	for (j = mPrimiMap.begin(); j != mPrimiMap.end(); j++)
	{
		delete j->second;
	}
	mPrimiMap.clear();
}
void GameOutput::Init()
{
	LoadShader();
	SetShader("LightTexture");

	LoadPrimi();
	SetPrimi("Plane");
}
BOOL GameOutput::LoadShader()
{
	mShaderMap["WaterShader"] = new cWaterShader();
	mShaderMap["SkyShader"] = new cSkyShader();
	mShaderMap["LightTexture"] = new cLightTextureShader();
	mShaderMap["ParticleShader"] = new cParticleShader();
	return TRUE;
}
BOOL GameOutput::SetShader(const string nameID)
{
	map<string, cShaderData*>::iterator i = mShaderMap.find(nameID);
	if (i == mShaderMap.end())
		return FALSE;
	m_pShaderID = i->second;
	m_pShaderID->Enter();
	return TRUE;
}
cShaderData* GameOutput::GetShaderPointer(const string nameID)
{
	map<string, cShaderData*>::iterator i = mShaderMap.find(nameID);
	if (i == mShaderMap.end())
		return NULL;
	return i->second;
}

BOOL GameOutput::LoadPrimi()
{
	mPrimiMap["Face"] = new cFacePrimi();
	mPrimiMap["Plane"] = new cPlanePrimi();
	mPrimiMap["Block"] = new cBlockPrimi();
	mPrimiMap["Block2"] = new cBlock2Primi();

	return TRUE;
}
BOOL GameOutput::SetPrimi(const string nameID)
{
	map<string, cPrimitive*>::iterator i = mPrimiMap.find(nameID);
	if (i == mPrimiMap.end())
		return FALSE;
	m_pPrimiID = i->second;
	m_pPrimiID->Enter(m_pShaderID->vPosition,0, m_pShaderID->vTexCoord, m_pShaderID->vTangent);

	return TRUE;
}
cPrimitive* GameOutput::GetPrimiPointer(const string nameID)
{
	map<string, cPrimitive*>::iterator i = mPrimiMap.find(nameID);
	if (i == mPrimiMap.end())
		return NULL;
	return i->second;
}

int LoadTexture(const char *szPathName/*纹理图像路径名*/)
{
	HDC		hdcTemp;				// DC句柄
	HBITMAP	hbmpTemp;			// Bitmap句柄
	CImage  	*pPicture;			// CImage对象指针
	long			lWidth;				// 图像宽度
	long			lHeight;				// 图像高度
	long			lWidthPixels;			// 调整后的宽度(2的n次方)
	long			lHeightPixels;			// 调整后的高度(2的n次方)
	GLint		glMaxTexDim;		// 最大纹理尺寸

	pPicture = new CImage;						// 创建CImage对象
	HRESULT hr = pPicture->Load(szPathName);	// 加载图像文件
	if (FAILED(hr))							// 如果加载失败
		return FALSE;							// Return False (Failure)

	hdcTemp = CreateCompatibleDC(GetDC(0));	// 创建兼容DC
	if (!hdcTemp)								// 创建失败?
	{
		pPicture->Destroy();					// 销毁CImage对象内容
		delete pPicture;						// 有new就得有delete
		return FALSE;							// Return False (Failure)
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);	// 获取所支持的最大纹理尺寸

	lWidth = pPicture->GetWidth();					// 获取图像宽度
	lHeight = pPicture->GetHeight();					// 获取图像高度

														/*将图像尺寸调整为2的整数次幂*/
	if (lWidth <= glMaxTexDim)	// 图像宽度小于等于最大纹理尺寸?
		lWidthPixels = 1 << (int)floor((log((double)lWidth) / log(2.0f)) + 0.5f);
	else	// 否则设为最大纹理尺寸
		lWidthPixels = glMaxTexDim;

	if (lHeight <= glMaxTexDim)	// 图像高度小于等于最大纹理尺寸?
		lHeightPixels = 1 << (int)floor((log((double)lHeight) / log(2.0f)) + 0.5f);
	else	// 否则设为最大纹理尺寸
		lHeightPixels = glMaxTexDim;

	/*创建临时Bitmap*/
	BITMAPINFO	bi = { 0 };			// Bitmap信息
	DWORD		*pBits = 0;			// 指向Bitmap像素数据的指针
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// 设置结构体大小
	bi.bmiHeader.biBitCount = 32;					// 每个像素32位
	bi.bmiHeader.biWidth = lWidthPixels;			// Bitmap宽度
	bi.bmiHeader.biHeight = lHeightPixels;			// Bitmap高度
	bi.bmiHeader.biCompression = BI_RGB;				// RGB编码
	bi.bmiHeader.biPlanes = 1;						// 1 个像素平面

													/*创建Bitmap*/
	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);
	if (!hbmpTemp)	// 创建失败?
	{
		DeleteDC(hdcTemp);	// 删除DC
		pPicture->Destroy();	// 销毁图像
		delete pPicture;		// 有new就得有delete
		return FALSE;			// Return False (Failure)
	}

	SelectObject(hdcTemp, hbmpTemp);	// 将该Bitmap选为DC的“画板”

										/*将图像绘制到Bitmap上*/
	RECT rectDest;	// 目标矩形
	rectDest.left = 0;
	rectDest.right = lWidthPixels;
	rectDest.top = 0;
	rectDest.bottom = lHeightPixels;
	SetStretchBltMode(hdcTemp, COLORONCOLOR);	// 设置Draw时的拉伸模式
	pPicture->Draw(hdcTemp, rectDest);

	/*将BGR像素数据格式转换为RGB格式*/
	for (long i = 0; i < lWidthPixels * lHeightPixels; i++)	// 遍历所有像素
	{
		BYTE* pPixel = (BYTE*)(&pBits[i]);	// 获取当前像素指针
		BYTE  temp = pPixel[0];		// 将蓝色分量保存到temp
		pPixel[0] = pPixel[2];			// 将红色分量保存到第一个分量
		pPixel[2] = temp;				// 将蓝色分量保存到第三个分量

										// 没有透明度则透明度置为255(完全不透明)
		if (pPicture->GetBPP() < 32)
			pPixel[3] = 255;
	}

	// 将纹理图像数据发送到GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidthPixels, lHeightPixels,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	glGenerateMipmap(GL_TEXTURE_2D);//创建多级渐变纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	DeleteObject(hbmpTemp);		// 删除Bitmap对象 
	DeleteDC(hdcTemp);			// 删除DC

	pPicture->Destroy();		// 销毁CImage图像
	delete pPicture;			// 有new就得有delete
	return TRUE;				// Return True (一切正常)
}