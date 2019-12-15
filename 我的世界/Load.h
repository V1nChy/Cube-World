#ifndef _LOAD_H_
#define _LOAD_H_

#include "Basicdata.h"
#include "Scene.h"

class LoadGameScene :public Scene
{
	cPlane* mBg;
public:
	static BOOL mIsLoading;
	static int mRecordNum;
	static int mUsedRecord;
	void Init();
	void Enter();

	void LoadFile(const char* pathName);

	void RenderForSelect(mat4 vp);
	void Updata();
	void Quit();
	void End();
};

#endif
