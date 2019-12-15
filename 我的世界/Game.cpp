#include "Game.h"
#include "Load.h"
#include "GameFrame.h"
#include <atlimage.h>

int LoadTexture(GLenum target,const char *szPathName)
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
	glTexImage2D(target, 0, GL_RGBA, lWidthPixels, lHeightPixels,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	DeleteObject(hbmpTemp);		// ɾ��Bitmap���� 
	DeleteDC(hdcTemp);			// ɾ��DC

	pPicture->Destroy();		// ����CImageͼ��
	delete pPicture;			// ��new�͵���delete
	return TRUE;				// Return True (һ������)
}

cParticle::cParticle()
{
	time = 0;
	mSpeed = 2;
	NumVertices = 50000;
	point3 v[50000];
	for (int i = 0; i < NumVertices; i++)
	{
		v[i].x = rand() % 4000 / 100.0;
		v[i].y = rand() % 4000/100.0;
		v[i].z = rand() % 4000 / 100.0;
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point3)*NumVertices, v, GL_STATIC_DRAW);

	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer("ParticleShader");
	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture("Res\\textures\\snow.png");

	mModelTranslate *= Translate(-40 / 2.0, 0.0, -40 / 2.0);
}
void cParticle::Enter()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	mUseShader->Enter();
	glEnableVertexAttribArray(mUseShader->vPosition);
	glVertexAttribPointer(mUseShader->vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}
void cParticle::Render()
{
	time += GameFrame::GetObject()->mDeltaTime*mSpeed;
	if (time > 25)
		time = 0;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTex);

	glUniform1f(mUseShader->Time, -time);
	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate);
	glDrawArrays(GL_POINTS, 0, NumVertices);
}

GLuint cSky::mCubeTex;
cSky::cSky()
{
	ID = SKY;
	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer("SkyShader");
	mPrimi = GameFrame::GetObject()->GetGO()->GetPrimiPointer("Face");

	mModelTranslate *= Translate(0.0,2.0,0.0);

	mTex = -1;

	glGenTextures(1, &mCubeTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP,mCubeTex);
	LoadTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,"Res\\textures\\environment\\sky_up.jpg");
	LoadTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,"Res\\textures\\environment\\sky_dn.jpg");
	LoadTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,"Res\\textures\\environment\\sky_lt.jpg");
	LoadTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X,"Res\\textures\\environment\\sky_rt.jpg");
	LoadTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,"Res\\textures\\environment\\sky_ft.jpg");
	LoadTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,"Res\\textures\\environment\\sky_bk.jpg");
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);//�����༶��������
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	glGenTextures(6,Tex);
	glBindTexture(GL_TEXTURE_2D, Tex[UP]);
	LoadTexture("Res\\textures\\environment\\sky_up.jpg");

	glBindTexture(GL_TEXTURE_2D, Tex[DOWN]);
	LoadTexture("Res\\textures\\environment\\sky_dn.jpg");

	glBindTexture(GL_TEXTURE_2D, Tex[LEFT]);
	LoadTexture("Res\\textures\\environment\\sky_lt.jpg");

	glBindTexture(GL_TEXTURE_2D, Tex[RIGHT]);
	LoadTexture("Res\\textures\\environment\\sky_rt.jpg");

	glBindTexture(GL_TEXTURE_2D, Tex[FRONT]);
	LoadTexture("Res\\textures\\environment\\sky_ft.jpg");

	glBindTexture(GL_TEXTURE_2D, Tex[BACK]);
	LoadTexture("Res\\textures\\environment\\sky_bk.jpg");
}
void cSky::Render()
{
	glDisable(GL_CULL_FACE);
	glActiveTexture(GL_TEXTURE0);
	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate*Translate(0.0,0.0,-19.9)*Scale(20, 20, 1)*RotateY(180));
	glBindTexture(GL_TEXTURE_2D, Tex[FRONT]);
	mPrimi->Render();

	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate*Translate(0.0, 0.0, 19.9)*Scale(20, 20, 1));
	glBindTexture(GL_TEXTURE_2D, Tex[BACK]);
	mPrimi->Render();

	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate*RotateY(90)*Translate(0.0, 0.0, 19.9)*Scale(20, 20, 1));
	glBindTexture(GL_TEXTURE_2D, Tex[RIGHT]);
	mPrimi->Render();

	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate*RotateY(270)*Translate(0.0, 0.0, 19.9)*Scale(20, 20, 1));
	glBindTexture(GL_TEXTURE_2D, Tex[LEFT]);
	mPrimi->Render();

	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate*Translate(0.0, 19.9, 0.0)*RotateZ(180)*RotateY(90)*RotateX(90)*Scale(20, 20, 1));
	glBindTexture(GL_TEXTURE_2D, Tex[UP]);
	mPrimi->Render();

	/*glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate*RotateX(90)*Translate(0.0, 0.0, 19.9)*Scale(20, 20, 1));
	glBindTexture(GL_TEXTURE_2D, Tex[DOWN]);
	mPrimi->Render();*/

	glEnable(GL_CULL_FACE);
}

cWater::cWater()
{
	mTime = 0;
	mWidth = 40;
	mDepth = 40;
	NumVertices = mWidth * mDepth * 6;

	point3 *vertex = new point3[NumVertices];
	vec3 *normal = new vec3[NumVertices];
	vec2 *texcoord = new vec2[NumVertices];

	int index = 0;
	float s = 0,t=0;
	for (int x = -mWidth / 2; x < mWidth / 2; x ++)
	{
		for (int z = mWidth / 2; z > -mWidth / 2; z --)
		{
			point3 LowerLeft = point3(x, 0, z);
			point3 LowerRight = point3(x + 1, 0, z);
			point3 UpperLeft = point3(x, 0, z - 1);
			point3 UpperRight = point3(x + 1, 0, z - 1);

			texcoord[index] = vec2(s, t + 1); normal[index] = vec3(0.0, 1.0, 0.0); vertex[index++] = UpperLeft;
			texcoord[index] = vec2(s, t);	  normal[index] = vec3(0.0, 1.0, 0.0); vertex[index++] = LowerLeft;
			texcoord[index] = vec2(s + 1, t); normal[index] = vec3(0.0, 1.0, 0.0); vertex[index++] = LowerRight;

			texcoord[index] = vec2(s, t + 1); normal[index] = vec3(0.0, 1.0, 0.0); vertex[index++] = UpperLeft;
			texcoord[index] = vec2(s + 1, t); normal[index] = vec3(0.0, 1.0, 0.0); vertex[index++] = LowerRight;
			texcoord[index] = vec2(s + 1, t + 1); normal[index] = vec3(0.0, 1.0, 0.0); vertex[index++] = UpperRight;
		}
	}


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(vec3) + sizeof(vec2))*NumVertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*NumVertices, vertex);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3)*NumVertices, sizeof(vec3)*NumVertices, normal);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(vec3))*NumVertices, sizeof(vec2)*NumVertices, texcoord);

	delete[]vertex;
	delete[]normal;
	delete[]texcoord;

	mUseShader = GameFrame::GetObject()->GetGO()->GetShaderPointer("WaterShader");
	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);
	LoadTexture("Res\\textures\\environment\\water.jpg");

	glGenTextures(1, &nTex);
	glBindTexture(GL_TEXTURE_2D, nTex);
	LoadTexture("Res\\textures\\environment\\water_NORM.jpg");

	mModelTranslate *= Translate(0.0,0.0,0.0);
}
void cWater::Enter()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	mUseShader->Enter();
	glEnableVertexAttribArray(mUseShader->vPosition);
	glVertexAttribPointer(mUseShader->vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(mUseShader->vNormal);
	glVertexAttribPointer(mUseShader->vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point3)*NumVertices));
	glEnableVertexAttribArray(mUseShader->vTexCoord);
	glVertexAttribPointer(mUseShader->vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET((sizeof(point3) + sizeof(vec3))*NumVertices));

}
void cWater::Render()
{
	mTime += 0.05;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTex);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, nTex);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cSky::mCubeTex);

	glUniform1f(mUseShader->Time, mTime);
	glUniformMatrix4fv(mUseShader->ModelView, 1, GL_TRUE, GameFrame::GetObject()->GetGI()->mMatView*mModelTranslate);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

BOOL GameScene::bParOn;
void GameScene::Init()
{
	bParOn = FALSE;

	mTime = 0;
	mSky = new cSky();
	mMap = new cBlockMap();
	mWater = new cWater();
	mParticle = new cParticle();

	LoadButton(new cGoodsButton(point3(-0.8, -1.0, -2.0), "Res\\textures\\buttons\\grassIco.png"), BUTTON, GRASS_BLOCK, "");
	LoadButton(new cGoodsButton(point3(-0.6, -1.0, -2.0), "Res\\textures\\buttons\\sandIco.png"), BUTTON, SAND_BLOCK, "");
	LoadButton(new cGoodsButton(point3(-0.4, -1.0, -2.0), "Res\\textures\\buttons\\clay.png"), BUTTON, CLAY_BLOCK, "");
	LoadButton(new cGoodsButton(point3(-0.2, -1.0, -2.0), "Res\\textures\\buttons\\stoneIco.png"), BUTTON, STONE_BLOCK, "");
	LoadButton(new cGoodsButton(point3(0.0, -1.0, -2.0), "Res\\textures\\buttons\\stonebrickIco.png"), BUTTON, STONEBRICK_BLOCK, "");
	LoadButton(new cGoodsButton(point3(0.2, -1.0, -2.0), "Res\\textures\\buttons\\brickIco.png"), BUTTON, BRICK_BLOCK, "");
	LoadButton(new cGoodsButton(point3(0.4, -1.0, -2.0), "Res\\textures\\buttons\\planksIco.png"), BUTTON, PLANKS_BLOCK, "");
	LoadButton(new cGoodsButton(point3(0.6, -1.0, -2.0), "Res\\textures\\buttons\\glassIco.png"), BUTTON, GLASS_BLOCK, "");
	LoadButton(new cGoodsButton(point3(0.8, -1.0, -2.0), "Res\\textures\\buttons\\bedrockIco.png"), BUTTON, BEDROCK_BLOCK, "");
}
void GameScene::Enter()
{
	mSoundPlay.Stop(MENU_BGM);
	mSoundPlay.play(GAME_BGM);

	bParOn = FALSE;
	glUniform1i(GameFrame::GetObject()->GetGO()->GetShaderPointer("LightTexture")->bFogOn, 0);

	mTime = 0;
	mParticle->time = 0;
	GameFrame::GetObject()->GetGI()->ResetCamera();
	GameFrame::GetObject()->GetGI()->mButtonSelect = FALSE;
	if (LoadGameScene::mIsLoading)
	{
		mMap->LoadMap();

	}
	else
	{
		mMap->BuildMap();
		int high = mMap->SearchHigh(0, 0);
		GameFrame::GetObject()->GetGI()->mMatCameraReverse = mat4()*Translate(0.0, 1.8 + high, 0.0);
		GameFrame::GetObject()->GetGI()->mMatCamera = mat4()*Translate(0.0, -1.8 - high, 0.0);
	}
}
void GameScene::Render()
{
	GameFrame::GetObject()->GetGI()->UpdateCamera();

	mWater->Enter();
	mWater->Render();

	mSky->Enter();
	mSky->Render();

	mMap->Render();

	if (bParOn)
	{
		mParticle->Enter();
		mParticle->Render();
	}

	glDisable(GL_DEPTH_TEST);
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		i->second->Enter();
		i->second->Render();
	}
	glEnable(GL_DEPTH_TEST);
}
void GameScene::RenderForSelect(mat4 vp)
{
	mMap->RenderForSelect(vp);
}
void GameScene::Updata()
{
	mTime += GameFrame::GetObject()->mDeltaTime;
	if (mTime > 260)
	{
		mSoundPlay.play(GAME_BGM);
		mTime -= 260;
	}
	map<int, cButton*>::iterator i;
	for (i = mButtonMap.begin(); i != mButtonMap.end(); i++)
	{
		if (i->second->ID == cBlockMap::mNowBlock)
			i->second->SetActive();
		else
			i->second->SetUnActive();
	}
}
void GameScene::Quit()
{
	mMap->SaveMap();
	mSoundPlay.Stop(GAME_BGM);
}
void GameScene::End()
{
}