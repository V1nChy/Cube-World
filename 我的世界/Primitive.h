#ifndef  _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "Angel.h"
#include "BasicData.h"

class cPrimitive
{
protected:
	GLuint mVao, mVbo, mTex;
	int mVerticesCount;
public:
	virtual void Init();
	virtual void Enter(GLuint vIndex, GLuint vnIndex, GLuint vtIndex,GLuint vnT);
	virtual void Render();
};
class cFacePrimi :public cPrimitive
{
public:
	cFacePrimi();
	void Init();
};
class cPlanePrimi :public cPrimitive
{
public:
	cPlanePrimi();
	void Init();
};
class cBlockPrimi :public cPrimitive
{
public:
	cBlockPrimi();
	void Init();
};
class cBlock2Primi :public cPrimitive
{
public:
	cBlock2Primi();
	void Init();
};
class cCubePrimi :public cPrimitive
{
public:
	cCubePrimi();
	void Init();
};
#endif

