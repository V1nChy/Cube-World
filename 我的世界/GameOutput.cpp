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

int LoadTexture(const char *szPathName/*����ͼ��·����*/)
{
	HDC		hdcTemp;				// DC���
	HBITMAP	hbmpTemp;			// Bitmap���
	CImage  	*pPicture;			// CImage����ָ��
	long			lWidth;				// ͼ����
	long			lHeight;				// ͼ��߶�
	long			lWidthPixels;			// ������Ŀ��(2��n�η�)
	long			lHeightPixels;			// ������ĸ߶�(2��n�η�)
	GLint		glMaxTexDim;		// �������ߴ�

	pPicture = new CImage;						// ����CImage����
	HRESULT hr = pPicture->Load(szPathName);	// ����ͼ���ļ�
	if (FAILED(hr))							// �������ʧ��
		return FALSE;							// Return False (Failure)

	hdcTemp = CreateCompatibleDC(GetDC(0));	// ��������DC
	if (!hdcTemp)								// ����ʧ��?
	{
		pPicture->Destroy();					// ����CImage��������
		delete pPicture;						// ��new�͵���delete
		return FALSE;							// Return False (Failure)
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);	// ��ȡ��֧�ֵ��������ߴ�

	lWidth = pPicture->GetWidth();					// ��ȡͼ����
	lHeight = pPicture->GetHeight();					// ��ȡͼ��߶�

														/*��ͼ��ߴ����Ϊ2����������*/
	if (lWidth <= glMaxTexDim)	// ͼ����С�ڵ����������ߴ�?
		lWidthPixels = 1 << (int)floor((log((double)lWidth) / log(2.0f)) + 0.5f);
	else	// ������Ϊ�������ߴ�
		lWidthPixels = glMaxTexDim;

	if (lHeight <= glMaxTexDim)	// ͼ��߶�С�ڵ����������ߴ�?
		lHeightPixels = 1 << (int)floor((log((double)lHeight) / log(2.0f)) + 0.5f);
	else	// ������Ϊ�������ߴ�
		lHeightPixels = glMaxTexDim;

	/*������ʱBitmap*/
	BITMAPINFO	bi = { 0 };			// Bitmap��Ϣ
	DWORD		*pBits = 0;			// ָ��Bitmap�������ݵ�ָ��
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// ���ýṹ���С
	bi.bmiHeader.biBitCount = 32;					// ÿ������32λ
	bi.bmiHeader.biWidth = lWidthPixels;			// Bitmap���
	bi.bmiHeader.biHeight = lHeightPixels;			// Bitmap�߶�
	bi.bmiHeader.biCompression = BI_RGB;				// RGB����
	bi.bmiHeader.biPlanes = 1;						// 1 ������ƽ��

													/*����Bitmap*/
	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);
	if (!hbmpTemp)	// ����ʧ��?
	{
		DeleteDC(hdcTemp);	// ɾ��DC
		pPicture->Destroy();	// ����ͼ��
		delete pPicture;		// ��new�͵���delete
		return FALSE;			// Return False (Failure)
	}

	SelectObject(hdcTemp, hbmpTemp);	// ����BitmapѡΪDC�ġ����塱

										/*��ͼ����Ƶ�Bitmap��*/
	RECT rectDest;	// Ŀ�����
	rectDest.left = 0;
	rectDest.right = lWidthPixels;
	rectDest.top = 0;
	rectDest.bottom = lHeightPixels;
	SetStretchBltMode(hdcTemp, COLORONCOLOR);	// ����Drawʱ������ģʽ
	pPicture->Draw(hdcTemp, rectDest);

	/*��BGR�������ݸ�ʽת��ΪRGB��ʽ*/
	for (long i = 0; i < lWidthPixels * lHeightPixels; i++)	// ������������
	{
		BYTE* pPixel = (BYTE*)(&pBits[i]);	// ��ȡ��ǰ����ָ��
		BYTE  temp = pPixel[0];		// ����ɫ�������浽temp
		pPixel[0] = pPixel[2];			// ����ɫ�������浽��һ������
		pPixel[2] = temp;				// ����ɫ�������浽����������

										// û��͸������͸������Ϊ255(��ȫ��͸��)
		if (pPicture->GetBPP() < 32)
			pPixel[3] = 255;
	}

	// ������ͼ�����ݷ��͵�GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidthPixels, lHeightPixels,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	glGenerateMipmap(GL_TEXTURE_2D);//�����༶��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	DeleteObject(hbmpTemp);		// ɾ��Bitmap���� 
	DeleteDC(hdcTemp);			// ɾ��DC

	pPicture->Destroy();		// ����CImageͼ��
	delete pPicture;			// ��new�͵���delete
	return TRUE;				// Return True (һ������)
}