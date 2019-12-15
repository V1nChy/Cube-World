#ifndef _GAME_H_
#define _GAME_H_

#include "Basicdata.h"
#include "Scene.h"

class cParticle:public cObject
{
	GLuint vao, vbo;
	int NumVertices;
	float mSpeed;
public:
	float time;
	cParticle();
	void Enter();
	void Render();
};
class cSky :public cObject
{
	GLuint Tex[6];
public:
	cSky();
	static GLuint mCubeTex;

	void Render();
};
class cWater:public cObject
{
	float mTime;
	int mWidth, mDepth;
	GLuint NumVertices;

	GLuint nTex;
	GLuint vao, vbo;
public:
	cWater();
	void Enter();
	void Render();
};
class GameScene :public Scene
{
	float mTime;
	cSky* mSky;
	cWater* mWater;
	cParticle* mParticle;
public:
	static BOOL bParOn;
	void Init();
	void Enter();
	void Render();
	void RenderForSelect(mat4 vp);
	void Updata();
	void Quit();
	void End();
};
#endif