#ifndef _MENU_H_
#define _MENU_H_

#include "Basicdata.h"
#include "Scene.h"


class MenuScene :public Scene
{
	cPlane* mBg;
public:
	void Init();
	void Enter();
	void RenderForSelect(mat4 vp);
	void Updata();
	void Quit();
	void End();
};
#endif