#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Primitive.h"
#include "ShaderData.h"

class cObject
{
protected:
	mat4 mModelTranslate;
	cPrimitive* mPrimi;
	cShaderData* mUseShader;
	materialStruct* mMaterial;
	GLuint mTex;
	GLuint mNormalTex;
public:
	cObject();
	~cObject();
	int ID;
	int idParent;
	BOOL bOnlyTex;
	BOOL bNormalOn;
	virtual void Init();
	virtual void Enter();
	virtual void Render();
	virtual void RenderForSelect(mat4 vp);
	virtual void End();
	virtual void Update(point3 pos,int offset);
	virtual void SetModelMat(mat4 mat);
	virtual void SetMaterial();
};

class cButton :public cObject
{
public:
	BOOL mActive;
	BOOL mClick;
	string mTargetSceneName;

	cButton();
	virtual void SetActive();
	virtual void SetUnActive();
};
class cButton1 :public cButton
{
	GLuint mOutTex;
	GLuint mInTex;
public:
	cButton1(point3 pos, const char* in, const char* out);
	void Render();
};
class cGoodsButton :public cButton
{
	mat4 mUnactiveMat;
	mat4 mActiveMat;
public:
	cGoodsButton(point3 pos, const char* pathTex);
	void SetActive();
	void SetUnActive();
	void Render();
};

class cBlock :public cObject
{
public:
	cBlock(int id, char* shader, char* primi, char* pathTex);
	cBlock(int id, char* shader, char* primi, materialStruct* material, char* pathTex);
	cBlock(int id, char* shader, char* primi, materialStruct* material, char* pathTex, char* pathNorTex);
	void Render();
	void RenderForSelect(mat4 vp);
};

class cPlane :public cObject
{
public:
	cPlane(const char* pathName);
	void Render();
};

class cBlockMap
{
	mat4 mModelTranslate;
	cBlock* mGrassBlock;
	cBlock* mSandBlock;
	cBlock* mClayBlock;
	cBlock* mStoneBlock;
	cBlock* mStoneBrickBlock;
	cBlock* mBrickBlock;
	cBlock* mPlanksBlock;
	cBlock* mGlassBlock;
	cBlock* mBedrockBlock;

	cBlock* mTreeLogBlock;
	cBlock* mTreeLeavesBlock;

	int mBlockMap[40][20][40];
	vector<isPos> mvGlass;
	int mMapWidth, mMapHeight, mMapDepth;
public:
	static int mNowBlock;
	cBlockMap();
	~cBlockMap();
	void Render();

	void RenderForSelect(mat4 vp);
	void Update(int px, int py, int pz, point3* fPos, point3 &cPos, int value);

	void BuildMap();
	void divide(int begin, int offset, int n);
	int SearchHigh(float x, float z);
	BOOL Collision(float x, float y, float z);

	void LoadMap();
	void SaveMap();
};
#endif
